/** @file datastore.c */
#include "datastore.h"
#include "datastore_control.h"
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int PRINTING = 0;



//Hash function courtesy of http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(unsigned char *str)
{
        unsigned long hash = 5381;
        int c;
        while (c = *(str++))
	  hash = ((hash << 5) + hash) + c;
        return hash;
}

void printTable(datastore_t *d) {
  int i;
  kvpair_t *it;
  for(i = 0; i < d->capacity; i++) {
    if(d->table[i])
      printf("%d : ", i);
    for(it = d->table[i]; it ; it = it->next)
      printf("(%s, %s), ", it->key, it->val);
    if(d->table[i])
      printf("\n");
  }
  fflush(stdout);
}

int count_elems(datastore_t *d) {
  int i, count=0;
  kvpair_t *it;
  for(i = 0; i < d->capacity; i++) {
    for(it = d->table[i]; it ; it = it->next) {
      count++;
    }
  }
  return count;
}

void datastore_init(datastore_t **d) {
}

pthread_mutex_t resize_lock;
pthread_mutex_t datastore_lock;

void datastore_load(datastore_t **d) {
  int i, length, table_idx=0;
  (*d) = malloc(sizeof(datastore_t));
  for(i = 0; i < NUM_LOCKS; i++)
    pthread_mutex_init((*d)->locks + i, NULL);
  pthread_mutex_init(&resize_lock, NULL);
  pthread_mutex_init(&datastore_lock, NULL);

  int *fd = open("data/serialized_data.bin", O_RDONLY);
  if(fd == -1) {
    (*d)->capacity = INIT_CAPACITY;
    (*d)->table = calloc((*d)->capacity, sizeof(kvpair_t*));
    (*d)->num_elems = 0;
    (*d)->file_size = 3*sizeof(int) + INIT_CAPACITY;
    int i;
  } else {
    struct stat s;
    int status = fstat(fd, &s);
    if(status < 0)
      perror("fstat failed");
    int size = s.st_size;
    char *map = mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);
    char *start = map;
    if(map == MAP_FAILED)
      perror("Error mapping file");    
    int capacity, num_elems, file_size;
    memcpy(&capacity, map, sizeof(int)); map += sizeof(int);
    memcpy(&num_elems, map, sizeof(int)); map += sizeof(int);
    memcpy(&file_size, map, sizeof(int)); map += sizeof(int);

    if(PRINTING) {
      printf("Capacity : %d, Num_elems : %d\n", capacity, num_elems); fflush(stdout);
    }
    
    (*d)->capacity = capacity;
    (*d)->table = calloc(capacity, sizeof(kvpair_t*));
    (*d)->num_elems = num_elems;
    (*d)->file_size = file_size;


    for(i = 0; i < num_elems; i++) {
      while( *map == '\n' ) {
	table_idx++;
	map++;
      }
      length = strlen(map);
      char *key = malloc(length + 1); strcpy(key, map); map += length + 1;

      length = strlen(map);
      char *value = malloc(length + 1); strcpy(value, map); map += length + 1;

      unsigned long rev;
      memcpy(&rev, map, sizeof(unsigned long)); map += sizeof(unsigned long);
      
      if(PRINTING) {
	printf("key:%s, val:%s, rev:%lu\n", key, value, rev);
	fflush(stdout);
      }
      kvpair_t *new_pair = malloc(sizeof(kvpair_t));
      new_pair->key = key; new_pair->val = value; new_pair->rev = rev;
      new_pair->next = (*d)->table[table_idx];
      new_pair->prev = NULL;
      if( (*d)->table[table_idx] )
	((*d)->table[table_idx])->prev = new_pair;
      ((*d)->table[table_idx]) = new_pair;
    }
  }
  if(PRINTING) {
    printTable( *d );
    fflush(stdout);
  }
}

void datastore_destroy(datastore_t **d) {
  int i;
  kvpair_t *it, *next;
  int fd = open("data/serialized_data.bin", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
  if(fd == -1)
    perror("Error opening fd");
  //Write memory to buffer
  /**
     Scheme : capacity,num_elems,file_size,
              k1,v1,revision1,k2,v2,revision2,...\n
	      ...
   **/
  //  char *buffer = malloc((*d)->file_size); 
  char *buffer = malloc((*d)->file_size);
  char *ptr = buffer;
  memcpy(ptr, &((*d)->capacity), sizeof(int)); ptr += sizeof(int);
  memcpy(ptr, &((*d)->num_elems), sizeof(int)); ptr += sizeof(int);  
  memcpy(ptr, &((*d)->file_size), sizeof(int)); ptr += sizeof(int);

  for(i = 0; i < (*d)->capacity; i++) {
    it = (*d)->table[i];
    while(it) {
      next = it->next;
      int key_len = strlen(it->key) + 1; //Null terminated!
      int val_len = strlen(it->val) + 1;
      memcpy(ptr, it->key, key_len); ptr += key_len;
      memcpy(ptr, it->val, val_len); ptr += val_len;
      memcpy(ptr, &(it->rev), sizeof(unsigned long)); ptr += sizeof(unsigned long);

      free(it->key); free(it->val);
      free(it);
      it = next;
    }
    memcpy(ptr, "\n", 1); ptr += 1;
  }

  if( (*d)->file_size != (ptr-buffer) )
    perror("OUT FILE SIZE IS INCORRECT\n");
  int size = ptr-buffer;

  if(-1 == lseek(fd, size, SEEK_SET))
    perror("lseek error 1");
  write(fd, "", 1);
  if(-1 == lseek(fd, 0, SEEK_SET))
    perror("lseek error 2");
  
  char *map = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if(map == MAP_FAILED)
    perror("Error mmaping file");

  memcpy(map, buffer, size); 

  if(-1 == msync(map, size, MS_SYNC))
    perror("Could not sync file");

  if(-1 == munmap(map, size))
    perror("Could not unmap file");  
  
  close(fd);
  free(buffer);
  for(i = 0; i < NUM_LOCKS; i++)
    pthread_mutex_destroy((*d)->locks + i);
  pthread_mutex_destroy(&resize_lock);
  pthread_mutex_destroy(&datastore_lock);

  free((*d)->table);
  free((*d));
  *d = NULL;
}

kvpair_t *kvpair_find(kvpair_t *root, char *key) {
  if(!root)
    return NULL;
  if(strcmp(key, root->key) == 0)//If they're equal
    return root;
  else
    return kvpair_find(root->next, key);
}

kvpair_t *kvpair_add_to_list(kvpair_t *head, char *key, char *val) {
  kvpair_t *new_head = malloc(sizeof(kvpair_t));
  new_head->key = malloc(strlen(key) + 1); strcpy(new_head->key, key);
  new_head->val = malloc(strlen(val) + 1); strcpy(new_head->val, val);
  new_head->rev = 1;
  new_head->next = head;
  new_head->prev = NULL;
  if(head)
    head->prev = new_head;
  return new_head;
}

void datastore_resize(datastore_t *d) {
  printf("Resizing\n");
  int i, idx;
  kvpair_t *it, *next;
  int new_capacity = d->capacity * CAPACITY_MULTIPLIER;
  kvpair_t **new_table = calloc(new_capacity, sizeof(kvpair_t*));
  
  for(i = 0; i < d->capacity; i++) {
    it = d->table[i];
    while(it) {
      next = it->next;
      idx = hash(it->key) % new_capacity;
      it->prev = NULL;
      it->next = new_table[idx];
      if(new_table[idx])
	new_table[idx]->prev = it;
      new_table[idx] = it;
      it = next;
    }
  }
  free(d->table);
  d->table = new_table;
  d->file_size = d->file_size - d->capacity + new_capacity;
  d->capacity = new_capacity;
}

jsonres_t datastore_add(datastore_t *d, char *key, char *val) {
  jsonres_t res;
  int orig_capacity = d->capacity;
  int idx = hash(key) % orig_capacity;
  int i;

  pthread_mutex_lock(d->locks + idx*NUM_LOCKS/orig_capacity);

  kvpair_t *it;
  int new_idx = hash(key) % d->capacity;
  if(it = kvpair_find(d->table[new_idx], key)) { //If key is already in the table
    res.success = "KEY ALREADY EXISTS";
    pthread_mutex_unlock(d->locks + idx*NUM_LOCKS/orig_capacity);
  } else {
    d->table[new_idx] = kvpair_add_to_list(d->table[new_idx], key, val);

    pthread_mutex_lock(&datastore_lock);
    (d->num_elems)++;
    d->file_size += (strlen(key)+1 + strlen(val)+1 + sizeof(unsigned long));
    pthread_mutex_unlock(&datastore_lock);

    pthread_mutex_unlock(d->locks + idx*NUM_LOCKS/orig_capacity);

    pthread_mutex_lock(&resize_lock);
    if( (double)(d->num_elems) / d->capacity > 0.75) {
      for(i = 0; i < NUM_LOCKS; i++) {
	pthread_mutex_lock(d->locks + i);
      }
      datastore_resize(d);
      for(i = 0; i < NUM_LOCKS; i++) {
	pthread_mutex_unlock(d->locks + i);
      }
    }
    pthread_mutex_unlock(&resize_lock);

    res.success = "true";
  }
  return res;
}

jsonres_t datastore_update(datastore_t *d, char *key, char *val, unsigned long rev) {
  if(PRINTING) {
    printf("UPDATE key:%s, value:%s\n", key, val);
    fflush(stdout);
  }
  jsonres_t res;

  int orig_capacity = d->capacity;
  int idx = hash(key) % orig_capacity;

  pthread_mutex_lock(d->locks + idx*NUM_LOCKS/orig_capacity);

  int new_idx = hash(key) % d->capacity;
  kvpair_t *found_kv = kvpair_find(d->table[new_idx], key);
  if(found_kv) {
    if(found_kv->rev == rev) {
      int new_length = strlen(val);
      (found_kv->rev)++;

      pthread_mutex_lock(&datastore_lock);
      d->file_size -= (strlen(found_kv->val)+1);
      d->file_size += new_length+1;
      pthread_mutex_unlock(&datastore_lock);

      free(found_kv->val);

      found_kv->val = malloc(new_length + 1); strcpy(found_kv->val, val);
      res.success = "true";
      res.rev = found_kv->rev;      

    } else {
      res.success = "REVISION NUMBER DOES NOT MATCH";
    }
  } else {
    res.success = "KEY DOES NOT EXIST";
  }

  pthread_mutex_unlock(d->locks + idx*NUM_LOCKS/orig_capacity);

  if(PRINTING) {
    printTable(d);
    fflush(stdout);
  }
  return res;
}

jsonres_t datastore_get(datastore_t *d, char *key) {
  if(PRINTING) {
    printf("GET key:%s\n", key);
    fflush(stdout);
  }
  jsonres_t res;
  int orig_capacity = d->capacity;
  int idx = hash(key) % orig_capacity;

  pthread_mutex_lock(d->locks + idx*NUM_LOCKS/orig_capacity);
  int new_idx = hash(key) % d->capacity;

  kvpair_t *found_kv = kvpair_find(d->table[new_idx], key);
  if(found_kv) {
    res.success = "true";
    res.value = malloc(strlen(found_kv->val) + 1); strcpy(res.value, found_kv->val);
    res.rev = found_kv->rev;
  } else {
    res.value = NULL;
    res.success = "KEY DOES NOT EXIST";
  }

  pthread_mutex_unlock(d->locks + idx*NUM_LOCKS/orig_capacity);

  return res;
}

jsonres_t datastore_delete(datastore_t *d, char *key) {
  if(PRINTING) {
    printf("DELETE key:%s\n", key);
    fflush(stdout);
  }
  jsonres_t res;
  int orig_capacity = d->capacity;
  int idx = hash(key) % orig_capacity;

  pthread_mutex_lock(d->locks + idx*NUM_LOCKS/orig_capacity);

  int new_idx = hash(key) % d->capacity;
  kvpair_t *found_kv = kvpair_find(d->table[new_idx], key);
  if(found_kv) {
    if(found_kv->prev)
      found_kv->prev->next = found_kv->next;
    else
      d->table[new_idx] = found_kv->next;
    if(found_kv->next)
      found_kv->next->prev = found_kv->prev;
    int file_diff = 0;
    file_diff -= strlen(found_kv->key)+1;
    free(found_kv->key);
    file_diff -= strlen(found_kv->val)+1;
    free(found_kv->val);
    file_diff -= sizeof(unsigned long);
    free(found_kv);

    pthread_mutex_lock(&datastore_lock);
    d->num_elems--;
    d->file_size += file_diff;
    pthread_mutex_unlock(&datastore_lock);


    res.success = "true";
  } else {
    res.success = "KEY DOES NOT EXIST";
  }

  pthread_mutex_unlock(d->locks + idx*NUM_LOCKS/orig_capacity);
  if(PRINTING) {
    printTable(d);
    fflush(stdout);
  }

  //  printf("%s\n", res.success);
  
  return res;
}
