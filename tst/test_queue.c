#include "../src/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int test_append(int n_test, unsigned int test_i[], unsigned int test_j[], int test_rule[], struct queue* queue_test)
{
    for (int i = 0; i < n_test; ++i) {
        queue_append(queue_test, test_i[i], test_j[i], test_rule[i]);
    }
    queue_view_to_do(queue_test);
    return EXIT_SUCCESS;
}

int test_pop(struct queue* queue_test)
{
    for (int i = 0; i < 3; ++i) {
        queue_pop(queue_test);
    }
    queue_view_to_do(queue_test);
    return EXIT_SUCCESS;
}

int main()
{
    unsigned int test_i[3] = { 11, 12, 13 };
    unsigned int test_j[3] = { 11, 12, 13 };
    int test_idx_rule[3] = { 1, 2, 3 };

    struct queue queue_test;
    queue_init(&queue_test);

    printf("########################\n");
    printf("######---TEST 1---######\n");
    printf("########################\n");
    int code_erreur_1 = test_append(3, test_i, test_j, test_idx_rule, &queue_test);

    printf("########################\n");
    printf("######---TEST 2---######\n");
    printf("########################\n");

    int code_erreur_2 = test_pop(&queue_test);
    return code_erreur_1 + code_erreur_2;
}