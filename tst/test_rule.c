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

int test_rule_match(const struct world* w, const struct rule* r)
{
    printf("Test le nombre de motifs qui correspond à une règle: ")
    int nb_match = 0;
    for(int i=0; i<HEIGHT; i++)
    {
        for(int j=0; j<WIDTH; j++)
        {
            if(rule_match(&w, rule_get(0), i, j))
            {
                ++nb_match;
            }
        }
    }
    if(nb_match=0)
    {
        printf("Erreur: Aucun match trouvé entre une regle et un motif du monde");
    }
    else if(nb_match>1)
    {
        printf("Erreur: il y a une regle qui correspond a plusieurs motifs");
        return EXIT_FAILURE;
    }
    else 
    {
        printf("VALIDE !\n");
        return EXIT_SUCCESS;
    }

}


int main()
{
    struct world w;
    w = world_init();
    for(int i; i<9; i++)
    {
        w.t[i]=i;
    }
    world_disp(w);
    rules_init2();
    // ### test find_neighbors ###
    unsigned int tab[9];
    find_neighbors(tab, &w, 0, 0);
    printf("%d\n", WIDTH);
    //afficher_tableau(9, tab);
    // ### test compare_t ###
    unsigned int t1[] = {1,2,3};
    unsigned int t2[] = {1,2,3};
    unsigned int t3[] = {1,2,0};
    unsigned int t4[] = {0,2,3};
    printf("### Test compare_t ###\n");
    printf("compare t1, t2 :%d\n", compare_t(3, t1, t2));
    printf("compare t1, t3 :%d\n", compare_t(3, t1, t3));
    printf("compare t1, t4 :%d\n", compare_t(3, t1, t4));
    // ### test rule_match ###
    //afficher_rule0_pattern();
    //test rule_init
    printf("### Test rules_init ###\n");
    rules_init();
    //afficher_rules_pattern();
    return 0;
}