#include "conflict.h"
#include "world.h"
#include <stdio.h>
#include <stdlib.h>

void construct_t_conflicts(struct conflict* t)
{
    for (int i = 0; i < WIDTH * HEIGHT; ++i) {
        t[i].conflict_to_process = 0;
        t[i].nb_conflicts = 0;
    }
}

int solve_conflict(struct conflict t_conflicts[], unsigned int i, unsigned int j)
{
    struct conflict c = t_conflicts[i * WIDTH + j];
    int random = rand();
    if (c.nb_conflicts == 0) { // le conflit a été géré
        return 0;
        fprintf(stderr, "Conflit perdant en %d %d car nb_conflicts =0\n", i, j);
    } else if (c.conflict_to_process == 1) // si il n'y a qu'un 'conflit' (c'est plus un conflit du coup mais bon ...)
    {
        return 1;
    } else if ((random % c.nb_conflicts) == 0) // 1 chance sur le nb de conflit d'accepter ce conflit
    {
        t_conflicts[i * WIDTH + j].nb_conflicts = 0;
        return 1;
    } else {
        t_conflicts[i * WIDTH + j].conflict_to_process -= 1;
        fprintf(stderr, "Conflit perdant en %d %d car perd au tirage random.\n", i, j);
        fprintf(stderr, "Conflict to process %d\n", c.conflict_to_process);
        return 0;
    }
}
