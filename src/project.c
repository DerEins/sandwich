#include "conflict.h"
#include "queue.h"
#include "rule.h"
#include "utils.h"
#include "world_ext.h"
#include <assert.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

extern char* optarg;

int main(int argc, char* argv[])
{
    // Options -s et -m
    if (argc == 2 || argc == 4 || argc > 5) {
        fprintf(stderr,
            "Erreur : il n'a pas été entré le bon nombre de paramètres.\n");
        return EXIT_FAILURE;
    }
    char input_opt = getopt(argc, argv, "m:s:");
    char opt = 0;
    int seed = 43, nb_pictures = 10; // values by default
    while (input_opt != -1) {
        switch (input_opt) {
        case 's':
            opt = 's';
            seed = atoi(optarg);
            break;
        case 'm':
            nb_pictures = atoi(optarg);
            break;
        default:
            break;
        }
        input_opt = getopt(argc, argv, "s:");
    }
    
    // Creation of the world and the rules
    struct world w;
    w = world_init(opt, seed);
    srand(seed);
    rules_init();
    printf("%d %d\n", WIDTH, HEIGHT);
    world_disp(&w);
    
    for (int i = 0; i < nb_pictures; i++) { // for each picture do the following
        
        // Creation of a queue and an array keeping the conflicts
        struct conflict t_conflicts[WIDTH * WIDTH]; 
        construct_t_conflicts(t_conflicts);
        queue_init();
        for (unsigned int k = 0; k < HEIGHT; k++) {
            for (unsigned int l = 0; l < WIDTH; l++) { // for each cells of the image
                for (unsigned int j = 0; j < rules_count(); ++j) {
                    struct rule* r = rule_get(j);
                    if (rule_match(&w, r, k, l)) { //if the rule match with the cell
                        unsigned int idx_change = chose_change(rule_num_changes(rule_get(j))); // randomly chose a change to apply
                        int dx_tmp = rule_change_dx(rule_get(j), idx_change);
                        int dy_tmp = rule_change_dy(rule_get(j), idx_change);
                        int index_tmp = modulo(k + dx_tmp, HEIGHT) * WIDTH + modulo(l + dy_tmp, WIDTH);
                        if (w.t[index_tmp] == DEAD && (dx_tmp || dy_tmp)) { // if the cell is empty and the change is a movement
                            t_conflicts[index_tmp].nb_conflicts = t_conflicts[index_tmp].nb_conflicts + 1;
                            t_conflicts[index_tmp].conflict_to_process = t_conflicts[index_tmp].conflict_to_process + 1;
                            queue_append(k, l, j, idx_change);
                        } else if (!(dx_tmp || dy_tmp)) {
                            t_conflicts[index_tmp].nb_conflicts = t_conflicts[index_tmp].nb_conflicts + 1;
                            t_conflicts[index_tmp].conflict_to_process = t_conflicts[index_tmp].conflict_to_process + 1;
                            queue_append(k, l, j, idx_change);
                        } // else do nothing because the cell can't move to a cell not empty
                        //else {
                           // fprintf(stderr, "Conflit perdant en %d %d car déplacement dans une case non vide.\n", k + dx_tmp, j = dy_tmp);
                        //}
                        break;
                    }
                }
            }
        }

        // Remove and apply all the changes from the queue
        while (queue_is_not_empty()) {
            struct change* change_tmp;
            change_tmp = queue_pop();
            world_apply_rule(&w, rule_get(change_tmp->idx_rule), change_tmp->i, change_tmp->j, change_tmp->idx_next_state, t_conflicts);
        }
        world_disp(&w);
    }
    return 0;
}
