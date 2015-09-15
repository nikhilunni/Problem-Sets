#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define BIG_BUFFER 100000

void executeCommands(FILE* f, char* target) {
  rewind(f);

  char buffer[BIG_BUFFER];
  int targetLength = strlen(target);
  char targetLookout[targetLength+3];
  strcpy(targetLookout, target); 
  targetLookout[targetLength] = ':'; 
  targetLookout[targetLength+1] = '\n'; 
  targetLookout[targetLength+2] = (char)0;

  char* fileEnd;
  //  while(strcmp (targetLookout, fileEnd=fgets(buffer, BIG_BUFFER, f)) != 0) {} //Find target
  while((fileEnd=fgets(buffer, BIG_BUFFER, f)) && strcmp(fileEnd, targetLookout) != 0) {}

  if(!fileEnd) {
    printf("Cannot build %s\n", target);
    exit(1);
  }

  printf("Found %s target\n", target);
  
  pid_t proc;
  int status;
  while(strcmp ("\n", fgets(buffer, BIG_BUFFER, f)) != 0) {
    proc = fork();
    if(proc == 0) { //It's alive!!!!!
      printf("Running %s", buffer+1);
      if (execlp("bash", "bash", "-c", buffer, (char*)0) == -1) {
	printf("Error running %s", buffer+1);
      }
    }
    else
      waitpid(proc, &status, 0);
  }
}

void interrupted(int signal) {
  printf("Interrupted by a signal\n");
  exit(1);
}

int main(int argc, char* argv[]) {
  if(argc != 2) {
    printf("Please enter only 1 target\n");
    exit(1);
  }
  
  signal(SIGINT, interrupted);

  FILE* f;
  if(!(f = fopen("Fakefile", "r"))) { //Could not load file
    printf("fake: *** No targets specified and no fakefile found. Stop.\n");
    exit(1);
  }

  executeCommands(f, argv[argc-1]);
  fclose(f);

  //  perror("echo");
  return 0;
}
