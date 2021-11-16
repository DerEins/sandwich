#include "../src/queue.h"
#include "../src/rule.h"
#include "../src/world.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char* optarg;
#define M 5 //le nombre d'images generees

//prendre comme cmd WIDTH=3 HEIGHT=4 make test_project
struct world world_init();

void world_disp(struct world w);

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
    w = world_init(opt, seed);
    world_disp(w);
    /**w.t[0] = 2;
    w.t[4] = 20;
    world_disp(w);
    rules_init();
    printf("%d %d\n", WIDTH, HEIGHT);
    for (int i = 0; i < M; i++) {
        struct queue* q;
        queue_init(q);
        for (int k = 0; k < HEIGHT; k++) {
            for (int l = 0; l < WIDTH; l++) {
                for (int j = 0; j < rules_count(); j++) {
                    if (rule_match(&w, rule_get(j), k, l)) {
                        queue_append(q, k, l, j);
                    }
                }
            }
        } */
    }
    return 0;
}