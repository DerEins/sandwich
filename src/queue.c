#include "queue.h"
#include "rule.h"
#include <stdio.h>

/** Concrete struct representing a queue of modifications which has to be done on a world */
struct change {
    int x;
    int y;
    int idx_rule;
    struct change* next;
};

struct queue {
    int len_queue;
    struct change list_changes[WIDTH * HEIGHT];
    struct change* first_to_do;
    struct change* first_done;
};

struct change* queue_append(struct queue* queue, int idx_rule, int x, int y)
{
    ++(queue->len_queue);
    struct change* change = &(queue->list_changes[queue->len_queue]);
    change->idx_rule = idx_rule;
    change->x = x;
    change->y = y;
    change->next = NULL;
    return change;
}

void queue_init(struct queue* queue)
{
    queue->len_queue = 0;
    queue->first_to_do = NULL;
    queue->first_done = NULL;
}

void change_add(struct queue* queue, struct change* change)
{
    if (queue->first_to_do == NULL) {
        queue->first_to_do = change;
    } else {
        struct change* change_tmp = queue->first_to_do;
        queue->first_to_do = change;
        change->next = change_tmp;
    }
}

void change_remove(struct queue* queue, struct change* change)
{
    struct change* previous_change = queue->first_to_do;
    while (previous_change->next != change) {
        previous_change = previous_change->next;
    }
    previous_change->next = change->next;

    if (queue->first_done == NULL) {
        queue->first_done = change;
    } else {
        struct change* change_tmp = queue->first_done;
        queue->first_done = change;
        change->next = change_tmp;
    }
}