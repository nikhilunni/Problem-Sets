#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "counters.h"
#include <time.h>

int *shuffledArray(int N) {
  srand(time(NULL));

  int *out = new int[N];
  for(int i = 0; i < N; i++)
    out[i] = i;
  for(int i = N-1; i >= 0; i--) {
    int j = rand() % (i+1);
    int temp = out[j];
    out[j] = out[i];
    out[i] = temp;    
  }
  return out;
}

int main(int argc, char *argv[]) {
  hwCounter_t cl;
  cl.init = false;
  initTicks(cl);

  printf("[");
  for(int len_arr = 8000; len_arr <= 1000000; len_arr += 10000) {
    int *shuffled_arr = shuffledArray(len_arr);
    int i = 0;
    uint64_t start_time = getTicks(cl);
    for(int count = 0; count < 1048576; count++, i = shuffled_arr[i]) {}
    uint64_t end_time = getTicks(cl);
    printf("(%d,%f),", len_arr, (float)(end_time-start_time) / 1048576);
  }
  printf("]\n");
}
