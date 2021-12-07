#ifndef __UTILS_H__
#define __UTILS_H__

enum state {
    EMPTY = 13603939,
    SAND = 5293812,
    GRASS = 1809732,
    RANDOM_COLOR = 4294967295,
    STATE_COUNT = 4,
    FIRST_STATE = EMPTY
};

struct conflict{
    unsigned int nb_conflicts;
    unsigned int conflict_to_process;
};

/** The usal modulo for positive number, for the negative number the function return a positive number like for congruence */
int modulo(int x, int n);

#endif // __UTILS_H__