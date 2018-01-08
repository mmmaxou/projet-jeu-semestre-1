/* Programme Tableaux statiques a deux dimensions */

#include <stdio.h>

/* Dimensions du monde en nombre de casess */
#define LONG 12
#define LARG 18
#define ROUGE 'R'/* Identifiant du premier joueur */
#define BLEU 'B' /* Identifiant du deuxieme joueur */
#define SERF 's'/* Identifiant du Serf */
#define GUERRIER 'g'/* Identifiant du Guerrier */

/* STRUCTURES */
typedef struct unite{
  int posX, posY; /* Pour stocker les coordonnees de l'unite*/
  char couleur; /* ROUGE ou BLEU */
  char genre; /* GUERRIER ou SERF*/
  struct unite *suiv; /* liste des unites suivantes*/
} Unite;
typedef Unite* UListe;
typedef struct monde{
Unite *plateau[LONG][LARG];
int tour; /* Numero du tour */
UListe rouge, bleu; /* Listes des deux joueurs */
} Monde;

/* DECLARATIONS DES FONCTIONS */
void initialiserMonde( Monde *monde );

int main(int argc, char *argv[]) {

  Monde monde;
  
  initialiserMonde(&monde);
  return 0;
  
}

/* Initialise une variable de type Monde*/
void initialiserMonde( Monde *monde ) {
  int x,y;
  monde->tour = 0;
  monde->rouge = NULL;
  monde->bleu = NULL;
  for ( x=0; x<LONG; x++) {
    for ( y=0; y<LONG; y++) {
      monde->plateau[x][y] = NULL;
    }
  }
}


