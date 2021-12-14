#include <assert.h>
#include <stdio.h>

#include "rule_ext.h"

#include "utils.h"
#include "world.h"

struct rule rules[MAX_RULE];

void rules_init() // règles pour générer un tas de sable
{
    for (int idx_rule = 0; idx_rule < MAX_RULE; ++idx_rule) {
        for (int i = 0; i < 6; ++i) {
            if (i != 4) {
                rules[idx_rule].pattern[i] = RANDOM_COLOR;
            }
        }

        if (idx_rule == 0) {
            rules[idx_rule].len_changes = 1;
            for (int i = 4; i < 9; ++i) {
                rules[idx_rule].pattern[i] = RANDOM_COLOR;
            }
            rules[idx_rule].next_state[0].next_color = EMPTY;
            rules[idx_rule].next_state[0].dx = 0;
            rules[idx_rule].next_state[0].dy = 0;
        } else {
            rules[idx_rule].pattern[4] = SAND;
            switch (idx_rule) {
            case 1:
                rules[idx_rule].len_changes = 1;
                rules[idx_rule].pattern[6] = RANDOM_COLOR;
                rules[idx_rule].pattern[7] = EMPTY;
                rules[idx_rule].pattern[8] = RANDOM_COLOR;
                rules[idx_rule].next_state[0].next_color = SAND;
                rules[idx_rule].next_state[0].dx = 1;
                rules[idx_rule].next_state[0].dy = 0;
                break;
            case 2:
                rules[idx_rule].len_changes = 1;
                rules[idx_rule].pattern[6] = EMPTY;
                rules[idx_rule].pattern[7] = SAND;
                rules[idx_rule].pattern[8] = SAND;
                rules[idx_rule].next_state[0].next_color = SAND;
                rules[idx_rule].next_state[0].dx = 0;
                rules[idx_rule].next_state[0].dy = -1;
                break;
            case 3:
                rules[idx_rule].len_changes = 2;
                rules[idx_rule].pattern[6] = EMPTY;
                rules[idx_rule].pattern[7] = SAND;
                rules[idx_rule].pattern[8] = EMPTY;
                rules[idx_rule].next_state[0].next_color = SAND;
                rules[idx_rule].next_state[1].next_color = SAND;
                rules[idx_rule].next_state[0].dx = 0;
                rules[idx_rule].next_state[0].dy = 1;
                rules[idx_rule].next_state[1].dx = 0;
                rules[idx_rule].next_state[1].dy = -1;
                break;
            case 4:
                rules[idx_rule].len_changes = 1;
                rules[idx_rule].pattern[6] = SAND;
                rules[idx_rule].pattern[7] = SAND;
                rules[idx_rule].pattern[8] = EMPTY;
                rules[idx_rule].next_state[0].next_color = SAND;
                rules[idx_rule].next_state[0].dx = 0;
                rules[idx_rule].next_state[0].dy = 1;
                break;
            }
        }
    }
}

unsigned int rules_count()
{
    return MAX_RULE; // depend du rules_init()
}

struct rule* rule_get(unsigned int i)
{
    unsigned int max_rule = rules_count();
    assert(max_rule == 0 || i < max_rule);
    return &rules[i];
}

/** Give the 8 neighbours of a cell and put them in an array of 9 cells */
void find_neighbors(unsigned int tab[], const struct world* w, unsigned int i,
    unsigned int j)
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

int rule_match(const struct world* w, const struct rule* r, unsigned int i,
    unsigned int j)
{
    unsigned int tab[NB_NEIGHBORS];
    find_neighbors(tab, w, i, j);
    return (compare_patterns(NB_NEIGHBORS, r->pattern, tab));
}

unsigned int rule_num_changes(const struct rule* r) { return r->len_changes; }

unsigned int rule_change_to(const struct rule* r, unsigned int idx)
{
    if (idx < rule_num_changes(r)) {
        return r->next_state[idx].next_color; // idx used whith more color
    } else
        return 0; // 0 signifie une erreur ici
}

int rule_change_dx(const struct rule* r, unsigned int idx)
{
    unsigned int max_change = rule_num_changes(r);
    assert(max_change == 0 || idx < max_change);
    // fprintf(stderr, "dx: %d \n", r->next_state[idx].dx);
    return r->next_state[idx].dx;
}

int rule_change_dy(const struct rule* r, unsigned int idx)
{
    unsigned int max_change = rule_num_changes(r);
    assert(max_change == 0 || idx < max_change);
    return r->next_state[idx].dy;
}
