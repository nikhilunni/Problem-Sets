#include <stdio.h>
#include <stdlib.h>

#define BIG_BUFFER 100000

int main(int argc, char* argv[]) {
  FILE* f;
  if(!(f = fopen(argv[argc-1], "r"))) { //Could not load file
    printf("fake: *** No targets specified and no fakefile found. Stop.\n");
    exit(1);
  }

  char buffer[BIG_BUFFER];
  while(fgets(buffer, BIG_BUFFER, f)) {printf("%s", buffer);}
  printf("\n");

  return 0;
}
