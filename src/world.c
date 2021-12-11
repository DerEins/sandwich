#include "world.h"
#include "rule.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

enum state;

/** Create a new world with value 0 (and I want random value)*/
struct world world_init(char opt, int seed)
{
    srand(seed);
    struct world w;
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        w.t[i] = EMPTY;
    }
    if (opt == 's') {
        for (int i = 0; i < WIDTH * HEIGHT; i++) {
            int r = rand() % (STATE_COUNT);
            switch (r) {
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
        }
    } else {
        int x_mid = HEIGHT / 2;
        int y_mid = WIDTH / 2;
        int i = 1;
        int j = 1;
        w.t[x_mid * WIDTH + (y_mid - j)] = GRASS;
        w.t[x_mid * WIDTH + (y_mid + j)] = GRASS;
        while ((x_mid - i) > 1 && (y_mid - j) > 1) {
            w.t[(x_mid + i) * WIDTH + (y_mid - j)] = GRASS;
            w.t[(x_mid + i) * WIDTH + (y_mid + j)] = GRASS;
            w.t[(x_mid - i) * WIDTH + (y_mid - j)] = GRASS;
            w.t[(x_mid - i) * WIDTH + (y_mid + j)] = GRASS;
            for (int k = (x_mid - i) * WIDTH + (y_mid - j) + 1; k < (x_mid - i) * WIDTH + (y_mid + j); k++) {
                w.t[k] = SAND;
            }
            i++;
            j++;
        }
        int k = (x_mid + i) * WIDTH + (y_mid - j) + WIDTH / 8; // améliorer le WIDTH/8
        while (k < (x_mid + i) * WIDTH + (y_mid + j) - WIDTH / 8) {
            w.t[k] = GRASS;
            k++;
        }
    }
    return w;
}

/** SAND FALL
 *   for (int i = 0; i < WIDTH * HEIGHT; i++) {
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
  } */

/** Display a world according to the rules specified*/
void world_disp(struct world* w)
{
    printf("#\n");
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        if ((i % WIDTH) == (WIDTH - 1)) {
            printf("%d \n", w->t[i]);
        } else
            printf("%d ", w->t[i]);
    }
}
