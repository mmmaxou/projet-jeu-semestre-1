#include <stdio.h>
#include <stdlib.h>
#include "header.h"

/* Dimensions du monde en nombre de casess */
#define LONG 12
#define LARG 18
#define ROUGE 'R'/* Identifiant du premier joueur */
#define BLEU 'B' /* Identifiant du deuxieme joueur */
#define SERF 's'/* Identifiant du Serf */
#define GUERRIER 'g'/* Identifiant du Guerrier */

int main(int argc, char *argv[]) {

  Monde monde;  
  initialiserMonde(&monde);
  remplirMonde(&monde);
  afficherPlateau(&monde);    
  afficherUListe(&(monde.rouge));
	
	/* Test deplacement */
	deplacerUnite( monde.rouge.premier, &monde, 3, 4);
	deplacerUnite( monde.rouge.premier, &monde, -3, 4);
	deplacerUnite( monde.rouge.premier, &monde, 3, -4);
	deplacerUnite( monde.rouge.premier, &monde, 0, 0);
	afficherPlateau(&monde);
	
	/* Test suppression */
	if ( enleverUnite( monde.bleu.premier, &monde ) == 2 ) {	
		afficherUListe(&(monde.bleu));
		afficherPlateau(&monde);
	}
	if ( enleverUnite( monde.bleu.premier, &monde ) == 2 ) {	
		afficherUListe(&(monde.bleu));
		afficherPlateau(&monde);
	}
  return 0;
	
}
