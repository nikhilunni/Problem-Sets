// compile with g++ -Wall -O0 main.cpp -o increment_vals
// and run with ./increment_vals

#include <cstdlib>
#include <stdio.h>


int *create_int_array(int seed, int length) {
    srand(seed);

    int *arr = new int[length];
    for (int i = 0; i < length; i++) {
        arr[i] = rand() % 100;
    }
    return arr;
}
int **create_int_ptr_array(int seed, int length) {
    srand(seed);

    int **arr = new int*[length];
    for (int i = 0; i < length; i++) {
        arr[i] = new int;
        *arr[i] = rand() % 100;
    }
    return arr;
}
void print_int_array(int *arr, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void increment_vals(int **A, int *vals, int length) {
    for (int i = 0; i < length; i += 2) {
        vals[i] = *A[i] + 17;
    }
}
int main() {
    int **test0_A = create_int_ptr_array(819, 6);
    int *test0_vals = create_int_array(630, 6);
    increment_vals(test0_A, test0_vals, 6);
    print_int_array(test0_vals, 6);
    int **test1_A = create_int_ptr_array(371, 4);
    int *test1_vals = create_int_array(293, 4);
    increment_vals(test1_A, test1_vals, 4);
    print_int_array(test1_vals, 4);
    return 0;
}