#ifndef __RULE_EXT_H__
#define __RULE_EXT_H__

#include "rule.h"

#define NB_NEIGHBORS 9
#define MAX_RULE 2
#define MAX_STATE 50

struct next_state {
    unsigned int next_color;
    int dx, dy;
};

struct rule {
    int (*match)(const struct world*, unsigned int, unsigned int);
    unsigned int len_changes;
    struct next_state next_state[MAX_STATE];
};

#endif // __RULE_EXT_H__
