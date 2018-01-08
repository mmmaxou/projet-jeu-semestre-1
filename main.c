/* Programme Tableaux statiques a deux dimensions */

#include <stdio.h>
#include <stdlib.h>

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
  UListe rouge, bleu; /* Listes des deux joueurs */
  int tour; /* Numero du tour */
} Monde;

/* DECLARATIONS DES FONCTIONS */
void initialiserMonde( Monde *monde );
int creerUnite( char type, Unite *unite );
int placerAuMonde( Unite *unite, Monde *monde, int posX,int posY, char couleur );
int affichePlateau( Monde *monde );

int main(int argc, char *argv[]) {

  Monde monde;  
  Unite u1;

  initialiserMonde(&monde);

  creerUnite(SERF, &u1);
  placerAuMonde(&u1, &monde, 0, 0, BLEU);
  affichePlateau(&monde);    
  return 0;

}

/*
  Initialise une variable de type Monde
*/
void initialiserMonde( Monde *monde ) {
  int x,y;
  monde->tour = 0;
  monde->rouge = NULL;
  monde->bleu = NULL;
  for ( x=0; x<LONG; x++) {
    for ( y=0; y<LARG; y++) {
      monde->plateau[x][y] = NULL;
    }
  }
}

/*
  Cree une variable de type Unite 
  Retourne un code d'erreur :
  0: Erreur d'allocation memoire
  1: Pas d'erreur  
*/
int creerUnite( char type, Unite *unite ) {

  if ( unite != NULL ) {
    unite->genre = type;
    return 1;
  } else {
    return 0;
  }

}

/*
  Place une unite qui vient d'etre creee a la position souhaitee dans le monde sous le controle de son nouveau maitre.
  Retourne un code d'erreur :
  0: Case designee deja occupee
  1: Pas d'erreur  
*/
int placerAuMonde( Unite *unite, Monde *monde, int posX, int posY, char couleur ) {
  if ( monde->plateau[posX][posY] != NULL ) {
    return 0;
  } else {
    unite->couleur = couleur;
    unite->posX = posX;
    unite->posY = posY;
    monde->plateau[posX][posY] = unite;
    return 1;
  }  
}

/*
  Affiche le plateau et les unites qu'il y a dessus
  Retourne un code d'erreur :
  0: ???
  1: Pas d'erreur
*/
int affichePlateau( Monde *monde ) {
  int x,y;
  for ( x=0; x<LONG; x++) {
    for ( y=0; y<LARG; y++) {
      if ( monde->plateau[x][y] == NULL ) {
        printf(".");
      } else {
        printf("%c", monde->plateau[x][y]->genre);
      }
    }
    printf("\n");
  }
  return 1;
}

