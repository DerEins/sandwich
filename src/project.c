#include "queue.h"
#include "rule.h"
#include "utils.h"
#include "world.h"
#include <assert.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

extern char *optarg;

struct world world_init();

void world_disp(struct world *w);

void construct_t_conflicts(struct conflict* t)
{
    for (int i = 0; i < WIDTH * HEIGHT; ++i) {
        t[i].conflict_to_process = 0;
        t[i].nb_conflicts = 0;
    }
}

int solve_conflict(struct conflict t_conflicts[], unsigned int i, unsigned int j)
{
    struct conflict c = t_conflicts[i * WIDTH + j];
    int random = rand();
    if (c.nb_conflicts == 0) { // le conflit a été géré
        return 0;
        fprintf(stderr, "Conflit perdant en %d %d car nb_conflicts =0\n", i, j);
    } else if (c.conflict_to_process == 1) // si il n'y a qu'un 'conflit' (c'est plus un conflit du coup mais bon ...)
    {
        return 1;
    } else if ((random % c.nb_conflicts) == 0) // 1 chance sur le nb de conflit d'accepter ce conflit
    {
        t_conflicts[i * WIDTH + j].nb_conflicts = 0;
        return 1;
    } else {
        assert(t_conflicts[i * WIDTH + j].conflict_to_process != 0);
        t_conflicts[i * WIDTH + j].conflict_to_process -= 1;
        fprintf(stderr, "Conflit perdant en %d %d car perd au tirage random.\n", i, j);
        fprintf(stderr, "Conflict to process %d\n", c.conflict_to_process);
        return 0;
    }
}

void world_apply_rule(struct world *w, struct rule *r, int i, int j,
                      unsigned int idx_change, struct conflict t_conflicts[]) {
    unsigned int dx = rule_change_dx(r, idx_change);
    unsigned int dy = rule_change_dy(r, idx_change);
    int s = solve_conflict(t_conflicts, modulo(i + dx, HEIGHT), modulo(j + dy, WIDTH));
    if (s) {
        if (dx || dy) {
            w->t[modulo(i + dx, HEIGHT) * WIDTH + modulo(j + dy, WIDTH)] = rule_change_to(r, idx_change);
            w->t[i * WIDTH + j] = EMPTY;
        }
    } else {
        w->t[i * WIDTH + j] = rule_change_to(r, idx_change);
    }
}

unsigned int chose_change(unsigned int nb_change) {
  unsigned int r = rand();
  return r % nb_change;
}

int main(int argc, char *argv[]) {
  // Gestion des options -s et -m
  if (argc == 2 || argc == 4 || argc > 5) {
    fprintf(stderr,
            "Erreur : il n'a pas été entré le bon nombre de paramètres.\n");
    return EXIT_FAILURE;
  }
  char input_opt = getopt(argc, argv, "m:s:");
  char opt = 0;
  int seed = 43, nb_pictures = 10;
  while (input_opt != -1) {
    switch (input_opt) {
    case 's':
      opt = 's';
      seed = atoi(optarg);
      break;
    case 'm':
      nb_pictures = atoi(optarg);
      break;
    default: /* '?' */
      break;
    }
    input_opt = getopt(argc, argv, "s:");
  }

  struct world w;
  w = world_init(opt, seed);
  srand(seed);
  rules_init();
  printf("%d %d\n", WIDTH, HEIGHT);
  for (int i = 0; i < nb_pictures; i++) {
    struct conflict t_conflicts[WIDTH * WIDTH];
    construct_t_conflicts(t_conflicts);
    struct queue q;
    queue_init(&q);
    for (unsigned int k = 0; k < HEIGHT; k++) {
      for (unsigned int l = 0; l < WIDTH; l++) {
        for (unsigned int j = 1; j < rules_count(); ++j) {
          struct rule *r = rule_get(j);
          if (rule_match(&w, r, k, l)) {
            unsigned int idx_change =
                chose_change(rule_num_changes(rule_get(j)));
            int dx_tmp = rule_change_dx(rule_get(j), idx_change);
            int dy_tmp = rule_change_dy(rule_get(j), idx_change);
            int index_tmp =
                modulo(k + dx_tmp, HEIGHT) * WIDTH + modulo(l + dy_tmp, WIDTH);
            if (w.t[index_tmp] == EMPTY && (dx_tmp || dy_tmp)) {
                t_conflicts[index_tmp].nb_conflicts = t_conflicts[index_tmp].nb_conflicts + 1;
                t_conflicts[index_tmp].conflict_to_process = t_conflicts[index_tmp].conflict_to_process + 1;
                queue_append(&q, k, l, j, idx_change);
            } else if (!(dx_tmp || dy_tmp)) {
                t_conflicts[index_tmp].nb_conflicts = t_conflicts[index_tmp].nb_conflicts + 1;
                t_conflicts[index_tmp].conflict_to_process = t_conflicts[index_tmp].conflict_to_process + 1;
                queue_append(&q, k, l, j, idx_change);
            } else {
                fprintf(stderr, "Conflit perdant en %d %d car déplacement dans une case non vide.\n", k + dx_tmp, j = dy_tmp);
            }
            break;
          }
        }
      }
    }
    while (queue_is_not_empty(&q)) {
        struct change* change_tmp;
        change_tmp = queue_pop(&q);
        world_apply_rule(&w, rule_get(change_tmp->idx_rule), change_tmp->i, change_tmp->j, change_tmp->idx_next_state, t_conflicts);
    }
    world_disp(&w);
  }
  return 0;
}
