#include "world.h"
#include "queue.h"
#include "rule.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

extern char* optarg;

struct world world_init();

void world_disp(struct world * w);

void world_apply_rule(struct world * w, struct rule* r, int i, int j)
{
    w->t[i*WIDTH+j]=rule_change_to(r, 0);
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
                unsigned int j = 0; 
                while (!rule_match(&w, rule_get(j), k, l) && j < rules_count()) {
                    ++j;
                }
                queue_append(&q, k, l, j);
            }
        } 
        while(queue_is_not_empty(&q))
        {
            struct change* change_tmp;
            change_tmp = queue_pop(&q);
            int n = rule_num
            world_apply_rule(&w, rule_get(change_tmp->idx_rule), change_tmp->i, change_tmp->j);
        }
        world_disp(&w);
    }
    return 0;
}