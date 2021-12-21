#include <assert.h>
#include <stdio.h>

#include "rule_ext.h"

#include "utils.h"
#include "world.h"

struct rule rules[MAX_RULE];

int born(const struct world* w, unsigned int i, unsigned int j)
{
    if (w->t[(i * WIDTH + j)] != DEAD) {
        return 0;
    } else {
        unsigned int nb_alive = 0;
        for (int k = -1; k <= 1; k++) {
            for (int l = -1; l <= 1; l++) {
                if (w->t[modulo(i + k, HEIGHT) * WIDTH + modulo(j + l, WIDTH)] == ALIVE && !(k == 0 && l == 0)) {
                    ++nb_alive;
                }
            }
        }
        return nb_alive == 3;
    }
}

int dead(const struct world* w, unsigned int i, unsigned int j)
{
    if (w->t[(i * WIDTH + j)] != ALIVE) {
        return 0;
    } else {
        unsigned int nb_alive = 0;
        for (int k = -1; k <= 1; k++) {
            for (int l = -1; l <= 1; l++) {
                if (w->t[modulo(i + k, HEIGHT) * WIDTH + modulo(j + l, WIDTH)] == ALIVE && !(k == 0 && l == 0)) {
                    ++nb_alive;
                }
            }
        }
        return nb_alive <= 1 || nb_alive >= 4;
    }
}

void rules_init() // règles pour générer un tas de sable
{
    rules[0].match = born;
    rules[0].len_changes = 1;
    rules[0].next_state[0].next_color = ALIVE;
    rules[0].next_state[0].dx = 0;
    rules[0].next_state[0].dy = 0;

    rules[1].match = dead;
    rules[1].len_changes = 1;
    rules[1].next_state[0].next_color = DEAD;
    rules[1].next_state[0].dx = 0;
    rules[1].next_state[0].dy = 0;
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

int rule_match(const struct world* w, const struct rule* r, unsigned int i, unsigned int j)
{
    return r->match(w, i, j);
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
