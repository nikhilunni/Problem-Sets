#include "stdio.h"
#include "stdlib.h"
#include <string.h>


//Double free
void gotcha1() {
  char* str = (char*)malloc(5 * sizeof(char));
  free(str);
  printf("Still ok\n");
  free(str);
  //Crashes!!
}

//Uninitialized heap memory
void gotcha2() {
  char* str = (char*)malloc(5 * sizeof(char));
  str[0] = 'a';
  free(str);
  printf("%s\n", str);
}


void gotcha3() {
  char* str = (char*)malloc(5 * sizeof(char));
  printf("%c\n", str[0]);
}
void gotcha4() {
  int a;
  int b = a;
  int c = a+b+4;
  printf("%d\n", c);
}
void gotcha5() {
  for(int i = 0; i < 5; i++); printf("Whoops\n");
}

void gotcha6() {
  char* str = "Hello world";
  strcpy(str, "Hi");
  printf("%s",str);
}

int main() {
  //gotcha1(); (It crashes)
  //  gotcha2();
  //  gotcha3();
  // gotcha4();
  // gotcha5();
  // gotcha6();
  int x = 4;
  for(int* i = &x; i < &x+1000; ++i)
    printf("%d\n",*i);
  return 0;
}
