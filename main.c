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
void remplirMonde ( Monde *monde );

int main(int argc, char *argv[]) {

  Monde monde;  
  initialiserMonde(&monde);
  remplirMonde(&monde);
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

void remplirMonde ( Monde *monde ) {
  Unite *u1 = malloc(sizeof(*u1));
  Unite *u2 = malloc(sizeof(*u2));
  Unite *u3 = malloc(sizeof(*u3));
  Unite *u4 = malloc(sizeof(*u4));
  Unite *u5 = malloc(sizeof(*u5));
  Unite *u6 = malloc(sizeof(*u6));
  
  creerUnite(GUERRIER, u1);
  creerUnite(SERF, u2);
  creerUnite(SERF, u3);
  creerUnite(GUERRIER, u4);
  creerUnite(SERF, u5);
  creerUnite(SERF, u6);
  placerAuMonde(u1, monde, 0, 0, BLEU);
  placerAuMonde(u2, monde, 1, 0, BLEU);
  placerAuMonde(u3, monde, 0, 1, BLEU);
  placerAuMonde(u4, monde, LONG-1, LARG-1, ROUGE);
  placerAuMonde(u5, monde, LONG-2, LARG-1, ROUGE);
  placerAuMonde(u6, monde, LONG-1, LARG-2, ROUGE);  
}

