#include "world.h"
#include <stdio.h>
#include <stdlib.h>

#define B 16777215
#define NB_STATE 2

/** Create a new world with value 0 (and I want random value)*/
struct world world_init(char opt, int seed)
{
    srand(seed);
    struct world w;
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        if (opt == 's') {
            if (rand() % NB_STATE) {
                w.t[i] = B;
            } else {
                w.t[i] = 0;
            }
        } else {
            w.t[i] = 0;
        }
    }
    return w;
}

/** display a world according to the rules specified*/
void world_disp(struct world w)
{
    printf("#\n");
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        if ((i % WIDTH) == (WIDTH - 1)) {
            printf("%d \n", w.t[i]);
        } else
            printf("%d ", w.t[i]);
    }
}
