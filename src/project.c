#include "queue.h"
#include "rule.h"
#include "world.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

extern char* optarg;

struct world world_init();

void world_disp(struct world* w);

void world_apply_rule(struct world* w, struct rule* r, int i, int j, unsigned int idx_color)
{
    w->t[i * WIDTH + j] = rule_change_to(r, idx_color);
}

unsigned int chose_color(unsigned int nb_colors)
{
    unsigned int r = rand();
    return r % nb_colors;
}

int main(int argc, char* argv[])
{
    if (argc == 2 || argc == 4 || argc > 5) {
        fprintf(stderr, "Erreur : il n'a pas été entré le bon nombre de paramètres.\n");
        return EXIT_FAILURE;
    }
    char input_opt = getopt(argc, argv, "m:s:");
    char opt = 0;
    int seed = 0, nb_pictures = 10;
    while (input_opt != -1) {
        switch (input_opt) {
        case 's':
            opt = 's';
            seed = atoi(optarg);
            break;
        case 'm':
            nb_pictures = atoi(optarg);
            break;
        default: /* '?' */
            break;
        }
        input_opt = getopt(argc, argv, "s:");
    }
    struct world w;

    /* pas necessaire ici  je pense
    w = world_init(opt, seed); //pq des parametres dans world_init ??
    world_disp(w);*/

    w = world_init(opt, seed);
    rules_init();
    printf("%d %d\n", WIDTH, HEIGHT);
    for (int i = 0; i < nb_pictures; i++) {
        struct queue q;
        queue_init(&q);
        for (unsigned int k = 0; k < HEIGHT; k++) {
            for (unsigned int l = 0; l < WIDTH; l++) {
                fprintf(stderr, "%d\n", w.t[k * WIDTH + l]);
                fprintf(stderr, "%d\n", w.t[(k + 1) * WIDTH + l]);
                for (unsigned int j = 1; j < rules_count() - 1; ++j) {
                    struct rule* r = rule_get(j);
                    if (rule_match(&w, r, k, l)) {
                        unsigned int dx = rule_change_dx(r, 0);
                        unsigned int dy = rule_change_dy(r, 0);
                        if (dx || dy) {
                            queue_append(&q, k, l, 0);
                        }
                        queue_append(&q, k + dx, l + dy, j);
                        break;
                    }
                }
            }
        }
        srand(seed);
        while (queue_is_not_empty(&q)) {
            struct change* change_tmp;
            change_tmp = queue_pop(&q);
            unsigned int n = chose_color(rule_num_changes(rule_get(change_tmp->idx_rule)));
            world_apply_rule(&w, rule_get(change_tmp->idx_rule), change_tmp->i, change_tmp->j, n);
        }
        world_disp(&w);
    }
    return 0;
}

/*
            for(unsigned int idx_color=0; idx_color<n; ++idx_color)
            {
                unsigned int color = rule_change_to(rule_get(change_tmp->idx_rule), idx_color);
                if(rand()%100<10)
                {
                    world_apply_rule(&w, rule_get(change_tmp->idx_rule), change_tmp->i, change_tmp->j, idx_color);
                }
            }
*/
