#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define BIG_BUFFER 100000
#define NUM_SLOTS 4

typedef struct {
  char* name;
  struct command* next;
  pid_t proc;
} command;

typedef struct {
  command* history; //head of linked list
  command* current; //tail of linked list
  char* toExecute;
} slot;


slot slots[NUM_SLOTS];

void run(char* c, slot* s) {
  char* name = malloc(strlen(c)); strcpy(name, c); //Copy name into new name
  command* next = NULL;
  if(s->current != NULL)
    kill(s->current->proc, SIGKILL); //Kill what's going on in the slot
  //  pid_t proc = execute(c);
  pid_t proc = fork();
  if(proc == 0) {
    system(c);
  }
  else {
    command* newestCommand = malloc(sizeof(command));
    newestCommand->name = name; newestCommand->proc = proc;
    if(s->history == NULL) {
      s->history = s->current = newestCommand;
    }
    else {
      s->current->next = newestCommand;
      s->current = s->current->next;
    }
  } 
}

void queue(char* c, slot* s) {
  if(s->current != NULL && kill(s->current->proc, 0) == 0) {//Process is still running
    char* toExecute = malloc(strlen(c)); strcpy(toExecute, c);
    s->toExecute = toExecute;
  }
  else {
    s->history = NULL;
    run(c,s);
  }
}

pid_t execute(char* c) {
  pid_t out = fork();
  if(out == 0) {
    if(system(c) == -1) {
      perror("Error executing command");
      return NULL;
    }
    return 0;
  }
  return out;
}

void deleteCommand(command* c) {
  if(c == NULL) return;
  free(c->name);
  deleteCommand(c->next);
  free(c);
}

void tearDown() {
  for(int i = 0; i < NUM_SLOTS; i++) {
    slot s = slots[i];
    deleteCommand(s.history); s.history = NULL;
    free(s.toExecute);
  }
}

void printHistory(slot* s) {
  command* history = s->history;

  while(history != NULL) {
    printf("%s\n", history->name);
    history = history->next;
  }
}

int main() {
  char c[BIG_BUFFER];
  while(fgets(c, BIG_BUFFER, stdin) && c[0] != 'q') {
    char* end;
    if(end = strchr(c, '\n'))
      *end = '\0';
    
    switch(c[0])
    {
    case 'r':
      run(c+4, &slots[(int)(c[2]-'0') - 1]); break;
    case 'l':
      printHistory(&slots[(int)(c[2]-'0') - 1]); break;
    case 'w':
      queue(c+4, &slots[(int)(c[2]-'0') - 1]); break;
    }
  }
  
  tearDown();

  return 0;
}
