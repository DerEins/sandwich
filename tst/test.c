#include "../src/queue.h"
#include "../src/rule.h"
#include "../src/world.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char* optarg;

struct world world_init();

void world_disp(struct world w);

void world_apply_rule(struct world w, struct rule r, int i, int j)
{
    w->pattern[i*WIDTH+j]=r.change;
}

int main(int argc, char* argv[])
{
    if (argc == 2 || argc == 4 || argc > 5) {
        fprintf(stderr, "Erreur : il n'a pas été entré le bon nombre de paramètres.\n");
        return EXIT_FAILURE;
    }
    char input_opt = getopt(argc, argv, "m:s:");
    char opt = 0;
    int seed = 0, nb_pictures = 1;
    while (input_opt != -1) {
        switch (input_opt) {
        case 's':
            opt = 's';
            seed = atoi(optarg);
            printf("%c, Seed : %d \n", opt, seed);
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


    w = world_init();
    rules_init();
    printf("%d %d\n", WIDTH, HEIGHT);
    for (int i = 0; i < nb_pictures; i++) {
        struct queue* q;
        queue_init(q);
        for (int k = 0; k < HEIGHT; k++) {
            for (int l = 0; l < WIDTH; l++) {
                for (int j = 0; j < rules_count(); j++) {
                    if (rule_match(&w, rule_get(j), k, l)) {
                        queue_append(q, k, j);
                    }
                }
            }
        } 
        while(not is_empty(q)) //a def
        {
            struct change* change_tmp; // ou est la def de struct change ?
            change_tmp = queue_pop(q);
            world_apply_rule(w, change_tmp->, )
        }
    }
    return 0;
}