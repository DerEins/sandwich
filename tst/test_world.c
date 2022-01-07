#include "../src/world_ext.h"
#include "utils_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int test_world_init(char opt, int seed1, int seed2, int nb_tests)
{
    printf("###############################################################\n");
    printf("######--- TEST 1: Initialisation d'un monde aleatoire ---######\n");
    printf("###############################################################\n");
    printf("Initialisation d'un monde ...");
    struct world w1;
    w1 = world_init(opt, seed1);
    printf("VALIDE !\n");
    printf("Initialisation d'un deuxieme monde aleatoire ...");
    struct world w2;
    w2 = world_init(opt, seed2);
    printf("VALIDE !\n");
    printf("Test du caractere aleatoire d'un monde ...");
    if (comparer_monde(&w1, &w2)) {
        int i = 0;
        while (comparer_monde(&w1, &w2) && (i < nb_tests)) {
            printf("Tentative %d ...\n", i);
            w2 = world_init(opt, seed2);
            ++i;
        }
        fprintf(stderr,
            "ECHOUE : Les mondes ne sont pas generes de maniere aleatoire \n");
        exit(EXIT_FAILURE);
    }
    printf("VALIDE !\n");
    printf("\nTest d'initialisation d'un monde termine avec succes. \n \n");
    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("Erreur : il n'a pas été entré le bon nombre de paramètres. \n");
        exit(EXIT_FAILURE);
    }

    int error = EXIT_FAILURE;

    switch (atoi(argv[1])) {
    case 1:
        error = test_world_init('s', 42, 33, 10); // test with 2 different seeds for random number (42 and 33)
        break;
    default:
        error = test_world_init('s', 42, 33, 10);
    }
    return error;
}