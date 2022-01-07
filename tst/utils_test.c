#include "utils_test.h"
#include <stdio.h>

/** Print an array of unsigned integer */
void afficher_tableau(int n, unsigned int* t)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", t[i]);
    }
    printf("\n");
}

/** Return a booleen. Compare 2 worlds. */
int comparer_monde(struct world* w1, struct world* w2)
{
    for (int i = 0; i < WIDTH * HEIGHT; ++i) {
        if (w1->t[i] != w2->t[i]) {
            printf("Les mondes ne sont pas identiques !\n");
            return 0;
        }
    }
    return 1;
}

/** Show the positions in an array with the dallowing structure :(i,j)*/
void afficher_tableau_positions(int n, struct position* t)
{
    for (int i = 0; i < n; i++) {
        printf("(%d %d) ", t[i].x, t[i].y);
    }
    printf("\n");
}

/** Show all the movements defined in a rule r */
void print_moves_rule(struct rule* r, unsigned int len_changes, struct position* t)
{
    for (unsigned int i = 0; i < len_changes; ++i) {
        struct position p;
        p.x = r->next_state[i].dx;
        p.y = r->next_state[i].dy;
        t[i] = p;
    }
    afficher_tableau_positions(len_changes, t);
}