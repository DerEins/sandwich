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
    if (c.nb_conflicts == 0) { // the conflict is already solved 
        return 0;
        fprintf(stderr, "Conflit perdant en %d %d car nb_conflicts =0\n", i, j);
    } else if (c.conflict_to_process == 1) // there is no conflict (only one cell want to move to/change state in (i,j))
    {
        return 1;
    } else if ((random % c.nb_conflicts) == 0) // the change win the conflict with a probability of 1/nb_conflict (equal probability to win a conflict)
    {
        t_conflicts[i * WIDTH + j].nb_conflicts = 0; // there is no more conflict to solve
        return 1;
    } else { // the change is refused
        t_conflicts[i * WIDTH + j].conflict_to_process -= 1;
        return 0;
    }
}
