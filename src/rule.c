#include <stdio.h>

#include "world.h"
#include "rule.h"

#define NB_NEIGHBORS 9
#define NB_RULES 512
#define B 16777215

struct rule {
    unsigned int pattern[NB_NEIGHBORS]; // another def is possible instead of patterns
    unsigned int len_changes;
    unsigned int change; // the new state of the pixel after 
};

struct rule rules[NB_RULES];

void rules_init() //for the rules of life, we have the following patterns :
{
    int tmp = 0;
    int n_B = 0;
    for (int i = 0; i < NB_RULES; ++i) {
        rules[i].len_changes = 1;
        tmp = i;
        n_B = 0;
        for (int j = NB_NEIGHBORS; j > 0; --j) {
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
            } else
            {
                rules[i].change = rules[i].pattern[4];
            }
            
        }
    }
}

unsigned int rules_count()
{
    unsigned int n;
    n = NB_RULES; // the real formule is : 2^(nb of neighbors) for the rule represented by a pattern
    return n;
}

struct rule* rule_get(unsigned int i)
{
    if(i<rules_count())
    {
        return &rules[i];
    }
    return NULL;
}

/** The usal modulo for positive number, for the negative number the function return a positive number like for congruence */
int modulo(int x, int n)
{
    if(x<0)
    {
        return n+(x%n);
    }
    else 
        return x%n;
}

/** Give the 8 neighbours of a cell and put them in an array of 9 cells */
void find_neighbors(unsigned int tab[], const struct world* w, unsigned int i, unsigned int j)
{
    for(int m=0; m<3; m++)
    {
        for (int n=0; n<3; n++)
        {
            int idx_l, idx_c; //index of lines and columns
            idx_l = modulo(i+(m-1), HEIGHT); 
            idx_c = modulo(j+(n-1), WIDTH);
            tab[3*m+n]=w->t[idx_l*WIDTH+idx_c]; // the formule to transform a Matrix in an array
        }
    }
}


/** Return a booleen considering if two arrays of length n are the same */
int compare_t(int n, const unsigned int t1[], unsigned int t2[])
{
    for (int i = 0; i < n; i++) {
        if (t1[i] != t2[i]) {
            return 0;
        }
    }
    return 1;
}

//une amelioration possible est de tester les voisins 1 a 1 et retourner faux des la premiere incoherence
int rule_match(const struct world* w, const struct rule* r, unsigned int i, unsigned int j)
{
    unsigned int tab[NB_NEIGHBORS];
    find_neighbors(tab, w, i, j);
    return (compare_t(NB_NEIGHBORS, r->pattern, tab));
}

unsigned int rule_num_changes(const struct rule* r)
{
    return r->len_changes; // on est dans l'achiev 1 avec 1 seul change possible
}

// unsigned int rule_change_to(const struct rule* r, unsigned int idx) 
//This function is not use in this case

unsigned int rule_change_to(const struct rule* r, unsigned int idx)
{
    if(idx<rule_num_changes(r))
    {
        return r->change; //idx used whith more color
    }
    else 
        return 0; //trouver une autre solution
}

// #### FUNCTIONS CREATED FOR THE TESTS ####
// They are in this file because they need an access to the array rules 

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

/*
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
*/
