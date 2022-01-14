# Sandwich
## À propos du projet
Ce projet regroupe l'ensemble des travaux réalisés (sources, tests, rapport) pour répondre au [sujet Sandwich](https://www.labri.fr/perso/renault/working/teaching/projets/2021-22-S5-Sandwich.php) de semestre 5 proposé aux étudiant 1A Informatique de l'ENSEIRB-Matméca.

Il propose la simulation d'un monde fonctionnant à la manière d'un automate cellulaire et régit par des règles modifiables séparément du programme principal. Le développement de celui-ci est divisé en 5 achievements (0 à 4), tous récupérables grâce à des tags Git (voir Installation). La description de ceux-ci est disponible sur [la page du sujet](https://www.labri.fr/perso/renault/working/teaching/projets/2021-22-S5-Sandwich.php)

Le projet est exclusivement développé en C et la compilation est gérée par un Makefile. Il nécessite donc l'installation de `gcc` et de `make` pour être compilé

## Comment démarrer
### Pré-requis
* Git, pour cloner le dépôt et naviguer entre les achievements; 
* `gcc` et `make` pour la compilation des sources
* [SDL](https://www.labri.fr/perso/renault/working/teaching/projets/files/exe/sdl.linux.x86-64), pour la bibliothèque graphique, à incorporer dans le dossier contenant ce programme.

### Installation
Pour installer l'automate cellulaire : 
1. Cloner le dépôt et entrer dedans
   ```sh
   git clone https://[username]@thor.enseirb-matmeca.fr/git/projetss5-14130
   cd projetss5-14130
   ```
2. Télécharger la bibliothèque graphique SDL et la rendre exécutable
   ```sh
   wget https://www.labri.fr/perso/renault/working/teaching/projets/files/exe/sdl.linux.x86-64
   chmod u+x ./sdl.linux.x86-64
   ```
3. Compiler le projet
   ```sh
   make project
   ```

### Options de compilation
C'est au moment de la compilation qu'il faut choisir la taille du monde qui sera généré. Pour cela, on spécifie sa largeur `WIDTH` et sa hauteur `HEIGHT` au moment de la compilation avec `make` :
```sh
WIDTH=100 HEIGHT=80 make project
```

### Choix de version
La version au rendu du projet est la version `achiev4.1`, mais on peut choisir l'achievement que l'on souhaite. Pour cela, il suffit de déplacer la tête du dépôt git au bon tag avant de compiler le projet. Pour cela, on utilise :
```sh
git checkout tag
```

Voici la liste des tags disponibles :
* `achiev0`
* `achiev1.0`
* `achiev2.0`
* `achiev3.0`
* `achiev4.1`

## Utilisation
### Exécution de base
L'exécutable `./project` ainsi compilé produira les images sous formes de texte directement sur la sortie standard. Cette sortie doit être renvoyé à `sdl` à l'aide d'un pipe.
Ainsi, une exécution de base du projet se fait ainsi :
```sh
./project | ./sdl.linux.x86-64
```

Par défaut, le projet exécute un monde vide pour l'achievement 4 (branche master). Pour obtenir un résultat intéressant, on recommande d'utiliser :
```sh
./project -m 100 -s 256 | ./sdl.linux.x86-64
```

### Options
* `project -m [nombre]` : préciser le nombre d'images à calculer pour l'exécution
* `project -s [graine]` : permet de préciser une graine de génération d'un monde de départ aléatoire
* SDL peut aussi prendre des options pour gérer le défilement des images. Ceux-ci sont consultables en faisant `./sdl.linux.x86-64 -h`.

## Exécuter les tests
### Test principal
Afin de vérifier le bon fonctionnement de certaines composantes du projet, nous avons conçu des tests, dont les sources sont regroupés dans le dossier `tst/`.

Pour directement exécuter tous les tests, il suffit d'utiliser l'option `test` du `Makefile` :

```sh
make tests
```

### Tests particuliers
Si l'on souhaite juste tester certains tests, voici leur liste complète :
* Test du monde :
  * Compilation : `make test_world`
  * Exécution : `./test_world`
* Test du comportement des règles :
  * Compilation : `make test_rule`
  * Exécution :
    * Tous les tests : `./test_rule`
    * Test de règle uniquement : `./test_rule 1`
    * Test de déplacement uniquement : `./test_rule 2`
* Test du comportement de la file :
  * Compilation : `make test_queue`
  * Exécution :
    * Tous les tests : `./test_queue`
    * Test d'ajout uniquement : `./test_queue 1`
    * Test de contenance uniquement : `./test_queue 2`
    * Test de suppression uniquement : `./test_queue 3`
* Test de la gestion des conflits :
  * Compilation : `make test_conflict`
  * Exécution : `./test_conflict | ./sdl.linux.x86-64` (utilisation de `sdl` afin de voir la gestion aléatoire des conflits)

### Nettoyage du dépot
Le nettoyage du dépot de tout exécutable et autres fichiers intermédiaires à la compilation sont aisément supprimable avec :
```sh
make clean
```

## Rapport
Un compte-rendu de la réflexion et de la méthodologie utilisée pour résoudre ce sujet est disponible [ici](https://framagit.org/DerEins/projetss5-14130/-/blob/master/doc/report.pdf). Le dossier `doc/` comporte aussi les sources et figures utilisés pour sa rédaction, et il est directement compilable via make avec :
```sh
make doc
```

## Auteurs
**Marine Vovard** - mvovard@bordeaux-inp.fr
**Mathieu Dupoux** - mdupoux@bordeaux-inp.fr

Lien du projet : [https://framagit.org/DerEins/projetss5-14130](https://framagit.org/DerEins/projetss5-14130)

## Remerciements
Un grand merci aux équipes pédagogiques qui nous ont accompagnés dans ce projet. Vos précieux conseils nous ont permis de mener ce projet à un stade aussi avancé.
