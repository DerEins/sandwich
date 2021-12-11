#include "../src/queue.h"
#include "../src/rule.h"
#include "../src/utils.h"
#include "../src/world.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATE 10
#define NB_NEIGHBORS 9

struct world world_init();
void world_disp(struct world* w);

struct position {
    unsigned int x;
    unsigned int y;
};

struct next_state {
    unsigned int next_color;
    int dx, dy;
};

struct rule {
    unsigned int pattern[NB_NEIGHBORS];
    unsigned int len_changes;
    struct next_state next_state[MAX_STATE];
};

//### COPIE D'UNE PARTIE DES .C INACCESSIBLES ###

void world_apply_rule(struct world* w, struct rule* r, int i, int j,
    unsigned int idx_color)
{
    w->t[i * WIDTH + j] = rule_change_to(r, idx_color);
}

//### FIN DE LA COPIE ###

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

void create_damier(struct world* w)
{

    for (int i = 0; i < HEIGHT * WIDTH; i++) {
        if (i % 2 == 0) {
            w->t[i] = EMPTY;
        } else {
            w->t[i] = SAND;
        }
    }
}

void create_basic_world(struct world* w)
{
    for (int i = 0; i < HEIGHT * WIDTH; i++) {
        w->t[i] = GRASS;
    }
    w->t[4] = SAND;
    /**
     *  G G G
     *  G S G
     *  G G G
     */
}

/** Créer le monde attendu à partir du monde de départ, du monde à modifier, des
 * deplacements, et de la position de la cellule à déplacer*/
void world_expected_after_movement(struct world* initial_world,
    struct world* final_world, int dx, int dy,
    unsigned int i, unsigned int j)
{
    if (dx == 0 && dy == 0) {
        printf("Il n'y a pas de mouvements !\n");
    } else {
        for (int k = 0; k < WIDTH * HEIGHT; ++k) {
            final_world->t[k] = initial_world->t[k];
        }
        unsigned int idx_mov = modulo(i + dx, HEIGHT) * WIDTH + modulo(j + dy, WIDTH);
        final_world->t[idx_mov] = final_world->t[i * WIDTH + j];
        final_world->t[i * WIDTH + j] = EMPTY;
    }
}

/** La règel suivante change le SAND (blanc) en EMPTY(noir, idx=0) ou en
 * GRASS(vert,idx=1) Utile  pour le test d'utilisation de RANDOM_COLOR comme
 * couleur bonus ie une couleur qui 'match' avec toutes les couleurs*/
void create_rule1(struct rule* r)
{
    r->len_changes = 2;
    r->next_state[0].next_color = EMPTY;
    r->next_state[1].next_color = GRASS;
    r->next_state[0].dx = 0;
    r->next_state[0].dy = 0;
    r->next_state[1].dx = 0;
    r->next_state[1].dy = 0;
    for (int i = 0; i < NB_NEIGHBORS; i++) {
        r->pattern[i] = RANDOM_COLOR;
    }
    r->pattern[4] = SAND;
}

/** Créer une règle comportant 8 déplacements et 1 changement de couleur.
 * Le but est étant de tester les déplacements positifs, négatifs et la gestion
 * des bords d'un monde 3x3 */
void create_rule_movements(struct rule* r)
{
    r->len_changes = 9;
    for (int i = 0; i < NB_NEIGHBORS; i++) {
        r->pattern[i] = RANDOM_COLOR;
    }
    r->pattern[4] = SAND;
    for (int j = 0; j < 4; j++) {
        r->next_state[j].dx = j % 2;
        r->next_state[j].dy = j / 2;
        r->next_state[j].next_color = SAND;
    }
    for (int j = 1; j < 4; j++) {
        r->next_state[j + 3].dx = -(j % 2);
        r->next_state[j + 3].dy = -(j / 2);
        r->next_state[j + 3].next_color = SAND;
    }
    r->next_state[7].next_color = SAND;
    r->next_state[8].next_color = SAND;
    r->next_state[0].next_color = GRASS; // Le changement de couleur fait passer une cellule de SAND à GRASS
    r->next_state[7].dx = 2;
    r->next_state[7].dy = 0;
    r->next_state[8].dx = 0;
    r->next_state[8].dy = -2;
    // Les regles de deplacements sont les suivantes (avec (dx,dy))
    //(0,0) (1,0) (0,1) (1,1) (-1,0) (0,-1) (-1,-1) (2,0) (0,2)
}

/**Prend en argument le pointeur vers une règle, len_changes de la rule, un
 * tableau de taille len_changes et retourne tous les déplacements d'une règle*/
void print_moves_rule(struct rule* r, unsigned int len_changes,
    struct position* t)
{
    for (unsigned int i = 0; i < len_changes; ++i) {
        struct position p;
        p.x = r->next_state[i].dx;
        p.y = r->next_state[i].dy;
        t[i] = p;
    }
    afficher_tableau_positions(len_changes, t);
}

/** Test si une règle correspond à un motif présent dans le monde,
 * Si c'est le cas, la position est stockée dans le tableau t.
 * La fonction retourne le nombre de correspondances entre la règle et le monde
 * (qui est également la réelle taille de t)*/
int test_rule_match(const struct world* w, const struct rule* r,
    struct position t[])
{
    int nb_matchs = 0;
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        struct position p;
        p.x = i / WIDTH;
        p.y = i % WIDTH;
        if (rule_match(w, r, p.x, p.y)) {
            t[nb_matchs] = p;
            ++nb_matchs;
        }
    }
    return nb_matchs;
}

/** Applique sur un monde les changement liée à un changement d'une règle.
 * Prend en compte les changements de couleurs et les déplacements.*/
void evolution_world(struct world* w, struct rule* r, unsigned int idx_change)
{
    struct queue q;
    queue_init(&q);
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        struct position p;
        p.x = i / WIDTH;
        p.y = i % WIDTH;
        if (rule_match(w, r, p.x, p.y)) {
            int dx = r->next_state[idx_change].dx;
            int dy = r->next_state[idx_change].dy;
            if (dx || dy) {
                queue_append(&q, p.x, p.y, 1, idx_change); // la rule avec l'index 1 est celle qui remplace une
                                                           // cellule par EMPTY en (i,j)
            }
            queue_append(&q, modulo(p.x + dx, HEIGHT), modulo(p.y + dy, WIDTH), 0, idx_change);
        }
    }
    while (queue_is_not_empty(&q)) {
        struct change* change_tmp;
        change_tmp = queue_pop(&q);
        if (change_tmp->idx_rule == 1) // Cas particulier du deplacement avec passage de i,j en EMPTY
        {
            w->t[change_tmp->i * WIDTH + change_tmp->j] = EMPTY;
        } else {
            world_apply_rule(w, r, change_tmp->i, change_tmp->j, idx_change);
        }
    }
}

/** Test des règles utilisant RANDOM_COLOR*/
int test_rule_with_random_color()
{
    printf("#####################################################################"
           "#############\n");
    printf("######--- TEST 1: Test d'une règle utilisant RANDOM_COLOR sur un "
           "damier  ---######\n");
    printf("#####################################################################"
           "#############\n");
    printf("Initialisation des regles ...");
    struct rule r;
    create_rule1(&r); //
    printf("FAIT \n");
    printf("Creation d'un damier...");
    struct world w_damier;
    create_damier(&w_damier);
    printf("FAIT \n");
    world_disp(&w_damier);
    printf("Rechercher du nombres de positions où s'applique la règle avec leurs "
           "indices...\n");
    struct position t_idx_positions[WIDTH * HEIGHT];
    int nb_p_matchs = test_rule_match(&w_damier, &r, t_idx_positions);
    printf("Nombre de match = %d \n", nb_p_matchs);
    printf("Les positions sont: ");
    afficher_tableau_positions(nb_p_matchs, t_idx_positions);
    printf("Application des changements sur le monde ...");
    evolution_world(&w_damier, &r, 1); // the SAND is replace by GRASS
    printf("FAIT \n");
    printf("Le nouveau monde :\n");
    world_disp(&w_damier);
    printf("Verification des modifications par rapport aux positions des "
           "changements ...");
    for (int i = 0; i < nb_p_matchs; i++) {
        unsigned int index = t_idx_positions[i].x * WIDTH + t_idx_positions[i].y;
        if (w_damier.t[index] != GRASS) {
            printf("Erreur : Au moins un changement n'a pas été effectué. \n");
            exit(EXIT_FAILURE);
        } // ajouter un else qui permet de tester les autres valeurs
    }
    printf("FAIT\n");
    printf("\nTest d'utilisation de COLOR_RANDOM termine avec succes. \n \n");
    return EXIT_SUCCESS;
}

/** Test une règle avec des déplacements*/
int test_deplacements()
{
    printf("#####################################################################"
           "############\n");
    printf("######--- TEST 2: Test des règles de déplacements dans un monde "
           "simple  ---######\n");
    printf("#####################################################################"
           "############\n");
    printf("Initialisation de la regle de deplacement ...");
    struct rule r;
    create_rule_movements(&r);
    printf("FAIT \n");
    printf("Les déplacements de la règle crée sont les suivants : \n");
    struct position t_moves[r.len_changes];
    print_moves_rule(&r, r.len_changes, t_moves);
    printf("Creation d'un monde simple...");
    struct world w;
    create_basic_world(&w);
    printf("FAIT \n");
    world_disp(&w);
    printf("Rechercher du nombres de positions où s'applique la règle avec leurs "
           "indices...\n");
    struct position t_idx_positions[WIDTH * HEIGHT];
    int nb_p_matchs = test_rule_match(&w, &r, t_idx_positions);
    printf("Nombre de match = %d \n", nb_p_matchs);
    printf("Les positions sont: ");
    afficher_tableau_positions(nb_p_matchs, t_idx_positions);

    for (unsigned int j = 1; j < r.len_changes; ++j) {
        create_basic_world(&w);
        struct world w_expected;
        world_expected_after_movement(&w, &w_expected, t_moves[j].x, t_moves[j].y,
            1, 1);
        evolution_world(&w, &r, j);
        if (comparer_monde(&w, &w_expected) != 1) {
            printf("Le déplacement %d ne correspond pas à celui attendu.\n", j);
            printf("le monde généré %d \n", j);
            world_disp(&w);
            printf("le monde attendu %d \n", j);
            world_disp(&w_expected);
        }
    }

    printf("Application des changements sur le monde ...");
    // the SAND is replace by GRASS
    printf("FAIT \n");
    printf("Le nouveau monde :\n");
    world_disp(&w);
    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("Erreur : il n'a pas été entré le bon nombre de paramètres. \n");
        exit(EXIT_FAILURE);
    }

    int error = EXIT_FAILURE;

    switch (atoi(argv[1])) {
    case 1:
        error = test_rule_with_random_color();
        break;
    case 2:
        error = test_deplacements();
        break;
    default:
        error = test_rule_with_random_color();
    }
    return error;

    return 0;
}