// Replace "Full name" and "netid" here with your name and netid

// Copyright (C) [Nikhil Unni] ([nunni2]) 2015

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include "mpsortutil.h"

#include <time.h>

#define MAXTHREAD (16)
#define QUEUE_SIZE (256)
#define INIT_MERGE_BUFFER (512)
#define INITIAL_CAPACITY (32)
#define CAPACITY_MULTIPLIER (8)
#define SCRATCH_MULTIPLIER (8)

extern int nthreads, verbose; // defined in main.c
extern char * outfile_name;

static FILE * outfile;
static int* data;
static int nitems;
static int capacity;
static pthread_t tid[MAXTHREAD];

static int finalCapacity;

typedef enum MERGE_STATE_ {
  UNSORTED,
  SORTED
} MERGE_STATE;

typedef struct sorted_list_t_ {
  int start,end;
  MERGE_STATE state;
  struct sorted_list_t_* next;
  struct sorted_list_t_* prev;
} sorted_list_t;

typedef struct task_t_ {
  sorted_list_t* pos;
  int start, end;
} task_t;

static sorted_list_t* head;
static sorted_list_t* tail;
    
task_t* _queue[QUEUE_SIZE];
int _in, _out, _count, _done;

pthread_mutex_t _m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t _cv_full = PTHREAD_COND_INITIALIZER; //Queue is full
pthread_cond_t _cv_empty = PTHREAD_COND_INITIALIZER; //Queue is empty

pthread_mutex_t _chunk_accessor = PTHREAD_MUTEX_INITIALIZER;


//Reader-Writer solution courtesy of http://www.researchgate.net/publication/1871845_Fair_Solution_to_the_Reader-Writer-Problem_with_Semaphores_only
sem_t access;

void _enqueue(task_t*task) {
  pthread_mutex_lock(&_m);
  while(_count >= QUEUE_SIZE) {
    pthread_cond_wait(&_cv_full, &_m);
  }
  _queue[_in] = task;
  _in = (_in+1) % QUEUE_SIZE;
  pthread_cond_signal(&_cv_empty); //If we just added an element, and the old count was 0, signal to all the threads waiting on the queue
  _count++;  
  pthread_mutex_unlock(&_m);  
}

task_t* _dequeue() {
  //The special NULL (finished) stays in the queue
  // Once NULL is returned, dequeue will never block and will always immediately return NULL.
  if(_done) {
    return NULL;
  }
  else {
    pthread_mutex_lock(&_m);
    while(_count <= 0) {
      if(_done) {
	pthread_mutex_unlock(&_m);
	return NULL;
      }
      pthread_cond_wait(&_cv_empty, &_m);
    }
    task_t* out_task = _queue[_out];
    _out = (_out+1) % QUEUE_SIZE;  
    pthread_cond_signal(&_cv_full);
    _count--;
    if(out_task == NULL) {
      _done = 1;
      pthread_cond_broadcast(&_cv_empty);
    }
    pthread_mutex_unlock(&_m);
    return out_task;
  }
}
char* out;
void my_merge(int * data , int * scratch, int start,int mid, int end) {
  if(finalCapacity > 0 && start == 0 && end == finalCapacity) {
    int i = start;
    int j = mid;
    int k = 0;
    while(i < mid && j < end) {
      if(data[i] < data[j]) {
	scratch[k] = data[i++];
	fprintf(outfile,"%d\n", scratch[k]);
	k++;
      } else {
	scratch[k] = data[j++];
	fprintf(outfile,"%d\n", scratch[k]);
	k++;
      }
    }
    while(i < mid) {
      scratch[k] = data[i++];
      fprintf(outfile,"%d\n", scratch[k]);
      k++;
    }
    while(j < end) {
      scratch[k] = data[j++];
      fprintf(outfile,"%d\n", scratch[k]);
      k++;
    }
    if(verbose)
      print_stat(scratch, 0, k);
  } else {
    // mid,end are exclusive when used as end-points
    assert(data && scratch && (start >=0) && (start <= mid) && (mid <= end));
    int i = start;
    int j = mid;
    int k = 0;
    while(i <mid && j < end) {
      scratch[k++] = data[i] < data[j] ? data[i++] : data[j++];
    }
    while(i <mid)
      scratch[k++] = data[i++];
    while(j <end)
      scratch[k++] = data[j++];
  
    // Copy back 
    for(i=0; i<k ; i++)
      data[start + i] = scratch[i];

    if(verbose)
      print_stat(data, start, end);
  }
  
}

static int compare_fn(const void *arg1, const void *arg2) {
  return (*((int*)arg1)) - (*((int*)arg2)); 
}

void _mergeNow(int,int,int,int**,int*, sorted_list_t*);


void addMergeItem(sorted_list_t* pos, int** scratch, int* merge_buffer_size) {
  int canMerge = 0;
  int startFirst, startSecond, endSecond;
  pthread_mutex_lock(&_chunk_accessor);
  if(pos->state == SORTED) {
    sorted_list_t* pos2;
    int len = pos->end - pos->start;
    if((pos->start / len) % 2 == 0) {
      pos2 = pos->next;
      if(pos2 != NULL && pos2->state == SORTED && pos2->end-pos2->start == len) {
	canMerge = 1;
	startFirst = pos->start; startSecond = pos2->start; endSecond = pos2->end;           
	pos->end = pos2->end;
	pos->state = UNSORTED;
	pos2->state = UNSORTED;
	pos->next = pos2->next;
	if(pos2->next != NULL)
	  pos2->next->prev = pos;
	else
	  tail = pos;
	free(pos2);	
      }
    }
    else {
      pos2 = pos->prev;
      if(pos2 != NULL && pos2->state == SORTED && pos2->end-pos2->start == len) {
	canMerge = 1;
	startFirst = pos2->start; startSecond = pos->start; endSecond = pos->end;
	pos->start = pos2->start;
	pos->state = UNSORTED;
	pos2->state = UNSORTED;
	pos->prev = pos2->prev;
	if(pos2->prev != NULL)
	  pos2->prev->next = pos;
	else
	  head = pos;
	free(pos2);	
      }
    }
  }
  pthread_mutex_unlock(&_chunk_accessor);
  if(canMerge) {
    _mergeNow(startFirst, startSecond, endSecond, scratch, merge_buffer_size, pos);
  }
}

void _sort(task_t* sort_task, int** scratch, int* merge_buffer_size, sorted_list_t* pos) {
  int len = sort_task->end - sort_task->start;

  sem_wait(&access);
  qsort(data+sort_task->start, len, sizeof(int), compare_fn);
  if(verbose)
    print_stat(data, sort_task->start, sort_task->end);
  sem_post(&access);

  pos->state = SORTED;
  addMergeItem(pos, scratch, merge_buffer_size);
}

void _mergeNow(int startFirst, int startSecond, int endSecond, int** scratch, int* merge_buffer_size, sorted_list_t* pos) {
  int len = endSecond - startFirst;
  if(*merge_buffer_size < len) {
    *merge_buffer_size = len * SCRATCH_MULTIPLIER;
    *scratch = realloc(*scratch, *merge_buffer_size * sizeof(int));
  }
  sem_wait(&access);
  my_merge(data, *scratch, startFirst, startSecond, endSecond);
  sem_post(&access);

  pos->state = SORTED;
  addMergeItem(pos, scratch, merge_buffer_size);
}

void* _work(void* in) {
  int** scratch = malloc(sizeof(int**));
  *scratch = malloc( INIT_MERGE_BUFFER * sizeof(int) );
  int* merge_buffer_size = malloc(sizeof(int));
  *merge_buffer_size = INIT_MERGE_BUFFER;
  task_t* task;
  while( (task = _dequeue()) ) {
    _sort(task, scratch, merge_buffer_size, task->pos);
    free(task);
  }
  free(merge_buffer_size);
  free(*scratch);
  free(scratch);
  return NULL;
}


int** main_scratch;
int* main_merge_buffer_size;

/**
 * Stream-based fast sort. The stream sort may be faster because you can start processing the data
 * before it has been fully read.
 * Before data arrives, you can pre-create threads and prepared to send output to the given ile
 * @param nthreads number of threads to use including the calling thread (these should created once and reused for multiple tasks)
 * @param verbose whether to print to standard out the number of unique values for each merged segment
 * @param outfile output FILE descriptor (either stdout or a output file)
 */
void stream_init() {
  outfile = open_outfile(outfile_name);
  data = malloc( INITIAL_CAPACITY * sizeof(int) );
  capacity = INITIAL_CAPACITY;

  main_scratch = malloc(sizeof(int**));
  *main_scratch = malloc(INIT_MERGE_BUFFER * sizeof(int));
  main_merge_buffer_size = malloc(sizeof(int));
  *main_merge_buffer_size = INIT_MERGE_BUFFER;
  
  sem_init(&access, 0, nthreads);
  int i;

  for(i = 1; i < nthreads; i++)
    pthread_create(&tid[i], NULL, _work, NULL);
}


/**
 * Additional data has arrived and is ready to be processed in the buffer. 
 * This function may be called multiple times (between stream_init() and stream_en()d).
 * The buffer is re-used for new data, you will need to copy / process the data before returning from this method.
 * @param buffer pointer to the buffer. The buffer contents is only valid for the duration of the call.
 * @param count the number of items in the buffer (256 >= count > 0). This may be less than 256 for the last segment.
*/
task_t* toDo = NULL;

void stream_data(int* buffer, int count) {
  if(toDo != NULL) {
    if(nthreads > 1)
      _enqueue(toDo);
    else {
      _sort(toDo, main_scratch, main_merge_buffer_size, tail);
      free(toDo);
    }
  }
  if(nitems + count > capacity) {
    int k;
    for(k = 0; k < nthreads; k++)
      sem_wait(&access);
    data = realloc(data, capacity * CAPACITY_MULTIPLIER * sizeof(int));
    capacity *= CAPACITY_MULTIPLIER;
    for(k = 0; k < nthreads; k++)
      sem_post(&access);
  }
  int i = 0;
  int start = nitems;
  while(i < count) {
    data[nitems++] = buffer[i++];
  }


  sorted_list_t* newTail;
  pthread_mutex_lock(&_chunk_accessor);    
  if(head == NULL) {
    head = malloc(sizeof(sorted_list_t));
    head->start = 0; head->end = nitems;
    head->state = UNSORTED;
    head->next = NULL;
    head->prev = NULL;
    tail = head;
    newTail = head;
  } else {
    newTail = malloc(sizeof(sorted_list_t));
    newTail->start = start; newTail->end = nitems;
    newTail->state = UNSORTED;
    newTail->next = NULL;
    newTail->prev = tail;

    tail->next = newTail; tail = tail->next;
  }
  pthread_mutex_unlock(&_chunk_accessor);


  task_t* task = malloc(sizeof(task_t));
  task->pos = newTail;
  task->start = start;
  task->end = nitems;
  toDo = task;
}

void writeToFile() {
  int i;
  for(i = 0; i < nitems;i++) {
    fprintf(outfile,"%d\n", data[i]);
  }
  /**
  size_t bytes_expected = nitems*2;
  size_t bytes_written = write(data, 
  **/
}


/**
 * All data has been delivered. Your implementation should now finish writing out sorted data and verbose info.
* The output stream will be closed for you after this call returns
*/
void stream_end() {
  _enqueue(NULL);
  qsort(data+toDo->start, toDo->end-toDo->start, sizeof(int), compare_fn); //Sort last chunk
  toDo->pos->state = SORTED;
  if(verbose)
    print_stat(data, toDo->start, toDo->end);
  free(toDo);


  int i;
  for(i = 1; i < nthreads; i++)
    pthread_join(tid[i], NULL);

  finalCapacity = nitems;

  free(main_merge_buffer_size);
  free(*main_scratch);
  free(main_scratch);

  if(head->next != NULL) {
    int* scratch = malloc(nitems * sizeof(int));
    sorted_list_t* it;
    for(it = tail->prev; it != NULL;) {
      my_merge(data, scratch, it->start, tail->start, tail->end);
      tail->start = it->start;
      sorted_list_t* prev = it->prev;
      free(it);
      it = prev;
    }
    free(scratch);
  }
  else
    writeToFile();
  free(data);
  if(outfile != stdout) 
     fclose(outfile);
}
