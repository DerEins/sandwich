#include "conflict.h"
#include "rule.h"
#include "utils.h"
#include "world_ext.h"
#include <stdio.h>
#include <stdlib.h>

enum state;

/** Create a new world for the game of life*/
struct world world_init(char opt, int seed)
{
    srand(seed);
    struct world w;
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        w.t[i] = ALIVE;
    }
    if (opt == 's') {
        for (int i = 0; i < WIDTH * HEIGHT; i++) {
            int r = rand() % (10);
            switch (r) {
            case 0:
                w.t[i] = ALIVE;
                break;
            case 1:
                w.t[i] = DEAD;
                break;
            default:
                w.t[i] = DEAD;
            }
        }
    } else {
        int x_mid = HEIGHT / 2;
        int y_mid = WIDTH / 2;
        int i = 1;
        int j = 1;
        w.t[x_mid * WIDTH + (y_mid - j)] = ALIVE;
        w.t[x_mid * WIDTH + (y_mid + j)] = ALIVE;
        while ((x_mid - i) > 1 && (y_mid - j) > 1) {
            w.t[(x_mid + i) * WIDTH + (y_mid - j)] = ALIVE;
            w.t[(x_mid + i) * WIDTH + (y_mid + j)] = ALIVE;
            w.t[(x_mid - i) * WIDTH + (y_mid - j)] = ALIVE;
            w.t[(x_mid - i) * WIDTH + (y_mid + j)] = ALIVE;
            for (int k = (x_mid - i) * WIDTH + (y_mid - j) + 1; k < (x_mid - i) * WIDTH + (y_mid + j); k++) {
                w.t[k] = ALIVE;
            }
            i++;
            j++;
        }
        int k = (x_mid + i) * WIDTH + (y_mid - j) + WIDTH / 8; // améliorer le WIDTH/8
        while (k < (x_mid + i) * WIDTH + (y_mid + j) - WIDTH / 8) {
            w.t[k] = DEAD;
            k++;
        }
    }
    return w;
}

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

void world_apply_rule(struct world* w, struct rule* r, int i, int j,
    unsigned int idx_change, struct conflict t_conflicts[])
{
    unsigned int dx = rule_change_dx(r, idx_change);
    unsigned int dy = rule_change_dy(r, idx_change);
    int s = solve_conflict(t_conflicts, modulo(i + dx, HEIGHT), modulo(j + dy, WIDTH));
    if (s) { //if the change wins the conflict
        if (dx || dy) { // movement
            w->t[modulo(i + dx, HEIGHT) * WIDTH + modulo(j + dy, WIDTH)] = rule_change_to(r, idx_change);
            w->t[i * WIDTH + j] = DEAD; //the cell where the particule was become empty
        } else { //change of color
            w->t[i * WIDTH + j] = rule_change_to(r, idx_change);
        }
    } 
}