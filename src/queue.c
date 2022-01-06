#include <assert.h>
#include <stdio.h>

#include "queue.h"

// Structures
/** Concrete struct representing a queue of modifications which has to be done
 * on a world */

struct queue {
    int len_list_changes;
    struct change list_changes[MAX_QUEUE_SIZE];
    struct change* first_to_do;
    struct change* first_done;
    struct change* last_to_do;
};

// Global variables
/** The declaration of the queue*/
static struct queue queue;

// Intern functoions
/** Create a new change in an existing queue */
struct change* change_create(unsigned int i,
    unsigned int j, unsigned int idx_rule,
    unsigned int idx_next_state)
{
    struct change* change = NULL;
    if (queue.first_done != NULL) {
        change = queue.first_done;
        queue.first_done = (queue.first_done)->next;
    } else {
        assert(queue.len_list_changes - 1 < MAX_QUEUE_SIZE);
        ++(queue.len_list_changes);
        change = &(queue.list_changes)[queue.len_list_changes];
    }
    change->i = i;
    change->j = j;
    change->idx_rule = idx_rule;
    change->idx_next_state = idx_next_state;
    change->next = NULL;
    change->idx_next_state = idx_next_state;
    return change;
}

// Test functions (prototypes in test_queue.c)
struct change* get_first_to_do()
{
    return queue.first_to_do;
}

int get_nb_changes()
{
    return queue.len_list_changes;
}

// Queue methods
/** Initialize attributes of the queue*/
void queue_init()
{
    queue.len_list_changes = 0;
    queue.first_to_do = NULL;
    queue.first_done = NULL;
    queue.last_to_do = NULL;
}

/** Check if the queue is empty */
int queue_is_not_empty()
{
    return queue.first_to_do != NULL;
}

/** Add a change to the end of the queue*/

void queue_append(unsigned int i, unsigned int j, unsigned int idx_rule, unsigned int idx_next_state)
{
    struct change* change = change_create(i, j, idx_rule, idx_next_state);

    if (queue.first_to_do == NULL) {
        queue.first_to_do = change;
    } else {
        (queue.last_to_do)->next = change;
    }
    queue.last_to_do = change;
    change->next = NULL;
}

/** Remove the first change of the queue and return its pointer*/
struct change* queue_pop()
{
    struct change* popped_change = queue.first_to_do;
    if (queue_is_not_empty()) {
        queue.first_to_do = popped_change->next;

        if (queue.first_done == NULL) {
            queue.first_done = popped_change;
        } else {
            struct change* change_tmp = queue.first_done;
            queue.first_done = popped_change;
            popped_change->next = change_tmp;
        }
    }
    return popped_change;
}
