#include <stdio.h>
#include <stdlib.h>
#include "header.h"

/* Dimensions du monde en nombre de casess */
#define LARG 18
#define LONG 12
#define ROUGE 'R'/* Identifiant du premier joueur */
#define BLEU 'B' /* Identifiant du deuxieme joueur */
#define SERF 's'/* Identifiant du Serf */
#define GUERRIER 'g'/* Identifiant du Guerrier */

int main(int argc, char *argv[]) {

  Monde monde;  
  initialiserMonde(&monde);
  remplirMonde(&monde);
	
	/* Test deplacement */
	/*
	printf("Test deplacement \n");
	deplacerUnite( monde.rouge.premier, &monde, 3, 4);
	deplacerUnite( monde.rouge.premier, &monde, -3, 4);
	deplacerUnite( monde.rouge.premier, &monde, 3, -4);
	deplacerUnite( monde.rouge.premier, &monde, 0, 0);
	afficherPlateau(&monde);
	*/
	
	/* Test suppression */
	/*
	printf("Test suppression \n");
	if ( enleverUnite( monde.bleu.premier, &monde ) == 2 ) {	
		afficherUListe(&(monde.bleu));
		afficherPlateau(&monde);
	}
	if ( enleverUnite( monde.bleu.premier, &monde ) == 2 ) {	
		afficherUListe(&(monde.bleu));
		afficherPlateau(&monde);
	}
	*/
	
	/*
		Test attaque :
		1 = Resultat : Victoire
		2 = Resultat : Defaite
		3 = Resultat : Double KO
		4 = Resultat : ERREUR : La case attaquée est vide
		5 = Resultat : ERREUR : La case attaquée est un allié
	*/
	/*
	printf("Test attaque \n");
	if ( attaquer( monde.rouge.premier->suiv->suiv, &monde, 1, 0 ) < 2 ) {
		afficherPlateau(&monde);		
	}
	if ( attaquer( monde.rouge.premier, &monde, 0, 0 ) < 2 ) {
		afficherPlateau(&monde);		
	}
	if ( attaquer( monde.rouge.premier, &monde, 0, 1 ) < 2 ) {
		afficherPlateau(&monde);		
	}
	if ( attaquer( monde.rouge.premier, &monde, 5, 5 ) < 2 ) {
		afficherPlateau(&monde);		
	}
	if ( attaquer( 
		monde.rouge.premier,
		&monde,
		monde.rouge.premier->posX,
		monde.rouge.premier->posY ) < 2 ) {
		afficherPlateau(&monde);		
	}
	*/
	
  return 0;
	
}
