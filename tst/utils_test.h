#ifndef __TEST_H__
#define __TEST_H__

#include "../src/rule_ext.h"
#include "../src/utils.h"
#include "../src/world.h"

#define NB_NEIGHBORS 9
#define MAX_RULE 5
#define MAX_STATE 50

struct position {
    unsigned int x;
    unsigned int y;
};

void afficher_tableau(int n, unsigned int* t);

int comparer_monde(struct world* w1, struct world* w2);

void afficher_tableau_positions(int n, struct position* t);

void print_moves_rule(struct rule* r, unsigned int len_changes, struct position* t);
#endif // __TEST_H__
