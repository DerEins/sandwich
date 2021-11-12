#include "world.h"
#include <stdio.h>

#define NB_NEIGHTBORS 3
#define B 16777215

struct rule
{
    unsigned int pattern[NB_NEIGHTBORS]; /** a voir pour le motif*/
    unsigned int change; /** la valeur du changement du pixel*/
    // il faudra changer change en tableau dans un deuxieme tps
};

struct rule rules[2]; 

void rules_init() //pour les regles de la vie, on a 
{
    struct rule r;
    for(int i = 0; i<3; i++)
    {
        r.pattern[i]=0;
    }
    r.change=B;
    rules[0]=r;
    for(int i = 0; i<3; i++)
    {
        r.pattern[i]=B;
    }
    r.change=0;
    rules[1]=r;
}

unsigned int rules_count()
{   
    unsigned int n;
    n = 512; /** la vrai formule : nb_couleur ^(NB_NEIGHTBORS)*/
    return n;
}

struct rule * rule_get(unsigned int i)
{
    return &rules[i];
}

/** il faut prendre en compte les cas limites (mais une formule c'est quand meme mieux"*/
/**void find_neighbors(int tab[9], const struct world* w,unsigned int i, unsigned int j)
{
    tab[0]=w->t[(i-1)*WIDTH+(j-1)];
    tab[1]=w->t[(i-1)*WIDTH+j];
    tab[2]=w->t[(i-1)*WIDTH+(j+1)];
    tab[3]=w->t[i*WIDTH+(j-1)];
    tab[4]=w->t[i*WIDTH+(j)];
    tab[5]=w->t[i*WIDTH+(j+1)];
    tab[6]=w->t[(i+1)*WIDTH+(j-1)];
    tab[7]=w->t[(i+1)*WIDTH+j];
    tab[8]=w->t[(i+1)*WIDTH+(j+1)];
}*/

void find_neighbors(int tab[3], const struct world* w,unsigned int i, unsigned int j)
{
    if(j==0)
    {
        tab[0]=w->t[(i+1)*WIDTH-1];
    }
    else if(j==WIDTH)
    {
        tab[0]=w->t[i*WIDTH];
    }
    else 
        tab[0]=w->t[i*WIDTH+j];
}

int compare_t(int c, int *t1, int *t2)
{
    for(int i = 0; i<c; i++)
    {
        if(t1[i]!=t2[i])
        {
            return 0;
        }
    }
    return 1;
}

//faire une fonction : find_neighbors, pour mettre tous les voisins dans un tableau
int rule_match(const struct world* w, const struct rule* r, unsigned int i, unsigned int j)
{
    int tab[NB_NEIGHTBORS];
    find_neighbors(tab, w, i, j);
    return compare_t(w->t, tab, NB_NEIGHTBORS);
}

unsigned int rule_num_changes(const struct rule* r)
{ 
    return 1; // on est dans l'achiev 1 avec 1 seul change possible 
}

/** unsigned int rule_change_to(const struct rule* r, unsigned int idx) on ne l'utilise pas ici car 1 seul changement*/