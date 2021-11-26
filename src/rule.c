#include <assert.h>
#include <stdio.h>

#include "rule.h"
#include "world.h"

enum state {
    EMPTY = 0,
    SAND = 16777215,
    GRASS = 65280,
    RANDOM_COLOR = 4294967295,
    STATE_COUNT = 4,
    FIRST_STATE = EMPTY
};

#define NB_NEIGHBORS 9
#define MAX_RULE 513

/*
#define B 16777215
#define RED 255
#define GREEN 65280
#define BLUE 16711680
#define NB_COLOR 5
*/

struct rule {
    unsigned int pattern[NB_NEIGHBORS]; // another def is possible instead of patterns
    unsigned int len_changes;
    unsigned int change[STATE_COUNT]; // 5 diff color
    unsigned int dx, dy; // vector difining the cell move
};

struct rule rules[MAX_RULE];

void rules_init() // for the rules of life, we have the following patterns :
{
    int tmp = 0;

    for (int i = 0; i < NB_NEIGHBORS; ++i) {
        rules[0].pattern[i] = RANDOM_COLOR;
    }
    rules[0].pattern[4] = EMPTY;

    for (int i = 0; i < MAX_RULE; ++i) {
        rules[i + 1].len_changes = 1; // un choix entre noir et blanc
        tmp = i;
        for (int j = NB_NEIGHBORS; j > 0; --j) {
            if (tmp % 2 == 0) {
                rules[i + 1].pattern[j - 1] = EMPTY;
            } else {
                rules[i + 1].pattern[j - 1] = SAND;
            }
            tmp = tmp / 2;

            if (rules[i + 1].pattern[4] == SAND) {
                if (rules[i + 1].pattern[8] == GRASS) {
                    rules[i + 1].change[0] = GRASS;
                    rules[i + 1].dx = 0;
                } else if (rules[i].pattern[8] == EMPTY) {
                    rules[i + 1].change[0] = SAND;
                    rules[i + 1].dx = 1;
                } else {
                    rules[i + 1].change[0] = rules[i].pattern[4];
                    rules[i + 1].dx = 0;
                }
            } else {
                rules[i].change[0] = rules[i].pattern[4];
            }
            rules[i].dy = 0;
        }
    } // ajouter un convention qui dit que si il y a des couleurs alors redeviennent noires juste apres
}
unsigned int rules_count()
{
    return 512; // the real formule is : 2^(nb of neighbors) for the rule represented by a pattern
}

struct rule* rule_get(unsigned int i)
{
    unsigned int max_rule = rules_count();
    assert(max_rule == 0 || i < max_rule);
    return &rules[i];
}

/** The usal modulo for positive number, for the negative number the function return a positive number like for congruence */
int modulo(int x, int n)
{
    if (x < 0) {
        return n + (x % n);
    } else
        return x % n;
}

/** Give the 8 neighbours of a cell and put them in an array of 9 cells */
void find_neighbors(unsigned int tab[], const struct world* w, unsigned int i, unsigned int j)
{
    for (int m = 0; m < 3; m++) {
        for (int n = 0; n < 3; n++) {
            int idx_l, idx_c; // index of lines and columns
            idx_l = modulo(i + (m - 1), HEIGHT);
            idx_c = modulo(j + (n - 1), WIDTH);
            tab[3 * m + n] = w->t[idx_l * WIDTH + idx_c]; // the formule to transform a Matrix in an array
        }
    }
}

/** Return a booleen considering if two arrays of length n are the same */
int compare_t(int n, const unsigned int t1[], unsigned int t2[])
{
    for (int i = 0; i < n; i++) {
        if (t1[i] != t2[i]) {
            return 0;
        }
    }
    return 1;
}

// une amelioration possible est de tester les voisins 1 a 1 et retourner faux des la premiere incoherence
int rule_match(const struct world* w, const struct rule* r, unsigned int i, unsigned int j)
{
    unsigned int tab[NB_NEIGHBORS];
    find_neighbors(tab, w, i, j);
    return (compare_t(NB_NEIGHBORS, r->pattern, tab));
}

unsigned int rule_num_changes(const struct rule* r)
{
    return r->len_changes;
}

unsigned int rule_change_to(const struct rule* r, unsigned int idx)
{
    if (idx < rule_num_changes(r)) {
        return r->change[idx]; // idx used whith more color
    } else
        return 0; // trouver une autre solution
}

int rule_change_dx(const struct rule* r, unsigned int idx)
{
    return r->dy;
}

int rule_change_dy(const struct rule* r, unsigned int idx)
{
    return r->dx;
}
