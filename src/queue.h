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
};

/** Create a new change */
struct change* change_create(struct queue* queue, int i, int j, int idx_rule);

/** View a change queue */
void change_view(struct change* change);

/** Create a new modifications queue*/
void queue_init(struct queue* queue);

/** Add a modificatvoidion to an existing queue*/
void queue_append(struct queue* queue, int i, int j, int idx_rule);

/** */
void queue_get_first_change(struct queue* queue);

/** List all element of a queue*/
void queue_view_to_do(struct queue* queue);

/** Remove a change to a queue*/
void queue_pop(struct queue* queue);

/** Apply a modifications queue to an existing world*/
void change_apply(struct queue* queue);

#endif // __QUEUE_H__