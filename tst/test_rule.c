#include "../src/queue.h"
#include "../src/rule_ext.h"
#include "../src/utils.h"
#include "../src/world_ext.h"
#include "utils_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Create a 2D world like a checkerboard */
void create_checkerboard(struct world* w)
{

    for (int i = 0; i < HEIGHT * WIDTH; i++) {
        if (i % 2 == 0) {
            w->t[i] = EMPTY;
        } else {
            w->t[i] = SAND;
        }
    }
}

/** Create a 2D world filled with grass for the movement test. Only one cell is yellow (SAND).*/
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

/** Compare the world excepted after a movement (dx,dy) and the one created by evolution_world (based on the application of the rules)*/
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

/** Match a yellow cell (SAND) */
int match_sand(const struct world* w, unsigned int i, unsigned int j)
{
    if (w->t[(i * WIDTH) + j] == SAND) {
        return 1;
    } else {
        return 0;
    }
}

/** Create a rule with 2 change. If the cell is yellow (SAND), the cell change into a EMPTY or GRASS */
void create_rule1(struct rule* r)
{
    r->len_changes = 2;
    r->next_state[0].next_color = EMPTY;
    r->next_state[1].next_color = GRASS;
    r->next_state[0].dx = 0;
    r->next_state[0].dy = 0;
    r->next_state[1].dx = 0;
    r->next_state[1].dy = 0;
    r->match = match_sand;
}

/** Create a rule with 9 changes, 8 movements and one change of color */
void create_rule_movements(struct rule* r)
{
    r->len_changes = 9;
    r->match = match_sand;
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
    r->next_state[0].next_color = GRASS; // change of color -> SAND to GRASD
    r->next_state[7].dx = 2;
    r->next_state[7].dy = 0;
    r->next_state[8].dx = 0;
    r->next_state[8].dy = -2;
    // The movements are the following (with (dx,dy))
    //(0,0) (1,0) (0,1) (1,1) (-1,0) (0,-1) (-1,-1) (2,0) (0,2)
}

/** Store the position of the cells matching with a rule and return the number of cells matching */
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

/** Modifies new world following the rules in the array r. */
void evolution_world(struct world* w, struct rule* r, unsigned int idx_change)
{
    queue_init();
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        struct position p;
        p.x = i / WIDTH;
        p.y = i % WIDTH;
        if (rule_match(w, r, p.x, p.y)) {
            int dx = r->next_state[idx_change].dx;
            int dy = r->next_state[idx_change].dy;
            if (dx || dy) {
                queue_append(p.x, p.y, 1, idx_change); // la rule avec l'index 1 est celle qui remplace une
                                                       // cellule par EMPTY en (i,j)
            }
            queue_append(modulo(p.x + dx, HEIGHT), modulo(p.y + dy, WIDTH), 0, idx_change);
        }
    }
    while (queue_is_not_empty()) {
        struct change* change_tmp;
        change_tmp = queue_pop();
        if (change_tmp->idx_rule == 1) // Cas particulier du deplacement avec passage de i,j en EMPTY
        {
            w->t[change_tmp->i * WIDTH + change_tmp->j] = EMPTY;
        } else {
            w->t[change_tmp->i * WIDTH + change_tmp->j] = rule_change_to(r, idx_change);
        }
    }
}

/** Test the random color for pattern*/
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
    create_checkerboard(&w_damier);
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
    evolution_world(&w_damier, &r, 1); // SAND replace by GRASS
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
        } 
    }
    printf("FAIT\n");
    printf("\nTest d'utilisation de COLOR_RANDOM termine avec succes. \n \n");
    return EXIT_SUCCESS;
}

/** Test the movements of cells */
int test_movements()
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
    // the SAND is replaced by GRASS
    printf("FAIT \n");
    printf("Le nouveau monde :\n");
    world_disp(&w);
    printf("\nTest d'utilisation des déplacements termine avec succes. \n \n");
    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    int parm = 0;
    if (argc >= 2) {
        parm = atoi(argv[1]);
    }

    int error = EXIT_FAILURE;

    switch (parm) {
    case 1:
        error = test_rule_with_random_color();
        break;
    case 2:
        error = test_movements();
        break;
    default:
        error = test_rule_with_random_color() + test_movements();
    }
    return error;
}