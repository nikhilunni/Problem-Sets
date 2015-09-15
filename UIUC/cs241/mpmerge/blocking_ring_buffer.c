// Replace "Full name" and "netid" here with your name and netid

// Copyright (C) [Nikhil Unni] ([nunni2]) 2015

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "blocking_ring_buffer.h"

task_t* queue[QUEUE_SIZE];
int in, out, count, done;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv_full = PTHREAD_COND_INITIALIZER; //Queue is full
pthread_cond_t cv_empty = PTHREAD_COND_INITIALIZER; //Queue is empty

/* Adds the task to the queue. If the queue is full this call will block until space is available.
  enqueue 'NULL' when there are no more tasks to execute. */

void enqueue(task_t*task) {
  pthread_mutex_lock(&m);
  while(count >= QUEUE_SIZE) {
    pthread_cond_wait(&cv_full, &m);
  }
  queue[in] = task;
  in = (in+1) % QUEUE_SIZE;
  pthread_cond_signal(&cv_empty); //If we just added an element, and the old count was 0, signal to all the threads waiting on the queue
  count++;  
  pthread_mutex_unlock(&m);  
}

/* Removes the next task from the queue. If there are currently no more items, this call blocks.
 Note if the removed item is null then the null remains on the queue for all future dequeue requests.
 Thus the null task is a poison-pill and can be used to terminate all remaining waiting threads.
*/
task_t* dequeue() {
  //The special NULL (finished) stays in the queue
  // Once NULL is returned, dequeue will never block and will always immediately return NULL.
  if(done) {
    return NULL;
  }
  else {
    pthread_mutex_lock(&m);
    while(count <= 0) {
      if(done) {
	pthread_mutex_unlock(&m);
	return NULL;
      }
      pthread_cond_wait(&cv_empty, &m);
    }
    task_t* out_task = queue[out];
    out = (out+1) % QUEUE_SIZE;  
    pthread_cond_signal(&cv_full);
    count--;
    if(out_task == NULL) {
      done = 1;
      pthread_cond_broadcast(&cv_empty);
    }
    pthread_mutex_unlock(&m);
    return out_task;
  }

  
}
