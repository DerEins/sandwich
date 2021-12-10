#include "../src/queue.h"
#include "../src/rule.h"
#include "../src/utils.h"
#include "../src/world.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_STATE 10
#define NB_NEIGHBORS 9
#define NB_IMAGES 100

struct world world_init();
void world_disp(struct world* w);

struct position {
    unsigned int x;
    unsigned int y;
};

struct next_state {
    unsigned int next_color;
    int dx, dy;
};

struct rule {
    unsigned int pattern[NB_NEIGHBORS];
    unsigned int len_changes;
    struct next_state next_state[MAX_STATE];
};

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

/** the grass go down */
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

void construct_t_conflicts(struct conflict* t)
{
    for (int i = 0; i < WIDTH * HEIGHT; ++i) {
        t[i].conflict_to_process = 0;
        t[i].nb_conflicts = 0;
    }
}

// the main function (a copy of project.c)

int solve_conflict(struct conflict t_conflicts[], unsigned int i, unsigned int j)
{
    struct conflict c = t_conflicts[i * WIDTH + j];
    int random = rand();
    if (c.nb_conflicts == 0) { // le conflit a été géré
        return 0;
    } else if (c.conflict_to_process == 1) // si il n'y a qu'un 'conflit' (c'est plus un conflit du coup mais bon ...)
    {
        return 1;
    } else if ((random % c.nb_conflicts) == 0) // 1 chance sur le nb de conflit d'accepter ce conflit
    {
        t_conflicts[i * WIDTH + j].nb_conflicts = 0;
        return 1;
    } else {
        t_conflicts[i * WIDTH + j].conflict_to_process -= 1;
        return 0;
    }
}

void world_apply_rule(struct world* w, struct rule* r, int i, int j, unsigned int idx_change, struct conflict t_conflicts[])
{
    unsigned int dx = rule_change_dx(r, idx_change);
    unsigned int dy = rule_change_dy(r, idx_change);
    int s = solve_conflict(t_conflicts, modulo(i + dx, HEIGHT), modulo(j + dy, WIDTH));
    if (s) {
        if (dx || dy) {
            w->t[modulo(i + dx, HEIGHT) * WIDTH + modulo(j + dy, WIDTH)] = rule_change_to(r, idx_change);
            w->t[i * WIDTH + j] = EMPTY;
        }
    } else {
        w->t[i * WIDTH + j] = rule_change_to(r, idx_change);
    }
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
    w = world_init();
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