#ifndef __UTILS_H__
#define __UTILS_H__

enum state {
    DEAD = 0,
    ALIVE = 16777215,
    EMPTY = 13603939,
    SAND = 5293812,
    GRASS = 1809732,
    RANDOM_COLOR = 4294967295,

    STATE_COUNT = 6,
    FIRST_STATE = DEAD
};

/** The usal modulo for positive number, for the negative number the function
 * return a positive number like for congruence */
int modulo(int x, int n);

unsigned int chose_change(unsigned int nb_change);

#endif // __UTILS_H__