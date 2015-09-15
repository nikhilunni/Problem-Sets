// compile with g++ -Wall -O0 main.cpp -o tweak_int
// and run with ./tweak_int

#include <cstdlib>
#include <stdio.h>

struct node_t {
    node_t *left;
    node_t *right;
    int *data;
};
node_t *create_int_ptr_binary_tree(int seed, int depth) {
    if (depth == 0) {
        return NULL;
    }
    srand(seed);

    node_t *root = new node_t;
    root->data = new int;
    *(root->data) = rand() % 100;

    int delta = rand() % 100;
    
    root->left = create_int_ptr_binary_tree(seed + delta, depth - 1);
    root->right = create_int_ptr_binary_tree(seed - delta, depth - 1);

    return root;
}
void print_int_ptr_binary_tree(node_t *root, bool is_root) {
    if (root == NULL) {
        return;
    }

    if (root->data != NULL) {
        printf("%d ", *(root->data));
    } else {
        printf("(null) ");
    }
    
    print_int_ptr_binary_tree(root->left, false);
    print_int_ptr_binary_tree(root->right, false);

    if (is_root) {
        printf("\n");
    }
}

void tweak_int(node_t *root, int save, int spend) {
    if (root == NULL) {
        return;
    }

    if (root->data != NULL) {
        if (*(root->data) != save) {
            save = spend;
            spend = *(root->data);
            *(root->data) = save;
        }
    }

    tweak_int(root->left, save, spend);
    tweak_int(root->right, save, spend);
}
int main() {
    node_t *test0 = create_int_ptr_binary_tree(551, 4);
    tweak_int(test0, 71, *(test0->data));
    print_int_ptr_binary_tree(test0, true);
    node_t *test1 = create_int_ptr_binary_tree(348, 4);
    tweak_int(test1, 30, *(test1->data));
    print_int_ptr_binary_tree(test1, true);
    return 0;
}