#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "world.h"

/** Concrete struct representing a modifications inside a queue */
struct change {
    unsigned int i, j, idx_rule;
    struct change* next;
};

/** Concrete struct representing a queue of modifications which has to be done on a world */
struct queue {
    int len_queue;
    struct change list_changes[WIDTH * HEIGHT];
    struct change* first_to_do;
    struct change* first_done;
    struct change* last_to_do;
    struct change* last_done;
};

/** Create a new change */
struct change* change_create(struct queue* queue, int i, int j, int idx_rule);

/** Create a new modifications queue*/
void queue_init(struct queue* queue);

/** Add a change to the end of an existing queue*/
void queue_append(struct queue* queue, int i, int j, int idx_rule);

/** Remove a change to a queue and return the change*/
struct change* queue_pop(struct queue* queue);

#endif // __QUEUE_H__