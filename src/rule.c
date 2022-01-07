#include <assert.h>
#include <stdio.h>

#include "rule_ext.h"

#include "utils.h"
#include "world.h"

/** Array storing the rules */
struct rule rules[MAX_RULE];

/** Return a booleen. True (1) if a cell should live following the rule of the game of life*/
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

/** Return a booleen. True (1) if cell should died following the rule of the game of life*/
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

void rules_init() // Initialize 2 rules for the game of life
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
    return MAX_RULE; // defined in world_ext.h, change with world_init
}

struct rule* rule_get(unsigned int i)
{
    unsigned int max_rule = rules_count();
    assert(max_rule == 0 || i < max_rule); //verify if the rule exists in the array rules
    return &rules[i];
}

int rule_match(const struct world* w, const struct rule* r, unsigned int i, unsigned int j)
{
    return r->match(w, i, j);
}

unsigned int rule_num_changes(const struct rule* r) { return r->len_changes; }

unsigned int rule_change_to(const struct rule* r, unsigned int idx)
{
    assert(idx < rule_num_changes(r));
    return r->next_state[idx].next_color;
}

int rule_change_dx(const struct rule* r, unsigned int idx)
{
    unsigned int max_change = rule_num_changes(r);
    assert(max_change == 0 || idx < max_change);
    return r->next_state[idx].dx;
}

int rule_change_dy(const struct rule* r, unsigned int idx)
{
    unsigned int max_change = rule_num_changes(r);
    assert(max_change == 0 || idx < max_change);
    return r->next_state[idx].dy;
}
