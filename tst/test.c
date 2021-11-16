#include "../src/world.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char* optarg;

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
    return 0;
}