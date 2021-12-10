#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "world.h"

#define MAX_QUEUE_SIZE (WIDTH * HEIGHT)
/** Concrete struct representing a modifications inside a queue */
struct change {
  unsigned int i, j, idx_rule, idx_next_state;
  struct change *next;
};

/** Concrete struct representing a queue of modifications which has to be done
 * on a world */
struct queue {
  int len_list_changes;
  struct change list_changes[MAX_QUEUE_SIZE];
  struct change *first_to_do;
  struct change *first_done;
  struct change *last_to_do;
  struct change *last_done;
};

/** Create a new change */
struct change *change_create(struct queue *queue, unsigned int i,
                             unsigned int j, unsigned int idx_rule,
                             unsigned int idx_next_change);

/** Create a new modifications queue*/
void queue_init(struct queue *queue);

/** Check if a queue is empty */
int queue_is_not_empty(struct queue *queue);

/** Add a change to the end of an existing queue*/
void queue_append(struct queue *queue, unsigned int i, unsigned int j,
                  unsigned int idx_rule, unsigned int idx_next_state);

/** Remove a change to a queue and return the change*/
struct change *queue_pop(struct queue *queue);

#endif // __QUEUE_H__