// Replace "Full name" and "netid" here with your name and netid

// Copyright (C) [Nikhil Unni] ([nunni2]) 2015

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include "mpsortutil.h"
#include "blocking_ring_buffer.h"

/*
  A reasonably fast queue-based solution.
*/
#define MAXTHREAD (16)
#define MSG(msg) fprintf(stderr,"%s\n",msg);

// Defined in main.c
extern int verbose;
extern int nthreads;


static int nitems;  
static int *data;
static int *sorted_info;
static pthread_t tid[MAXTHREAD];
static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;


static int compare_fn(const void *arg1, const void *arg2) {
  return (*((int*)arg1)) - (*((int*)arg2)); 
}


void create_tasks(task_t*parent, int start, int end) { 
  task_t* task = malloc(sizeof(task_t));
  task->start = start;
  task->end = end;
  task->completed_child_tasks = 0;
  task->parent = parent;
  
  int mid = (end + start) / 2;
  int len = (end - start);
  if(len > 256) {
    create_tasks(task,  start,  mid);
    create_tasks(task,  mid, end);
  } else {
    enqueue(task);
  }
}
void do_task(int*scratch, task_t* task);

void child_finished(int* scratch, task_t* task) {
  if(task == NULL) return;
  pthread_mutex_lock(&m);
  int done = ++ (task->completed_child_tasks);
  pthread_mutex_unlock(&m);
  assert(done>0 && done<3);
  
  if(done == 2) {
    do_task(scratch, task);
  }
}

void do_task(int*scratch, task_t* task) {
  int start = task->start;
  int end = task->end;  
  int midpt = (start + end)/2;
  int len = end - start;

  
  if(len <=256) {
    qsort(data +start,len,sizeof(int), compare_fn);
  } else {
    simple_merge(data, scratch, start, midpt, end);
  }
  if(verbose)
    print_stat(data,start,end);
     
  if(task->parent != NULL)
    child_finished(scratch, task->parent);
  else
    enqueue(NULL);

  free(task);
}

void* worker_func(void* arg) {
  int* scratch = malloc( nitems * sizeof(int) );
  task_t * task;
  while( (task = dequeue()) )  {
    do_task(scratch, task);
  }
  free(scratch);
  return NULL;
}


void my_threaded_mergesort(int* _data,int _nitems) {
  
  data = _data;
  nitems = _nitems;
  int i;
  for(i = 1; i < nthreads; i++) {
    pthread_create(&tid[i], NULL, worker_func, NULL);
  }  
  create_tasks(NULL,  0, nitems );
  worker_func( NULL );  

  for(i=1;i < nthreads; i++) { 
    pthread_join(tid[i], NULL);   
  }
  
}
