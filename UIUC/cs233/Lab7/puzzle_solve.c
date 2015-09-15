#include <stdio.h>
#include <strings.h>

int rotate_amt = 10;
char g_str1[20] = "ABCDEFGABCABCHHIIJJ";
char g_str2[20] = "ABCHHIIJJABCDEFGABC";

// function that behaves the same as strlen from std library
int 
my_strlen(const char *str) {
  int length = 0;
  while (str[length] != '\0') {
	 length ++;
  }
  return length;
}

// function that behaves the same as strcmp from std library
int 
my_strcmp(const char *str1, const char *str2) {
  int i = 0;

  while (1) {
	 char c1 = str1[i];
	 char c2 = str2[i];
	 
	 if (c1 != c2) {  
		// if the characters are not equal, return the difference
		return c1 - c2; 
	 }
	 if (c1 == '\0') { 
		// if we the end of a string, then we hit the end of both
		// return 0 to indicate that the strings match
		return 0;       
	 }
	 // go on to the next character
	 i ++;             
  }
}

// Move every character of the string 1 closer to the beginning, except the first
// character which goes to the end.
void
rotate_string_in_place(char *str) {
  int length = my_strlen(str);
  char was_first = str[0];
  
  for (int i = 1 ; i < length ; i ++) {
	 char c = str[i];
	 str[i-1] = c;
  }

  str[length - 1] = was_first;
}

void
rotate_string_in_place_fast(char *str) {
  int length = my_strlen(str);

  // remember the very first character
  char was_first = str[0];

  // we're going to tell C that we want to operate on
  // our array of characters _as if_ it was an array of ints
  int *str_as_array_of_ints = (int *)str;
  int length_in_ints = length / 4; // this rounds down

  for (int i = 0 ; i < length_in_ints ; i ++) {
	 // using unsigneds so I get the correct kind of right shift
    unsigned first_word = str_as_array_of_ints[i];
	 unsigned second_word = str_as_array_of_ints[i+1];
	 unsigned combined_word = (first_word >> 8) | (second_word << 24);
	 str_as_array_of_ints[i] = combined_word;
  }

  for (int i = length_in_ints*4 + 1 ; i < length ; i ++) {
	 char c = str[i];
	 str[i-1] = c;
  }

  str[length - 1] = was_first;
}

// Given two strings, determine if one is a rotated version of the other, and if
// so, return the amount that the string was rotated.  If they aren't rotated 
// versions of each other, then return -1.
int
puzzle_solve(const char *str1, char *str2) {
  int length = my_strlen(str1);
  
  for (int i = 0 ; i < length ; i ++) {
	 if (my_strcmp(str1, str2) == 0) {
		return i;
	 }
	
	 rotate_string_in_place(str2);
//	 rotate_string_in_place_fast(str2);
  }
  return -1;
}

int 
main() {
  // test that my_strlen behaves the same as strlen
  int len1 = strlen(g_str1);
  int len2 = my_strlen(g_str1);
  printf("%d %d\n", len1, len2);
  
  // test the puzzle solving routine
  printf("%s\n", g_str1);
  printf("%s\n", g_str2);
  int rotate_amount = puzzle_solve(g_str2, g_str1);
  printf("rotate_amount is %d (should be %d)\n", rotate_amount, rotate_amt);
  
  return 0;
}
