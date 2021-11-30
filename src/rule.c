#include <assert.h>
#include <stdio.h>

#include "rule.h"
#include "utils.h"
#include "world.h"

enum state;

#define NB_NEIGHBORS 9
#define MAX_RULE 19684

#define B 16777215
#define RED 255
#define GREEN 65280
#define BLUE 16711680
#define NB_COLOR 5
#define MAX_CHANGES 100

struct rule {
    unsigned int pattern[NB_NEIGHBORS]; // another def is possible instead of patterns
    unsigned int len_changes;
    unsigned int change[MAX_CHANGES]; // 5 diff colors
    unsigned int dx[MAX_CHANGES]; // vector defining the cell move
    unsigned int dy[MAX_CHANGES];
};

struct rule rules[MAX_RULE];

unsigned int num_rules = 0;

void gen_pattern(int i, int idx_rule)
{
    int tmp = i;
    for (int j = NB_NEIGHBORS; j > 0; --j) {
        if (tmp % 3 == 0) {
            rules[idx_rule].pattern[j - 1] = EMPTY;
        } else if (tmp % 3 == 1) {
            rules[idx_rule].pattern[j - 1] = SAND;
        } else {
            rules[idx_rule].pattern[j - 1] = GRASS;
        }
        tmp = tmp / 3;
    }
}
void rules_init() // for the rules of life, we have the following patterns :
{
    int idx_rule = 1;
    rules[0].len_changes = 1;
    for (int i = 0; i < NB_NEIGHBORS; ++i) {
        rules[0].pattern[i] = RANDOM_COLOR;
    }
    // create a rule that change a every color in black(EMPTY)
    rules[0].pattern[4] = RANDOM_COLOR;
    rules[0].change[0] = EMPTY;
    rules[0].dx[0] = 0;
    rules[0].dy[0] = 0;

    for (int i = 1; i < MAX_RULE + 1; ++i) {
        rules[idx_rule].len_changes = 1; // un choix entre noir et blanc
        gen_pattern(i, idx_rule);
        if (rules[idx_rule].pattern[4] == SAND) {
            if (rules[idx_rule].pattern[7] == GRASS && rules[idx_rule].pattern[5] == GRASS && rules[idx_rule].pattern[3] == GRASS) {
                rules[idx_rule].len_changes = 1;
                rules[idx_rule].change[0] = GRASS;
                rules[idx_rule].dx[0] = 0;
                rules[idx_rule].dy[0] = 0;
                ++idx_rule;
            } else if (rules[idx_rule].pattern[7] == EMPTY) {
                rules[idx_rule].len_changes = 1;
                rules[idx_rule].change[0] = SAND;
                rules[idx_rule].dx[0] = 1;
                rules[idx_rule].dy[0] = 0;
                ++idx_rule;
            } else if (rules[idx_rule].pattern[7] == SAND) {
                if (rules[idx_rule].pattern[6] == EMPTY && rules[idx_rule].pattern[8] != EMPTY) {
                    rules[idx_rule].len_changes = 1;
                    rules[idx_rule].dy[0] = -1;
                } else if (rules[idx_rule].pattern[6] != EMPTY && rules[idx_rule].pattern[8] == EMPTY) {
                    rules[idx_rule].len_changes = 1;
                    rules[idx_rule].dy[0] = 1;
                } else if (rules[idx_rule].pattern[6] == EMPTY && rules[idx_rule].pattern[8] == EMPTY) {
                    rules[idx_rule].len_changes = 2;
                    rules[idx_rule].change[1] = SAND;
                    rules[idx_rule].dx[1] = 0;
                    rules[idx_rule].dy[0] = 1;
                    rules[idx_rule].dy[1] = -1;
                } else {
                    rules[idx_rule].len_changes = 1;
                    rules[idx_rule].dx[0] = 0;
                    rules[idx_rule].dy[0] = 0;
                }
                rules[idx_rule].change[0] = SAND;
                rules[idx_rule].dx[0] = 0;
                ++idx_rule;
            }
        } // ajouter un convention qui dit que si il y a des couleurs alors redeviennent noires juste apres
    }
    num_rules = idx_rule;
}

unsigned int rules_count()
{
    return num_rules; // the real formule is : 2^(nb of neighbors) for the rule represented by a pattern
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
int compare_patterns(int n, const unsigned int t_r[], unsigned int t_w[])
{
    for (int i = 0; i < n; i++) {
        if (t_r[i] != RANDOM_COLOR) {
            if (t_r[i] != t_w[i]) {
                return 0;
            }
        }
    }
    return 1;
}

// une amelioration possible est de tester les voisins 1 a 1 et retourner faux des la premiere incoherence
int rule_match(const struct world* w, const struct rule* r, unsigned int i, unsigned int j)
{
    unsigned int tab[NB_NEIGHBORS];
    find_neighbors(tab, w, i, j);
    return (compare_patterns(NB_NEIGHBORS, r->pattern, tab));
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
    unsigned int max_change = rule_num_changes(r);
    assert(max_change == 0 || idx < max_change);
    // fprintf(stderr, "dx: %d \n", r->dx[idx]);
    return r->dx[idx];
}

int rule_change_dy(const struct rule* r, unsigned int idx)
{
    unsigned int max_change = rule_num_changes(r);
    assert(max_change == 0 || idx < max_change);
    return r->dy[idx];
}
