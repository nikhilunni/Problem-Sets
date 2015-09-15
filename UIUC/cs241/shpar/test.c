#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BIG_BUFFER 2000 //Kinda big buffer
char* lines[10][BIG_BUFFER];
char remaining[10*BIG_BUFFER];

void clear() {
    system("clear");
}

void load_lines(FILE* f) {
  rewind(f);
  int i;
  for(i = 0; i < 10 && fgets(lines[i], BIG_BUFFER, f); i++) {
    //Kill newline
    char* end;
    if(end = strchr(lines[i], '\n'))
      *end = (char)0;
  }
  for(; i < 10; i++)
    lines[i][0] = (char)0;

  char buffer[BIG_BUFFER];
  while(fgets(buffer, BIG_BUFFER, f))
    strcat(remaining, buffer);
  fgets(buffer, BIG_BUFFER, f);
}

void write_back(char* fname) {
  FILE* f;
  if( !(f = fopen(fname, "w")) ) {
    printf("Could not write to file\n");
    return;
  }
  for(int i = 0; i < 10; i++) {
    fprintf(f, "%s\n", lines[i]);
  }
  fprintf(f, "%s", remaining);
  fclose(f);
}

void print() {
  clear();
  for(int i = 0; i < 10; i++)
    printf("%d\t%s\n", i+1, lines[i]);
}

void append(int i, char* str) {
  strcat(lines[i], str);
}

void find_all(char* str) {
  clear();
  for(int i = 0; i < 10; i++) {
    char* c1 = str;
    char* c2 = lines[i];
    char* start;
    int match = 0;
    int done = 0;
    for(;*c2; c2++) { //FSM for string matching, essentially
      if(!*c1) {//Reached the end of our FSM
	char* iter;
	printf("%d\t",i+1);
	for(iter = lines[i]; iter != c2-(c1-str); iter++) printf("%c", *iter); //Print up to our found pattern
	printf("<");
	for(char* temp = str; *temp; temp++, iter++) printf("%c", *temp);
	printf(">");
	for(; *iter; iter++) printf("%c", *iter);
	printf("\n");
	c1 = str;
	match = 0;
	continue;
      }
      if(*c2 == *c1) { //If match
	if(!match)
	  match = 1;
	c1++;
      }
      else {
	if(match) {
	  match = 0;
	}
	c1 = str;
      }
    }
    if(!*c1) {//In case the line ends with the pattern
      char* iter;
      printf("%d\t",i+1);
      for(iter = lines[i]; iter != c2-(c1-str); iter++) printf("%c", *iter); //Print up to our found pattern
      printf("<");
      for(char* temp = str; *temp; temp++, iter++) printf("%c", *temp);
      printf(">");
      for(; *iter; iter++) printf("%c", *iter);
      printf("\n");
    }
  }
}

int main(int argc, char* argv[]) {
  FILE* f;
  if (!(f = fopen(argv[argc-1], "r"))) { //Could not load file
    printf("Could not open %s\n", argv[argc-1]);
    return -1;
  }
  load_lines(f);
  fclose(f);
  char c[BIG_BUFFER];
  while(fgets(c, BIG_BUFFER, stdin) && c[0] != 'q') {
    //Kill newline
    char* end;
    if(end = strchr(c, '\n'))
      *end = (char)0;

    switch(c[0]) {
    case 'p':
      print(); break;
    case 'a':
      if(c[3] == ' ')
	append(c[2]-'0'-1 , c+4);
      else
	append(9, c+5); //No two digits other than line 10 allowed!!
      break;
    case '/':
      find_all(c+2); break;
    case 'w':
      write_back(argv[argc-1]); break;
    }
  }
  clear();
  printf("Bye!!!\n");
  return 0;
}
