#include "utils_test.h"
#include <stdio.h>

void afficher_tableau(int n, unsigned int* t)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", t[i]);
    }
    printf("\n");
}

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

void afficher_tableau_positions(int n, struct position* t)
{
    for (int i = 0; i < n; i++) {
        printf("(%d %d) ", t[i].x, t[i].y);
    }
    printf("\n");
}

/**Prend en argument le pointeur vers une règle, len_changes de la rule, un
 * tableau de taille len_changes et retourne tous les déplacements d'une règle*/
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