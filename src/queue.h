#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "world.h"

#define MAX_QUEUE_SIZE (WIDTH * HEIGHT)
/** Concrete struct representing a modifications inside a queue */
struct change {
    unsigned int i, j, idx_rule, idx_next_state;
    struct change* next;
};

/** Create a new modifications queue*/
void queue_init();

/** Check if a queue is empty */
int queue_is_not_empty();

/** Add a change to the end of an existing queue*/
void queue_append(unsigned int i, unsigned int j, unsigned int idx_rule, unsigned int idx_next_state);

/** Remove a change to a queue and return the change*/
struct change* queue_pop();

#endif // __QUEUE_H__