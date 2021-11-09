#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "world.h"

/** Abstract struct representing a queue of moodifications */
struct queue;

/** Abstract struct representing a modicifation inside the queue */
struct change;

/** Create a new change */
struct change* queue_append(struct queue* queue, int x, int y, int idx_rule);

/** Create a new modifications queue*/
void queue_init(struct queue* queue);

/** Add a modificatvoidion to an existing queue*/
void change_add(struct queue* queue, struct change* change);

/** Remove a change to a queue*/
void change_rm(struct queue* queue, struct change* change);

/** Apply a modifications queue to an existing world*/
void change_apply(struct queue* queue, struct world* world);

#endif // __QUEUE_H__