#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <limits.h>
#include <pthread.h>

#include "queue.h"

const char* TYPE1 = "heart_beat";
const char* TYPE2 = "blood_sugar";
const char* TYPE3 = "body_temp";

#define STARTED -1
#define FINISHED -2

//the wearable server socket, which all wearables connect to
int wearable_server_fd;

//a lock for your queue sctructure... (use it)
pthread_mutex_t queue_lock_;
pthread_mutex_t num_servers_lock_;
pthread_cond_t cv;
//a queue for all received data... 
queue_t received_data_;

int PRINTING = 0;

int num_servers;

typedef struct SampleData {

  char type_[50];
  int data_;

} SampleData;

int compare (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

int get_type1(void* data) {
  return ((SampleData*)data)->type_[1] == 'e';
}
int get_type2(void* data) {
  return ((SampleData*)data)->type_[1] == 'l';
}
int get_type3(void* data) {
  return ((SampleData*)data)->type_[1] == 'o';
}

/**
   Used to write out the statistics of a given results set (of timestamp_entry's).
   To generate the result set see queue_gather(). fd is the file descriptor to
   which the information is sent out. The type is the type of data that is written out
   (TYPE1, TYPE2, TYPE3). results is the array of timestamp_entrys, and size is 
   the size of that array. NOTE: that you should call method for every type 
   (TYPE1, TYPE2, TYPE3), and then write out the infomration "\r\n" to signify that
   you have finished sending out the results.
*/
void write_results(int fd, const char* type, timestamp_entry* results, int size) {
  long avg = 0;
  int i;

  char buffer[1024];
  int temp_array[size];
  sprintf(buffer, "Results for %s:\n", type);
  sprintf(buffer + strlen(buffer), "Size:%i\n", size);
  for (i = 0;i < size;i ++) {
    temp_array[i] = ((SampleData*)(results[i].data_))->data_;
    avg += ((SampleData*)(results[i].data_))->data_;
  }

  qsort(temp_array, size, sizeof(int), compare);

  if (size != 0) {
    sprintf(buffer + strlen(buffer), "Median:%i\n", (size % 2 == 0) ?
            (temp_array[size / 2] + temp_array[size / 2 - 1]) / 2 : temp_array[size / 2]);
  } else { 
    sprintf(buffer + strlen(buffer), "Median:0\n");
 }

  sprintf(buffer + strlen(buffer), "Average:%li\n\n", (size == 0 ? 0 : avg / size));
  write(fd, buffer, strlen(buffer));
}

/**
   Given an input line in the form <timestamp>:<value>:<type>, this method 
   parses the infomration from the string, into the given timestamp, and
   mallocs space for SampleData, and stores the type and value within
*/
void extract_key(char* line, long* timestamp, SampleData** ret) {
  *ret = malloc(sizeof(SampleData));
  sscanf(line, "%zu:%i:%[^:]%:\\.*", timestamp, &((*ret)->data_), (*ret)->type_);
}
typedef struct wearable_struct_ {
  int fd ;
  int i;
} wearable_struct;
typedef struct waiter_struct_ {
  int start;
  int end;
  int fd;
} waiter_struct;

long *statuses;

int have_to_wait(long timestamp) {
  int i;
  for(i = 0; i < num_servers; i++) {
    if(statuses[i] == STARTED || (statuses[i] != FINISHED && statuses[i] < timestamp)) {
      return 1;
    }
  }
  return 0;
}
//TODO USE WEARABLE_STRUCT
//PASS i, and have array of statuses for each device...
void* wearable_processor_thread(void* args) {
  wearable_struct *input = ((wearable_struct*)args);
  int socketfd = input->fd;
  int idx = input->i;
  SampleData *data;
  long timestamp;
  int subtracted_yet = 0;

  char buffer[64];
  while (read(socketfd, buffer, 64) > 0) {
    extract_key(buffer, &timestamp, &data);
    
    if(PRINTING) {
      printf("Timestamp:%zu, Type:%s, Data:%d\n", timestamp, data->type_, data->data_);
      fflush(stdout);
    }
    statuses[idx] = timestamp;
    pthread_mutex_lock(&num_servers_lock_);
    pthread_cond_broadcast(&cv);
    pthread_mutex_unlock(&num_servers_lock_);

    pthread_mutex_lock(&queue_lock_); //Change to reader-writer later...
    queue_insert(&received_data_, timestamp, data);
    pthread_mutex_unlock(&queue_lock_);
  }
  statuses[idx] = FINISHED;
  pthread_cond_broadcast(&cv);
  close(socketfd);
  return NULL;
}

void print_entries(timestamp_entry* entries, int size) {
  int i;
  for(i = 0; i < size; i++) {
    printf("%s\n", ((SampleData*)(entries[i].data_))->type_);
  }
}

void *waiter_thread(void *args) {
  waiter_struct *in = ((waiter_struct*)args);
  int start = in->start;
  int end = in->end;
  int socketfd = in->fd;
  pthread_mutex_lock(&num_servers_lock_);
  while(have_to_wait(end) > 0) {
    pthread_cond_wait(&cv, &num_servers_lock_);
  }
  pthread_mutex_unlock(&num_servers_lock_);
  pthread_mutex_lock(&queue_lock_);
  int size;
  timestamp_entry* entries;
  entries = queue_gather(&received_data_,start, end, get_type1, &size);
  write_results(socketfd, TYPE1, entries, size);
  free(entries);

  entries = queue_gather(&received_data_,start, end, get_type2, &size);
  write_results(socketfd, TYPE2, entries, size);
  free(entries);

  entries = queue_gather(&received_data_,start, end, get_type3, &size);
  write_results(socketfd, TYPE3, entries, size);
  free(entries);

  write(socketfd, "\r\n", 2);

  pthread_mutex_unlock(&queue_lock_);

}

void* user_request_thread(void* args) {
  int socketfd = ((int)args);
  int i;
  char buffer[64]; memset(buffer, 0, 64);
  int num_waiters = 0;
  int size_waiter_buff = 100;
  pthread_t *waiters = malloc(sizeof(pthread_t) * size_waiter_buff);
  waiter_struct *times = malloc(sizeof(waiter_struct) * size_waiter_buff);
  while(read(socketfd, buffer, 64) > 0) {
    num_waiters++;
    if(num_waiters >= size_waiter_buff) {
      size_waiter_buff *= 2;
      waiters = realloc(waiters, sizeof(pthread_t) * size_waiter_buff);
      times = realloc(times, sizeof(waiter_struct) * size_waiter_buff);
    }      
    char* colon = strstr(buffer, ":");
    *colon = '\0';
    char* endTime = colon+1;
    int start = atoi(buffer);
    int end = atoi(endTime);
    if(PRINTING) {
      printf("Request made : %d-%d\nnum_servers : %d\n", start, end, num_servers); fflush(stdout);
    }
    
    times[num_waiters-1].start = start;
    times[num_waiters-1].end = end;
    times[num_waiters-1].fd = socketfd;
    pthread_create(waiters+num_waiters-1, NULL, waiter_thread, (void*)(times+num_waiters-1));    
  }
  for(i = 0; i < num_waiters; i++)
    pthread_join(waiters[i], NULL);

  free(waiters);
  free(times);

  close(socketfd);
  return NULL;
}

//IMPLEMENT!
//given a string with the port value, set up a 
//serversocket file descriptor and return it
int open_server_socket(const char* port) {
  int s;
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  struct addrinfo hints, *result;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  s = getaddrinfo(NULL, port, &hints, &result); //TODO : Free up memory from getaddrinfo
  if(s != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    exit(1);
  }

  int optval = 1;
  setsockopt(sock_fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

  if(bind(sock_fd, result->ai_addr, result->ai_addrlen) != 0) {
    perror("bind()");
    exit(1);
  }

  if(listen(sock_fd, 40) != 0) {
    perror("listen()");
    exit(1);
  }

  freeaddrinfo(result);
  return sock_fd;
}


void signal_received(int sig) {
  //TODO close server socket, free anything you dont free in main;
  close(wearable_server_fd);
  if(PRINTING) {
    printf("SIGNAL RECEIVED\n");
  }
}


int main(int argc, const char* argv[]) {
  if (argc != 3) {
    printf("Invalid input size\n");
    exit(EXIT_FAILURE);
  }

  signal(SIGINT, signal_received);
  int i, server_thread_size;
  int request_server_fd = open_server_socket(argv[2]);
  wearable_server_fd = open_server_socket(argv[1]);
 
  pthread_t request_thread, *server_threads;
  int request_socket, server_socket;
  request_socket = accept(request_server_fd, NULL, NULL);
  close(request_server_fd);
  pthread_create(&request_thread, NULL, user_request_thread, (void*)request_socket);

  queue_init(&received_data_);
  pthread_mutex_init(&queue_lock_, NULL);
  pthread_mutex_init(&num_servers_lock_, NULL);
  pthread_cond_init(&cv, NULL);

  server_thread_size = 200;
  server_threads = malloc(sizeof(pthread_t) * server_thread_size);

  wearable_struct *thread_inputs = malloc(sizeof(wearable_struct) * server_thread_size);
  statuses = malloc(sizeof(long) * server_thread_size);

  while( (server_socket = accept(wearable_server_fd, NULL, NULL)) != -1) {
    num_servers++;
    if(PRINTING) {
      printf("CONNECTION MADE, num_servers : %d\n", num_servers); fflush(stdout);
    }
    if(num_servers >= server_thread_size) {
      server_thread_size *= 2;
      server_threads = realloc(server_threads, server_thread_size * sizeof(pthread_t) );
      thread_inputs = realloc(thread_inputs, server_thread_size * sizeof(wearable_struct));
      statuses = realloc(statuses, server_thread_size * sizeof(long));
    }
    statuses[num_servers-1] = STARTED;
    thread_inputs[num_servers-1].fd = server_socket;
    thread_inputs[num_servers-1].i = num_servers-1;
    pthread_create(server_threads+num_servers-1, NULL, 
		   wearable_processor_thread, (void*)(thread_inputs+num_servers-1));
  }
  for(i = 0; i < num_servers; i++)
    pthread_join(server_threads[i], NULL);
  pthread_cond_broadcast(&cv);
  pthread_join(request_thread, NULL);
  free(server_threads);
  free(thread_inputs);
  free(statuses);
  pthread_cond_destroy(&cv);
  queue_destroy(&received_data_, 1);
  pthread_mutex_destroy(&queue_lock_);
  pthread_mutex_destroy(&num_servers_lock_);

  return 0;
}
