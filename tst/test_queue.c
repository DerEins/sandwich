#include "../src/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_TEST 3

/** Print a change attribute to standard output */
void change_view(struct change* change)
{
    printf("Coordonnées cellule : (%d, %d) \n", change->i, change->j);
    printf("Numéro de règle: %d \n", change->idx_rule);
}

/* Print a queue to standard output**/
void queue_view_to_do(struct queue* queue)
{
    struct change* change = queue->first_to_do;
    while (change != NULL) {
        change_view(change);
        change = change->next;
    }
}

int test_length(int len, struct queue* queue)
{
    int len_queue_test = 0;
    struct change* change_tmp = queue->first_to_do;
    while (change_tmp != NULL) {
        ++len_queue_test;
        change_tmp = change_tmp->next;
    }

    printf("Test du nombre d'éléments dans la file : ");

    if (len_queue_test == 0) {
        fprintf(stderr, "ÉCHOUÉ : la file est vide. \n");
        exit(EXIT_FAILURE);
    } else if (len_queue_test != len) {
        fprintf(stderr, "ÉCHEC : la file n'a pas le bon nombre d'éléments (%d éléments au lieu de %d).\n", len_queue_test, queue->len_queue);
        exit(EXIT_FAILURE);
    }
    printf("VALIDÉ !\n");
    return EXIT_SUCCESS;
}

int test_change_integrity(unsigned int i, unsigned int j, unsigned int idx_rule, struct change* change)
{
    printf("Test d'intégrité du changement... ");
    if (change->i != i || change->j != j || change->idx_rule != idx_rule) {
        fprintf(stderr, "ÉCHEC : Changement non-conforme à ce qui est attendu. \n");
        exit(EXIT_FAILURE);
    }
    printf("VALIDÉ ! \n");

    return EXIT_SUCCESS;
}

int test_queue_integrity(int start, unsigned int test_i[], unsigned int test_j[], unsigned int test_idx_rule[], struct queue* queue)
{
    printf("Test du bon ordre des éléments... ");
    struct change* change_tmp = queue->first_to_do;
    int i = start;
    change_tmp = queue->first_to_do;
    while (change_tmp != NULL) {
        if (i >= NB_TEST) {
            fprintf(stderr, "ÉCHEC : La liste est plus longue que prévue. \n");
            exit(EXIT_FAILURE);
        } else if (change_tmp->i != test_i[i] || change_tmp->j != test_j[i] || change_tmp->idx_rule != test_idx_rule[i]) {
        }
        ++i;
        change_tmp = change_tmp->next;
    }
    printf("VALIDÉ !\n");
    return EXIT_SUCCESS;
}

/*************** Tests ******************/

/* Test appending on queue*/
int test_append()
{
    printf("#################################################\n");
    printf("######--- TEST 1 : Ajout de changements ---######\n");
    printf("#################################################\n");

    struct queue queue_test;
    queue_init(&queue_test);

    unsigned int test_i[NB_TEST] = { 11, 12, 13 };
    unsigned int test_j[NB_TEST] = { 21, 22, 23 };
    unsigned int test_idx_rule[NB_TEST] = { 1, 2, 3 };

    printf("Début du test d'ajout... \n \n");

    /* Execution of appending changes*/
    for (int i = 0; i < NB_TEST; ++i) {
        queue_append(&queue_test, test_i[i], test_j[i], test_idx_rule[i]);
    }

    /* Beginning of tests*/

    /* Test the lenght of the queue*/
    test_length(NB_TEST, &queue_test);

    /* Test the order and the integrety of the queue*/
    test_queue_integrity(0, test_i, test_j, test_idx_rule, &queue_test);

    printf("\nVisiblement, l'ajout de changements à une file fonctionne. \n");
    printf("Voici l'état de la file à la fin du test d'ajout : \n");
    queue_view_to_do(&queue_test);

    printf("\nTest d'ajout terminé avec succès. \n \n");
    return EXIT_SUCCESS;
}

int test_pop()
{
    printf("##############################################################\n");
    printf("######--- TEST 2 : Suppression de premier changement ---######\n");
    printf("##############################################################\n");

    struct queue queue_test;
    queue_init(&queue_test);

    unsigned int test_i[NB_TEST] = { 11, 12, 13 };
    unsigned int test_j[NB_TEST] = { 21, 22, 23 };
    unsigned int test_idx_rule[NB_TEST] = { 1, 2, 3 };

    /* Test popping a change from an empty list */
    printf("Début du test de suppression ... \n \n");
    printf("Test dans le cas d'une file vide... ");

    struct change* popped_change_test = queue_pop(&queue_test);

    if (popped_change_test != NULL) {
        fprintf(stderr, "ÉCHEC : Pointeur d'un changement null non null. \n");
        exit(EXIT_FAILURE);
    }
    printf("VALIDÉ !\n");

    /* Test popping a single change*/
    printf("Test de suppression du premier changement... \n");
    /* Create changes*/
    for (int i = 0; i < 3; ++i) {
        queue_append(&queue_test, test_i[i], test_j[i], test_idx_rule[i]);
    }

    /* Pop the first change*/
    popped_change_test = queue_pop(&queue_test);
    int idx_start = 1;
    /* Test the lenght of the queue*/
    test_length(NB_TEST - 1, &queue_test);

    /* Test the integrety of the popped element */
    test_change_integrity(test_i[0], test_j[0], test_idx_rule[0], popped_change_test);

    /* Test the regularity of the queue*/
    test_queue_integrity(idx_start, test_i, test_j, test_idx_rule, &queue_test);

    printf("\nVisiblement, la suppression du premier changement d'une file fonctionne. \n");

    printf("Voici le changement supprimé : \n");
    change_view(popped_change_test);

    printf("Voici l'état de la file à la fin du test de suppression : \n");
    queue_view_to_do(&queue_test);

    printf("\nTest de suppression terminé avec succès. \n \n");
    return EXIT_SUCCESS;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Erreur : il n'a pas été entré le bon nombre de paramètres. \n");
        exit(EXIT_FAILURE);
    }

    int error = EXIT_FAILURE;

    switch (atoi(argv[1])) {
    case 1:
        error = test_append();
        break;
    case 2:
        error = test_pop();
        break;
    default:
        error = test_append() + test_pop();
    }
    return error;
}