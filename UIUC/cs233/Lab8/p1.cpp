// compile with clang++ -o p1 -Wall p1.cpp

#include <stdio.h>
#include <strings.h>

struct string_node_t {
  const char *strings[2];
  int score;
  string_node_t *next;
};

string_node_t *
make_string_node(const char *str1, const char *str2, string_node_t *next) {
  string_node_t *node = new string_node_t;
  node->strings[0] = str1;
  node->strings[1] = str2;
  node->next = next;
  return node;
}

// function that behaves the same as strlen from std library
int 
my_strlen(const char *str) {
  int length = 0;
  while (str[length] != '\0') {
	 length ++;
  }
  return length;
}

const char *
find_longest_string(const string_node_t *node) {
  if (node == NULL) {
	 return NULL;
  }
  const char *str = find_longest_string(node->next);
  int length = (str == NULL) ? 0 : my_strlen(str);
  for (int i = 0 ; i < 2 ; i ++) {
	 int temp_length = my_strlen(node->strings[i]);
	 if (temp_length > length) {
		length = temp_length;
		str = node->strings[i];
	 }
  }
  return str;
}

int
main() {
  string_node_t *string_list = NULL;
  string_list = make_string_node("blah", "foo", string_list);
  string_list = make_string_node("hoopy", "frood", string_list);
  string_list = make_string_node("oxy", "moron", string_list);
  string_list = make_string_node("super", "calafragilistic", string_list);
  string_list = make_string_node("latency", "bandwidth", string_list);

  const char *str = find_longest_string(string_list);
  printf("%s\n", str);
}
