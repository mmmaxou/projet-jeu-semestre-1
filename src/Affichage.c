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
  Affiche le plateau et les unites qu'il y a dessus
  Retourne un code d'erreur :
  0: ???
  1: Pas d'erreur
*/
int afficherPlateau( Monde *monde ) {
  int x,y;
	char *s;
	
	printupperline();
  for ( y=0; y<LONG; y++ ) {
		s = format(y);
		
		/* affiche une ligne de bord */
		printborderline();
		printf("%s ", s);
    for ( x=0; x<LARG; x++ ) {
      if ( monde->plateau[x][y] == NULL ) {
        printf("|   ");
      } else {
				if ( monde->plateau[x][y]->couleur == BLEU ) {
        	printf("|•%c•", monde->plateau[x][y]->genre);
				} else {
        	printf("| %c ", monde->plateau[x][y]->genre);
				}
      }
    }
    printf("|\n");
  }
	printborderline();
  return 1;
}
void printborderline() {
	int i;
	printf("    ");
	for ( i=0; i<LARG; i++ ) {
		printf("+---");
	}
	printf("+\n");	
}
void printupperline() {
	int i;
	char * s;
	printf("    ");
	for ( i=0; i<LARG; i++ ) {
		s = format(i);
		printf(" %s", s);
	}
	printf("  <- x\n");	
}
void afficherUnite( Unite * u ) {
	printf("X : %d || Y: %d || clr: %c || genre: %c\n", u->posX, u->posY, u->couleur, u->genre );
}
