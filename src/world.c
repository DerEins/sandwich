#include "world.h"
#include "rule.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

enum state;

/** Create a new world with value 0 (and I want random value)*/
struct world world_init(char opt, int seed) {
  srand(seed);
  struct world w;
  for (int i = 0; i < WIDTH * HEIGHT; i++) {
    if (opt == 's') {
      switch (rand() % STATE_COUNT + 3) {
      case 1:
        w.t[i] = EMPTY;
        break;
      case 2:
        w.t[i] = SAND;
        break;
      case 3:
        w.t[i] = GRASS;
        break;
      default:
        w.t[i] = EMPTY;
      }
    } else {
      if (i < WIDTH * 3 && rand() % 5 == 0) {
        w.t[i] = SAND;
      } else if (i >= (WIDTH * (HEIGHT - 1) + (WIDTH) / 2) ||
                 (i >= WIDTH * (HEIGHT - 1) &&
                  i <= (WIDTH * (HEIGHT - 1) + WIDTH / 3))) {
        w.t[i] = GRASS;
      } else {
        w.t[i] = EMPTY;
      }
    }
  }
  return w;
}

/** Display a world according to the rules specified*/
void world_disp(struct world *w) {
  printf("#\n");
  for (int i = 0; i < WIDTH * HEIGHT; i++) {
    if ((i % WIDTH) == (WIDTH - 1)) {
      printf("%d \n", w->t[i]);
    } else
      printf("%d ", w->t[i]);
  }
}
