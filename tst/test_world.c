#include "../src/queue.h"
#include "../src/rule.h"
#include "../src/world.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define B 16777215

struct world world_init(char opt, int seed);

void world_disp(struct world *w);

int compare_cte_array(int n, const unsigned int t1[], unsigned int t2[]) {
  for (int i = 0; i < n; i++) {
    if (t1[i] != t2[i]) {
      return 0;
    }
  }
  return 1;
}

// Comment tester la longueur d'un tableau ?
int test_world_init(char opt, int seed1, int seed2, int nb_tests) {
  printf("###############################################################\n");
  printf("######--- TEST 1: Initialisation d'un monde aleatoire ---######\n");
  printf("###############################################################\n");
  printf("Initialisation d'un monde ...");
  struct world w1;
  w1 = world_init(
      opt, seed1); // peut-on mettre une exceptions si l'appel de la fonction
                   // retourne une erreur et ne veut pas compiler ?
  printf("VALIDE !\n");
  printf("Test de l'etat des cellules (blanches ou noires) et de la taille du "
         "tableau de world....");
  int b = 1;
  for (int i = 0; i < WIDTH * HEIGHT; i++) {
    if (w1.t[i] != 0 && w1.t[i] != B) {
      b = 0;
    }
  }
  if (b == 0) {
    fprintf(stderr, "ÉCHOUÉ : il y a une valeur qui n'appartient pas à "
                    "l'ensemble {O,B} \n");
    exit(EXIT_FAILURE);
  }
  printf("VALIDE !\n");
  printf("Initialisation d'un deuxieme monde aleatoire ...");
  struct world w2;
  w2 = world_init(opt, seed2);
  printf("VALIDE !\n");
  printf("Test du caractere aleatoire d'un monde ...");
  if (compare_cte_array(WIDTH * HEIGHT, w1.t, w2.t)) {
    int i = 0;
    while (compare_cte_array(WIDTH * HEIGHT, w1.t, w2.t) && (i < nb_tests)) {
      printf("Tentative %d ...\n", i);
      w2 = world_init(opt, seed2); // est-ce que je dois changer la seed ?
      ++i;
    }
    fprintf(stderr,
            "ECHOUE : Les mondes ne sont pas generes de maniere aleatoire \n");
    // ajouter le test de l'option s !
    exit(EXIT_FAILURE);
  }
  printf("VALIDE !\n");
  printf("\nTest d'initialisation d'un monde termine avec succes. \n \n");
  return EXIT_SUCCESS;
}

// Faire un test world display a partir d'un modele deja existant (ou regarder
// les espaces, les #,...)

/*************** Tests ******************/

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Erreur : il n'a pas été entré le bon nombre de paramètres. \n");
    exit(EXIT_FAILURE);
  }

  int error = EXIT_FAILURE;

  switch (atoi(argv[1])) {
  case 1:
    error = test_world_init('s', 42, 33, 10); // seed1=42 et seed2=33
    break;
  default:
    error = test_world_init('s', 42, 33, 10);
  }
  return error;
}