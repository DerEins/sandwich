#ifndef __RULE_EXT_H__
#define __RULE_EXT_H__

#include "rule.h"

#define NB_NEIGHBORS 9
#define MAX_RULE 2
#define MAX_STATE 20 // the number of changes possible for a rule

/** Concrete struct representing the next state of a cell*/
struct next_state {
    unsigned int next_color;
    int dx, dy;
};

/** Concrete struct representing a rule for a cellular automaton */
struct rule {
    int (*match)(const struct world*, unsigned int, unsigned int);
    unsigned int len_changes;
    struct next_state next_state[MAX_STATE];
};

#endif // __RULE_EXT_H__
