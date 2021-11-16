#include "world.h"
#include <stdio.h>

#define NB_NEIGHTBORS 9
#define NB_RULES 512
// #define NB_RULES 2

#define B 16777215

struct rule {
    unsigned int pattern[NB_NEIGHTBORS]; /** a voir pour le motif*/
    unsigned int change; /** la valeur du changement du pixel*/
    // il faudra changer change en tableau dans un deuxieme tps
};

struct rule rules[NB_RULES];

/* Rules initialization, aim to be edited to implement new rules **/

/*
void rules_init() //pour les regles de la vie, on a 
{
    int tmp = 0;
    int n_B = 0;
    for (int i = 0; i < NB_RULES; ++i) {
        tmp = i;
        n_B = 0;
        for (int j = NB_NEIGHTBORS; j > 0; --j) {
            if (tmp % 2 == 0) {
                rules[i].pattern[j - 1] = 0;
            } else {
                rules[i].pattern[j - 1] = B;
                if (j - 1 != 4) {
                    ++n_B;
                }
            }
            tmp = tmp / 2;

            if (rules[i].pattern[4] == 0 && n_B == 3) {
                rules[i].change = B;
            } else if (rules[i].pattern[4] == B && (n_B == 0 || n_B == 1 || n_B >= 4)) {
                rules[i].change = 0;
            }
        }
    }
}
*/

// ### ceci est un test ###
void rules_init2()
{
    struct rule r;
    for(int i=0; i<9; i++)
    {
        r.pattern[i]=i;
    }
    r.change = 10;
    rules[0] = r;
}

void afficher_rule0_pattern()
{
    afficher_tableau(9, rules[0].pattern);
}

void afficher_rules_pattern()
{
    for(int i=0; i<NB_RULES; i++)
    {
        afficher_tableau(9, rules[i].pattern);
    }
}

// ceci est un test

void rules_init() //pour les regles de la vie, on a
{
    int tmp = 0;
    int n_B = 0;
    for (int i = 0; i < NB_RULES; ++i) {
        tmp = i;
        n_B = 0;
        for (int j = NB_NEIGHTBORS; j > 0; --j) {
            if (tmp % 2 == 0) {
                rules[i].pattern[j - 1] = 0;
            } else {
                rules[i].pattern[j - 1] = B;
                if (j - 1 != 4) {
                    ++n_B;
                }
            }
            tmp = tmp / 2;

            if (rules[i].pattern[4] == 0 && n_B == 3) {
                rules[i].change = B;
            } else if (rules[i].pattern[4] == B && (n_B == 0 || n_B == 1 || n_B >= 4)) {
                rules[i].change = 0;
            }
        }
    }
}

unsigned int rules_count()
{
    unsigned int n;
    n = NB_RULES; /** la vrai formule : nb_couleur ^(NB_NEIGHTBORS)*/
    return n;
}

struct rule* rule_get(unsigned int i)
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

int modulo(int x, int n)
{
    if(x<0)
    {
        return n+(x%n);
    }
    else 
        return x%n;
}

/** trouve les 9 voisins d'une case (i,j) et le met dans un tableau avec les 3premiers en (i-1), puis les 3 suivant en i ...*/
void find_neighbors(unsigned int tab[], const struct world* w, unsigned int i, unsigned int j)
{
    for(int m=0; m<3; m++)
    {
        for (int n=0; n<3; n++)
        {
            int idx_l, idx_c; //index ligne et colonne
            idx_l = modulo(i+(m-1), HEIGHT); // 1 est le milieu de 3, si on veut une generalisation faire millieu du motif a la place de -1
            idx_c = modulo(j+(n-1), WIDTH);
            tab[3*m+n]=w->t[idx_l*WIDTH+idx_c];
        }
    }
}


/** compare un tableau*/
int compare_t(int n, unsigned int t1[], const unsigned int t2[])
{
    for (int i = 0; i < n; i++) {
        if (t1[i] != t2[i]) {
            return 0;
        }
    }
    return 1;
}

//faire une fonction : find_neighbors, pour mettre tous les voisins dans un tableau
//une amelioration possible est de tester les voisins 1 a 1 et retourner faux des la premiere incoherence
int rule_match(const struct world* w, const struct rule* r, unsigned int i, unsigned int j)
{
    unsigned int tab[NB_NEIGHTBORS];
    find_neighbors(tab, w, i, j);
    return compare_t(NB_NEIGHTBORS, r->pattern, tab);
}

unsigned int rule_num_changes(const struct rule* r)
{
    return 1; // on est dans l'achiev 1 avec 1 seul change possible
}

/** unsigned int rule_change_to(const struct rule* r, unsigned int idx) on ne l'utilise pas ici car 1 seul changement*/
