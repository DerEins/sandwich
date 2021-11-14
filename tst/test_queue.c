#include "../src/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int test_append(int n_test, unsigned int test_i[], unsigned int test_j[], int test_rule[], struct queue* queue_test)
{
    for (int i = 0; i < n_test; ++i) {
        queue_append(queue_test, test_i[i], test_j[i], test_rule[i]);
    }
    return EXIT_SUCCESS;
}

int test_pop(struct queue* queue_test)
{
    queue_pop(queue_test);
    return EXIT_SUCCESS;
}

int test_apply(struct queue* queue_test)
{
    while (queue_test->first_to_do != NULL) {
        change_view(queue_test->first_to_do);
        queue_pop(queue_test);
    }
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Erreur : il n'a pas été entré le bon nombre de paramètres. \n");
        return EXIT_FAILURE;
    }

    unsigned int test_i[3] = { 11, 12, 13 };
    unsigned int test_j[3] = { 11, 12, 13 };
    int test_idx_rule[3] = { 1, 2, 3 };

    struct queue queue_test;
    queue_init(&queue_test);

    int error = EXIT_FAILURE;

    switch (atoi(argv[1])) {
    case 1:
        printf("########################\n");
        printf("######---TEST 1---######\n");
        printf("########################\n");
        error = test_append(3, test_i, test_j, test_idx_rule, &queue_test);
        break;
    case 2:
        printf("########################\n");
        printf("######---TEST 2---######\n");
        printf("########################\n");
        error = test_append(3, test_i, test_j, test_idx_rule, &queue_test) + test_pop(&queue_test);
        break;
    case 3:
        printf("########################\n");
        printf("######---TEST 3---######\n");
        printf("########################\n");
        error = test_append(3, test_i, test_j, test_idx_rule, &queue_test) + test_apply(&queue_test);
        break;
    default:
        printf("Erreur : Il a été entré un mauvais numéro de test. \n");
        return 1;
    }
    queue_view_to_do(&queue_test);
    return error;
}