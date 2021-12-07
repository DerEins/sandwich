#include <assert.h>
#include <stdio.h>

#include "queue.h"
#include "rule.h"

/** Create a new change in an existing queue */
struct change* change_create(struct queue* queue, unsigned int i, unsigned int j, unsigned int idx_rule, unsigned int idx_next_state)
{
    struct change* change = NULL;
    if (queue->first_done != NULL) {
        change = queue->first_done;
        queue->first_done = (queue->first_done)->next;
    } else {
        assert(queue->len_list_changes - 1 < MAX_QUEUE_SIZE);
        ++(queue->len_list_changes);
        change = &(queue->list_changes)[queue->len_list_changes];
    }
    change->i = i;
    change->j = j;
    change->idx_rule = idx_rule;
    change->idx_next_state = idx_next_state;
    change->next = NULL;
    return change;
}

/** Initialize attributes of an existing queue*/
void queue_init(struct queue* queue)
{
    queue->len_list_changes = 0;
    queue->first_to_do = NULL;
    queue->first_done = NULL;
    queue->last_to_do = NULL;
    queue->last_done = NULL;
}

/** Check if a queue is empty */
int queue_is_not_empty(struct queue* queue)
{
    return queue->first_to_do != NULL;
}

/** Add a change to the end of an existing queue*/

void queue_append(struct queue* queue, unsigned int i, unsigned int j, unsigned int idx_rule, unsigned int idx_next_state)
{
    struct change* change = change_create(queue, i, j, idx_rule, idx_next_state);

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
    if (queue_is_not_empty(queue)) {
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
