#include "../src/world.h"
#include "../src/rule.h"
#include "../src/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct world world_init();
void world_disp(struct world *w);

struct position{
    unsigned int x;
    unsigned int y;
};

//### COPIE D'UNE PARTIE DU RULE.C INACCESSIBLE ###
#define MAX_RULE 3
#define NB_NEIGHBORS 9

enum state {
    EMPTY = 0,
    SAND = 16777215,
    GRASS = 65280,
    RANDOM_COLOR = 4294967295,
    STATE_COUNT = 4,
    FIRST_STATE = EMPTY
};


struct rule {
    unsigned int pattern[NB_NEIGHBORS]; // another def is possible instead of patterns
    unsigned int len_changes;
    unsigned int change[STATE_COUNT]; // 5 diff color
    unsigned int dx[STATE_COUNT];
    unsigned int dy[STATE_COUNT]; // vector difining the cell move
};

struct rule rules[MAX_RULE];


//### FIN DE LA COPIE ###

void afficher_tableau(int n, unsigned int *t)
{
    for(int i=0; i<n; i++)
    {
        printf("%d ", t[i]);
    }
    printf("\n");
}

void afficher_tableau_positions(int n, struct position *t)
{
    for(int i=0; i<n; i++)
    {
        printf("(%d %d) ", t[i].x, t[i].y);
    }
    printf("\n");
}

/*a revoir*/
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
        /*
        for(unsigned int j=0; j<nb_changes; ++j)
        {
            unsigned int c = rule_change_to(rule_get(i), j); finir de tester
        }*/
    }
    return 0;
}

void create_damier(struct world *w)
{

    for(int i=0; i<HEIGHT*WIDTH; i++)
    {
        if(i%2==0)
        {
             w->t[i]=EMPTY;
        }
       else 
            w->t[i]=SAND;
    }
}

void create_hourglass(struct world *w)
{
    for(int i=0; i<HEIGHT*WIDTH; i++)
    {
        if(i<WIDTH)
        {
            w->t[i]=SAND;
        }
        else 
            w->t[i]=EMPTY;
    }
    w->t[6]=GRASS;
    w->t[8]=GRASS;
    /** #
     *  S S S
     *  E E E
     *  G E G
     * */
}

void create_rule1(struct rule *r)
/** Change le SAND (blanc) en EMPTY(noir, idx=0) ou en GRASS(vert,idx=1) */ 
{
    r->len_changes = 2;
    r->change[0] = EMPTY;
    r->change[1] = GRASS;
    for(int i = 0; i<NB_NEIGHBORS;i++)
    {
        r->pattern[i]=RANDOM_COLOR;
    }
    r->pattern[4]=SAND;
}

void create_rule2(struct rule *r)
/** Chute libre d'une particule de sable */
{
    r->len_changes = 1;
    r->dx[0] = 1;
    r->dy[0] = 0;
    for(int i = 0; i<NB_NEIGHBORS;i++)
    {
        r->pattern[i]=RANDOM_COLOR;
    }
    r->pattern[4]=SAND;
    r->pattern[4]=EMPTY;
}

int test_rule_match(const struct world* w, const struct rule* r, struct position t[])
{
    int nb_matchs = 0;
    for(int i=0; i<WIDTH*HEIGHT; i++)
    {
        struct position p;
        p.x = i/WIDTH;
        p.y = i%WIDTH;
        if(rule_match(w,r,p.x,p.y))
        {
            t[nb_matchs]= p;
            ++nb_matchs;
        }
    }
    return nb_matchs;
}

void evolution_world(struct world *w, struct rule *r, unsigned int idx_change)
{
    for(int i=0; i<WIDTH*HEIGHT; i++)
    {
        struct position p;
        p.x = i/WIDTH;
        p.y = i%WIDTH;
        if(rule_match(w,r,p.x,p.y))
        {
            w->t[i]=r->change[idx_change];
        }
    }
}

void deplacements(struct world *w, struct rule *r, unsigned int idx_change)
{
    struct queue q;
    queue_init(&q);
    for(int i=0; i<WIDTH*HEIGHT; i++)
    {
        struct position p;
        p.x = i/WIDTH;
        p.y = i%WIDTH;
        if(rule_match(w,r,p.x,p.y))
        {
            w->t[i]=r->change[idx_change];
        }
    }

}

int main()
{
    printf("Initialisation des regles ...");
    struct rule r;
    create_rule1(&r);
    rules[0]=r;
    printf("FAIT \n");
    printf("Creation d'un damier...");
    struct world w_damier;
    create_damier(&w_damier);
    printf("FAIT \n");
    world_disp(&w_damier);
    printf("Rechercher du nombres de positions où s'applique la règle avec leurs indices...\n");
    struct position t_idx_positions[WIDTH*HEIGHT];
    int nb_p_matchs = test_rule_match(&w_damier, &r, t_idx_positions);
    printf("Nombre de match = %d \n",nb_p_matchs);
    printf("Les positions sont: ");
    afficher_tableau_positions(nb_p_matchs,t_idx_positions);
    printf("Application des changements sur le monde ...");
    evolution_world(&w_damier,&r,1);
    printf("FAIT \n");
    printf("Le nouveau monde :\n");
    world_disp(&w_damier);
    printf("Creation d'un mini sablier...");
    struct world w_sablier;
    create_hourglass(&w_sablier);
    printf("FAIT \n");
    world_disp(&w_sablier);
    return 0;
}