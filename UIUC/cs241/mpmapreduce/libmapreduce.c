/** @file libmapreduce.c */
/* 
 * CS 241
 * The University of Illinois
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <pthread.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <poll.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "libmapreduce.h"
#include "libds/libds.h"


static const int BUFFER_SIZE = 2048;  /**< Size of the buffer used by read_from_fd(). */


static void update_trie(const char *key, const char *value, trie_t *root, const char*(*reduce)(const char*, const char*)) {
  if( (*key) == 0 ) { //End of string
    if(root->val == NULL) { //No previous value
      root->val = malloc(strlen(value));
      strcpy(root->val, value);
    } else {
      const char *newVal = (*reduce)(root->val, value);
      free(root->val);
      root->val = newVal;
    }
  } else {
    if(root->next[ *key ] == NULL) //We need to extend our trie
      root->next[ *key ] = calloc(1, sizeof(trie_t));
    update_trie(key+1, value, root->next[ *key ], reduce);
  }
}
/**
 * Adds the key-value pair to the mapreduce data structure.  This may
 * require a reduce() operation.
 *
 * @param key
 *    The key of the key-value pair.  The key has been malloc()'d by
 *    read_from_fd() and must be free()'d by you at some point.
 * @param value
 *    The value of the key-value pair.  The value has been malloc()'d
 *    by read_from_fd() and must be free()'d by you at some point.
 * @param mr
 *    The pass-through mapreduce data structure (from read_from_fd()).
 */
static void process_key_value(const char *key, const char *value, mapreduce_t *mr)
{
  update_trie(key, value, mr->root, mr->reduce);
  free(key);
  free(value);
}


/**
 * Helper function.  Reads up to BUFFER_SIZE from a file descriptor into a
 * buffer and calls process_key_value() when for each and every key-value
 * pair that is read from the file descriptor.
 *
 * Each key-value must be in a "Key: Value" format, identical to MP1, and
 * each pair must be terminated by a newline ('\n').
 *
 * Each unique file descriptor must have a unique buffer and the buffer
 * must be of size (BUFFER_SIZE + 1).  Therefore, if you have two
 * unique file descriptors, you must have two buffers that each have
 * been malloc()'d to size (BUFFER_SIZE + 1).
 *
 * Note that read_from_fd() makes a read() call and will block if the
 * fd does not have data ready to be read.  This function is complete
 * and does not need to be modified as part of this MP.
 *
 * @param fd
 *    File descriptor to read from.
 * @param buffer
 *    A unique buffer associated with the fd.  This buffer may have
 *    a partial key-value pair between calls to read_from_fd() and
 *    must not be modified outside the context of read_from_fd().
 * @param mr
 *    Pass-through mapreduce_t structure (to process_key_value()).
 *
 * @retval 1
 *    Data was available and was read successfully.
 * @retval 0
 *    The file descriptor fd has been closed, no more data to read.
 * @retval -1
 *    The call to read() produced an error.
 */
static int read_from_fd(int fd, char *buffer, mapreduce_t *mr)
{
	/* Find the end of the string. */
	int offset = strlen(buffer);

	/* Read bytes from the underlying stream. */
	int bytes_read = read(fd, buffer + offset, BUFFER_SIZE - offset);
	if (bytes_read == 0)
		return 0;
	else if(bytes_read < 0)
	{
		fprintf(stderr, "error in read.\n");
		return -1;
	}

	buffer[offset + bytes_read] = '\0';
	/* Loop through each "key: value\n" line from the fd. */
	char *line;
	while ((line = strstr(buffer, "\n")) != NULL)
	{
		*line = '\0';
		/* Find the key/value split. */
		char *split = strstr(buffer, ": ");
		if (split == NULL)
			continue;

		/* Allocate and assign memory */
		char *key = malloc((split - buffer + 1) * sizeof(char));
		char *value = malloc((strlen(split) - 2 + 1) * sizeof(char));

		strncpy(key, buffer, split - buffer);
		key[split - buffer] = '\0';

		strcpy(value, split + 2);

		/* Process the key/value. */
		process_key_value(key, value, mr);

		/* Shift the contents of the buffer to remove the space used by the processed line. */
		memmove(buffer, line + 1, BUFFER_SIZE - ((line + 1) - buffer));
		buffer[BUFFER_SIZE - ((line + 1) - buffer)] = '\0';
	}

	return 1;
}


/**
 * Initialize the mapreduce data structure, given a map and a reduce
 * function pointer.
 */
void mapreduce_init(mapreduce_t *mr, 
                    void (*mymap)(int, const char *), 
                    const char *(*myreduce)(const char *, const char *))
{	
  mr->map = mymap;
  mr->reduce = myreduce;
  mr->root = calloc( 1, sizeof(trie_t) );
}

typedef struct _map_info {
  int write_fd; 
  void (*map)(int, const char *);
  char* v;
} map_info;

void* map_job(void* in) {
  map_info *info = (map_info*)(in);
  void (*map)(int, const char *) = info->map;
  int write_fd = info->write_fd;
  char* v = info->v;
  (*map)(write_fd, v);
  free(in);
}

void* reduce_job(void* in) {
  mapreduce_t *mr = (mapreduce_t*)(in);
  int size = mr->size;
  char *buffer[size];
  int i;
  for(i = 0; i < size; i++) {
    buffer[i] = malloc(BUFFER_SIZE+1); buffer[i][0] = '\0';
  }
  int more = size;
  while(more) { //While mapper still runs
    struct epoll_event ev;
    epoll_wait(mr->epoll_fd, &ev, 1, -1);
    int out = 1;
    for(i = 0; i < size; i++) { // Find the right buffer
      if(ev.data.fd == mr->fds[i][0]) {
	out = read_from_fd(ev.data.fd, buffer[i], mr);
      }
    }
    if(out == 0) {
      epoll_ctl(mr->epoll_fd, EPOLL_CTL_DEL, ev.data.fd, NULL);
      more--;
    }
  }
  for(i = 0; i < size; i++)
    free(buffer[i]);
}

/**
 * Starts the map() processes for each value in the values array.
 * (See the MP description for full details.)
 */
void mapreduce_map_all(mapreduce_t *mr, const char **values)
{
  int i;
  mr->epoll_fd = epoll_create(10);
  for(i = 0; values[i] != NULL; i++) {}
  mr->size = i;
  mr->fds = malloc(i * sizeof(int*));
  mr->event = calloc(i , sizeof(struct epoll_event));
  for(i = 0; i < mr->size; i++) {
    mr->fds[i] = malloc(2 * sizeof(int));
    pipe(mr->fds[i]);
    mr->event[i].events = EPOLLIN;
    mr->event[i].data.fd = (mr->fds)[i][0];
    epoll_ctl(mr->epoll_fd, EPOLL_CTL_ADD, (mr->fds)[i][0], &(mr->event[i]));
  }

  pthread_create(&(mr->preducer), NULL, reduce_job, mr);
  pid_t pid = fork();
  if(pid == 0) { //Mapper
    pthread_t t[mr->size];
    for(i = 0; i < mr->size; i++) {
      close((mr->fds)[i][0]);
      map_info *info = malloc(sizeof(map_info));
      info->write_fd = (mr->fds)[i][1]; info->map = mr->map; info->v = values[i];
      pthread_create(&(t[i]), NULL, map_job, (void*)(info));
    }
    for(i = 0; i < mr->size; i++)
      pthread_join(t[i], NULL);
    exit(0);
  } else { //Reducer
    for(i = 0; i < mr->size; i++)
      close(mr->fds[i][1]);    
  }  
}


/**
 * Blocks until all the reduce() operations have been completed.
 * (See the MP description for full details.)
 */
void mapreduce_reduce_all(mapreduce_t *mr)
{
  pthread_join(mr->preducer, NULL);
}

const char *trie_get_value(trie_t* root, const char *key) {
  if( *key == 0)
    return root->val;
  else 
    return root->next[*key] == NULL ? NULL : trie_get_value(root->next[*key], key+1);
}

/**
 * Gets the current value for a key.
 * (See the MP description for full details.)
 */
const char *mapreduce_get_value(mapreduce_t *mr, const char *result_key)
{
  const char *val = trie_get_value(mr->root, result_key);
  if(val != NULL) {
    char* out = malloc(strlen(val));
    strcpy(out, val);
    return out;  
  }
  return NULL;
}

void destroy_trie(trie_t *root) {
  if(root == NULL)
    return;

  int i;
  for(i = 0; i < 256; i++)
    destroy_trie(root->next[i]);
  free(root->val);
  free(root);
}

/**
 * Destroys the mapreduce data structure.
 */
void mapreduce_destroy(mapreduce_t *mr)
{
  int i;
  for(i = 0; i < mr->size; i++) {
    free(mr->fds[i]);
  }
  destroy_trie(mr->root);
  free(mr->event);
  free(mr->fds);
}
