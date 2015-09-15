// Original file by Lawrence Angrave 2015
// Changes to this file will be ignored when your project is graded

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include "mpsortutil.h"
#include "blocking_ring_buffer.h"

static pthread_t tid1,tid2,tid3,tid4;

static int ip, ic; // producer consumer counts

static pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

#define NTASK (10001)
task_t tasks[NTASK];

int counter;
void * test1_thread(void* unused) {
  while(counter ++ < 80)  dequeue(); 
  return NULL;
}


int test1() {
  puts("Test 1:");
  // Queue size should be 64 entries. Should be able to enqueue 63 entries without blocking 
   for(int i=1; i < 64; i++)
      enqueue( & tasks[i]);
    
  // Pull two tasks off the quueue
   task_t *t= dequeue();
   assert(t && t->start == 1);
   
   t= dequeue();
   assert(t && t->start == 2);
   
   // Pull 81 tasks using a background queue
   pthread_create(&tid1, NULL, test1_thread,NULL);
   sleep(1);
   assert(counter == 62);
   
   for(int i=65; i < 125; i++)
     enqueue( & tasks[i]);
     
   pthread_join(tid1, NULL);
   assert(counter == 81);
   
   t= dequeue();
   assert(t && t->start == 84);
   
   puts("Test 1 passed");
   return 0;
}

void* test2_consume(void*unused) {
  sleep(1); // Let producer get ahead
  
  for(ic=1; ic < 3000; ic++) {
     // Don't enqueue NULL (0) as this poisons the queue
    task_t *t= dequeue();
    assert(t && t->start == ic);
    
    pthread_mutex_lock(&m);
    if(ip == 2000 && ic>=2000) pthread_cond_signal(&cv);
    pthread_mutex_unlock(&m);
    
  }
  return NULL;
}

void* test2_produce(void*unused) {
  for(ip = 1; ip < 3000; ip++) {
    enqueue( & tasks[ip]);  
    
    pthread_mutex_lock(&m);
    while(ip == 2000 && ic < 2000)
      pthread_cond_wait(&cv, &m);  // Let consumer catch up
    pthread_mutex_unlock(&m);
  }
  return NULL;
}


// ---- TEST 3
int test2() {
  puts("Test 2:");
  pthread_create(&tid1,0, test2_produce, NULL);
  pthread_create(&tid2,0, test2_consume, NULL);
  puts("Test 2, waiting on producer...");
  pthread_join(tid1,NULL);
  puts("Test 2, waiting on consumer...");
  pthread_join(tid2,NULL);
  puts("Test 2 passed");
  return 0;
}

// ---- TEST 3
int test3() {
  puts("Test 3:");
  puts("Test 3, enqueueing 64 tasks...");
  for(ip=1; ip < 64; ip++)
     enqueue( & tasks[ip]);
  puts("Test 3, dequeing 64 tasks...");
  for(ic=1; ic < 64; ic++) {
    task_t *t = dequeue();
    assert(t && t->start == ic);
  }
  puts("Test 3, enqueueing 'poison-pill' NULL task");
   enqueue((task_t*) NULL);
  puts("Test 3, dequeueing NULL task (should never block)");
  for(int i = 0; i < NTASK;i++) {
    assert( dequeue() == NULL);
  }
  puts("Test 3 passed");
  return 0;
}

// ---- TEST 4
  
int producer_running = 2;

long sum;
int producer_started;
  
void * test4_produce(void*arg) {
  puts("Producer starting");
  producer_started++;
  
  for(int i=1; i < NTASK; i++)  {
    enqueue(& tasks[i] );
    //write(1,"p",1);
  }
     
  pthread_mutex_lock(&m);
  producer_running --;
  // Am I the last consumer thread to finish? If so signal the other waiting threads
  if(producer_running ==0) {
    enqueue((task_t*) NULL); // send the poison pill message
    pthread_cond_broadcast(&cv);
  }
  else 
    while(producer_running)  // I'm not the last, so keep waiting
      pthread_cond_wait(&cv, &m);
  pthread_mutex_unlock(&m);
  puts("Test 4, producer quiting");
  return NULL;
}
int total_consume_count;

void * test4_consume(void*unused) {
  int value;
  int count =0;
  
  while(!producer_started ) sleep(1);
  
  puts("Test4, consumer starting up");
  
  task_t * t;
  while((t = dequeue())) {
    assert(t && t>= tasks && t< tasks + NTASK);
    pthread_mutex_lock(&m);
    int value = t->start;
    sum += value;
    pthread_mutex_unlock(&m);
    if( ++ count > 20001) {
      fprintf(stderr,"Consumer Got too many values\n"); 
      exit(1); 
    }
  }
  printf("Test 4, consumer got %d values\n", count);
  pthread_mutex_lock(&m);
  total_consume_count += count;
  
  pthread_mutex_unlock(&m);
  puts("Test 4, consumer: NULL value-> quitting");
  return NULL;
}



int test4() {
  puts("Test 4:");
  pthread_create(&tid1,0, test4_produce, NULL);
  pthread_create(&tid2,0, test4_produce, NULL);
  pthread_create(&tid3,0, test4_consume, NULL);
  pthread_create(&tid4,0, test4_consume, NULL);


  puts("Test 4, waiting on producer 1...");
  pthread_join(tid1,NULL);
  puts("Test 4, waiting on producer 2...");
  pthread_join(tid2,NULL);
  puts("Test 4, waiting on consumer 1...");
  pthread_join(tid3,NULL);
  puts("Test 4, waiting on consumer 2...");
  pthread_join(tid4,NULL);
  printf("Test 4, total consumed  %d values\n", total_consume_count );
  printf("Test 4, total sum %ld values\n", sum );

  // Sum of integers = N (N+1) / 2 
  // (and we have every integer 1..10000 twice)
  assert(sum == 100010000L);
  puts("Test 4 passed");
  return 0;
}


int main(int argc, char** argv) {
  for( int i=0; i < NTASK;i++)
     tasks[i].start = i;
  
  alarm(4);
  
  int doTest = argv[1] ? atoi( argv[1]) : 0;
  if(doTest==1) { exit( test1()); }
  if(doTest==2) { exit( test2()); }
  if(doTest==3) { exit( test3()); }
  if(doTest==4) { exit( test4()); }
  printf("Usage: %s 1|2|3|4\n", argv[0]);
  exit(1);
  
}
