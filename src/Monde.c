#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#define LARG 18
#define LONG 12
#define ROUGE 'R'/* Identifiant du premier joueur */
#define BLEU 'B' /* Identifiant du deuxieme joueur */
#define SERF 's'/* Identifiant du Serf */
#define GUERRIER 'g'/* Identifiant du Guerrier */

/*
  Initialise une variable de type Monde
*/
void initialiserMonde( Monde *monde ) {
  int x,y;
  monde->tour = 0;
  monde->rouge.premier = NULL;
  monde->bleu.premier = NULL;
  for ( x=0; x<LARG; x++) {
    for ( y=0; y<LONG; y++) {
      monde->plateau[x][y] = NULL;
    }
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
    if ( couleur == ROUGE ) {
      insertionUListe(&(monde->rouge), unite);
    } else if ( couleur == BLEU ) {
      insertionUListe(&(monde->bleu), unite);
    }
    return 1;
  }  
}

/*
  Fonction utilitaire pour remplir le monde
*/
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
  
  placerAuMonde( u1, monde, 0, 0, BLEU);
  placerAuMonde( u2, monde, 1, 0, BLEU);
  placerAuMonde( u3, monde, 0, 1, BLEU);
  placerAuMonde( u4, monde, 17, 11, ROUGE);
  placerAuMonde( u5, monde, 17, 10, ROUGE);
  placerAuMonde( u6, monde, 16, 11, ROUGE);   
}

void gererDemiTour( char joueur, Monde *monde ) {
  
}








