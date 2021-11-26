#include "../src/world.h"
#include "../src/rule.h"
#include "../src/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct world world_init();

void world_disp(struct world w);

void afficher_tableau(int n, unsigned int *t)
{
    for(int i=0; i<n; i++)
    {
        printf("%d ", t[i]);
    }
    printf("\n");
}

int test_init_rule()
{
    unsigned int n = rules_count();
    printf("Le nombre de regles a verifier est : %d\n", n);
    printf("Verification du tableau de couleurs d'une regle ...\n");
    for(unsigned int i=0; i<n; ++i)
    {
        unsigned int nb_changes = rule_num_changes(rule_get(i));
        if(nb_changes!=4)
        {
            printf("Erreur: mauvaise valeur pour nb_changes\n \n");
            return 1;
        }
        for(unsigned int j=0; j<nb_changes; ++j)
        {
            unsigned int c = rule_change_to(rule_get(i), j);//finir de tester
        }
    }
    return 0;
}

int main()
{
    //struct world w;
    //w = world_init();
    rules_init();
    test_init_rule();
    return 0;
}