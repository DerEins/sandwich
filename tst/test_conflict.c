#include "../src/conflict.h"
#include "../src/queue.h"
#include "../src/rule_ext.h"
#include "../src/utils.h"
#include "../src/world_ext.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define NB_IMAGES 100

void world_test_conflict(struct world* w)
{
    for (int i = 0; i < WIDTH * HEIGHT; ++i) {
        w->t[i] = EMPTY;
    }
    w->t[3] = SAND;
    w->t[1] = GRASS;
}

/** the sand go to the right */
void create_rule_sand(struct rule* r)
{
    r->len_changes = 1;
    r->next_state[0].next_color = SAND;
    r->next_state[0].dx = 0;
    r->next_state[0].dy = 1;
    for (int i = 0; i < NB_NEIGHBORS; i++) {
        r->pattern[i] = RANDOM_COLOR;
    }
    r->pattern[4] = SAND;
}

void create_rule_grass(struct rule* r)
{
    r->len_changes = 1;
    r->next_state[0].next_color = GRASS;
    r->next_state[0].dx = 1;
    r->next_state[0].dy = 0;
    for (int i = 0; i < NB_NEIGHBORS; i++) {
        r->pattern[i] = RANDOM_COLOR;
    }
    r->pattern[4] = GRASS;
}

int main()
{
    struct rule t[2];
    struct rule r;
    create_rule_sand(&r);
    t[0] = r;
    create_rule_grass(&r);
    t[1] = r;
    struct world w;
    world_test_conflict(&w);
    printf("%d %d\n", WIDTH, HEIGHT);
    world_disp(&w);
    srand(55); // essayer avec 128 pour voir les jaunes passer avant.
    for (int i = 0; i < NB_IMAGES; i++) {
        struct conflict t_conflicts[WIDTH * HEIGHT];
        construct_t_conflicts(t_conflicts);
        struct queue q;
        queue_init(&q);
        for (unsigned int k = 0; k < HEIGHT; k++) {
            for (unsigned int l = 0; l < WIDTH; l++) {
                for (unsigned int j = 0; j < 2; ++j) {
                    struct rule* r = &t[j];
                    if (rule_match(&w, r, k, l)) {
                        unsigned int idx_change = 0;
                        int dx_tmp = rule_change_dx(&t[j], idx_change);
                        int dy_tmp = rule_change_dy(&t[j], idx_change);
                        int index_tmp = modulo(k + dx_tmp, HEIGHT) * WIDTH + modulo(l + dy_tmp, WIDTH);
                        if (w.t[index_tmp] == EMPTY && (dx_tmp || dy_tmp)) {
                            t_conflicts[index_tmp].nb_conflicts = t_conflicts[index_tmp].nb_conflicts + 1;
                            t_conflicts[index_tmp].conflict_to_process = t_conflicts[index_tmp].conflict_to_process + 1;
                            queue_append(&q, k, l, j, idx_change);
                        } else if (!(dx_tmp || dy_tmp)) {
                            t_conflicts[index_tmp].nb_conflicts = t_conflicts[index_tmp].nb_conflicts + 1;
                            t_conflicts[index_tmp].conflict_to_process = t_conflicts[index_tmp].conflict_to_process + 1;
                            queue_append(&q, k, l, j, idx_change);
                        }
                        break;
                    }
                }
            }
        }
        while (queue_is_not_empty(&q)) {
            struct change* change_tmp;
            change_tmp = queue_pop(&q);
            world_apply_rule(&w, &t[change_tmp->idx_rule], change_tmp->i, change_tmp->j, change_tmp->idx_next_state, t_conflicts);
        }
        world_disp(&w);
    }
    return 0;
}