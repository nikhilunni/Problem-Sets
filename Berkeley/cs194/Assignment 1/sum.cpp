#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int n = 10000;//atoi(argv[1]);
  
  long long sum = 0;
  for(long long i = 0; i < n; i++) {
    sum += i;
  }
//  printf("%lld\n", sum);
}
