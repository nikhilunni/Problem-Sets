// compile with clang++ -o p2 -Wall p2.cpp

#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <stdio.h>

/**************************
 * Functions to implement *
 **************************/

struct person_t {
    uint8_t age;
    int salary;
};

struct quinary_tree_t {
    person_t ** persons;
    quinary_tree_t * children[5];
};

struct stats_t {
    uint8_t oldest;
    uint8_t youngest;
    int total_salary;
    int average_salary;
};

int compute_stats(const quinary_tree_t * root, stats_t * stats) {
    if (root == NULL) {
        return 0;
    }

    int population = 0;
    for (int i = 0; i < 5; ++i) {
        population += compute_stats(root->children[i], stats);
    }

    if (root->persons != NULL) {
        for (person_t ** person = root->persons; *person != NULL; ++person) {
            ++population;
            stats->total_salary += (*person)->salary;
            uint8_t person_age = (*person)->age;
            if (person_age > stats->oldest) {
                stats->oldest = person_age;
            }
            if (person_age < stats->youngest) {
                stats->youngest = person_age;
            }
        }
    }

    return population;
}


/****************
 * Testing code *
 ****************/

person_t * make_person(uint8_t age, int salary) {
    person_t * person = new person_t;
    person->age = age;
    person->salary = salary;
    return person;
}

quinary_tree_t * simple_tree() {
    quinary_tree_t * tree = new quinary_tree_t(); // parentheses to zero-initialize
    tree->persons = new person_t *[5];
    tree->persons[0] = make_person(32, 60000);
    tree->persons[1] = make_person(47, 40000);
    tree->persons[2] = make_person(22, 16000);
    tree->persons[3] = make_person(131, 4000);
    tree->persons[4] = NULL;
    return tree;
}

quinary_tree_t * medium_tree() {
    quinary_tree_t * tree = new quinary_tree_t;
    tree->children[0] = NULL;
    tree->children[1] = NULL;
    tree->children[2] = simple_tree();
    tree->children[3] = NULL;
    tree->children[4] = NULL;

    tree->children[2]->children[0] = simple_tree();
    tree->children[2]->children[4] = simple_tree();

    tree->persons = new person_t *[3];
    tree->persons[0] = make_person(15, 10000);
    tree->persons[1] = make_person(49, 50000);
    tree->persons[2] = NULL;
    return tree;
}

quinary_tree_t * complex_tree() {
    quinary_tree_t * tree = new quinary_tree_t;
    for (int i = 0; i < 5; ++i) {
        tree->children[i] = medium_tree();
    }

    tree->children[1]->children[3] = tree->children[4]->children[2];
    tree->children[4]->children[2] = NULL;

    tree->children[1]->children[3]->persons[0]->salary = 10000;
    tree->children[3]->children[2]->persons[1]->salary = 20000;
    tree->children[0]->children[2]->children[4]->persons[3]->age = 137;

    tree->persons = NULL;
    return tree;
}

void compute_stats_wrapper(const quinary_tree_t * tree, stats_t * stats) {
    int population = compute_stats(tree, stats);
    if (population == 0) {
        stats->average_salary = 0;
    } else {
        stats->average_salary = stats->total_salary / population;
    }
}

int main() {
    stats_t stats = stats_t(); // to zero-initialize
    stats.youngest = UINT8_MAX;

    //quinary_tree_t * tree = simple_tree();
    //quinary_tree_t * tree = medium_tree();
    quinary_tree_t * tree = complex_tree();

    compute_stats_wrapper(tree, &stats);
    printf("oldest: %u, youngest: %u, total_salary: %d, average_salary: %d\n",
           stats.oldest, stats.youngest, stats.total_salary, stats.average_salary);
}
