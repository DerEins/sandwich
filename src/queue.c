#include "queue.h"
#include "rule.h"
#include <stdio.h>

/** Create a new change in an existing queue */
struct change* change_create(struct queue* queue, int i, int j, int idx_rule)
{
    ++(queue->len_queue);
    struct change* change = &(queue->list_changes[queue->len_queue]);
    change->i = i;
    change->j = j;
    change->idx_rule = idx_rule;
    change->next = NULL;
    return change;
}

/** Initialize attributes of an existing queue*/
void queue_init(struct queue* queue)
{
    queue->len_queue = 0;
    queue->first_to_do = NULL;
    queue->first_done = NULL;
    queue->last_to_do = NULL;
    queue->last_done = NULL;
}

/** Add a change to the end of an existing queue*/

void queue_append(struct queue* queue, int i, int j, int idx_rule)
{
    struct change* change = change_create(queue, i, j, idx_rule);

    if (queue->first_to_do == NULL) {
        queue->first_to_do = change;
    } else {
        (queue->last_to_do)->next = change;
    }
    queue->last_to_do = change;
    change->next = NULL;
}

/** Remove the first change of an existing queue and return its pointer*/
struct change* queue_pop(struct queue* queue)
{
    struct change* popped_change = queue->first_to_do;
    if (popped_change != NULL) {
        queue->first_to_do = popped_change->next;

        if (queue->first_done == NULL) {
            queue->first_done = popped_change;
        } else {
            struct change* change_tmp = queue->first_done;
            queue->first_done = popped_change;
            popped_change->next = change_tmp;
        }
    }
    return popped_change;
}
