#ifndef __UTILS_H__
#define __UTILS_H__

/** Enumeration of color for a cell */
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

/** Usual modulo for positive number. For negative number, return a positive number */
int modulo(int x, int n);

/** Chose which change to apply after matching a rule and a cell. The choice is made with an equal probability.*/
unsigned int chose_change(unsigned int nb_change);

#endif // __UTILS_H__