#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <time.h>
#include "counters.h"

int main(int argc, char *argv[]) {
  hwCounter_t cl;
  cl.init = false;
  initTicks(cl);

  uint64_t current_time = getTicks(cl);
  printf("Current Time in Ticks %lu\n", current_time);
}
