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
	
	printLigneHaut();
  for ( y=0; y<LONG; y++ ) {
		s = format(y);
		
		/* affiche une ligne de bord */
		printLigneBord();
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
	printLigneBord();
  return 1;
}
void printLigneBord() {
	int i;
	printf("    ");
	for ( i=0; i<LARG; i++ ) {
		printf("+---");
	}
	printf("+\n");	
}
void printLigneHaut() {
	int i;
	char * s;
	printf("    ");
	for ( i=0; i<LARG; i++ ) {
		s = format(i);
		printf(" %s", s);
	}
	printf("  <- x\n");	
}
void printLigneDelimitation() {
  printf(">>> ••••••••••••••••••••••••••••••••••••••••••••••••• <<<\n");  
}
void afficherUnite( Unite * u ) {
	printf(">>> X: %d || Y: %d || clr: %c || genre: %c\n", u->posX, u->posY, u->couleur, u->genre );
}
void afficherTutoriel() {
  printLigneDelimitation();
  printf("\nCe jeu ce joue à deux joueurs.\nChaque joueur possède 2 Serfs ( représentés par un 's' ) et un Guerrier ( représenté par un 'g')\nLe jeu se déroule en tour.\nChaque tour le joueur qui commence est choisi aléatoirement.\nDurant chaque tour de jeu, on demande au joueur ce qu'il souhaite faire.\n");
  printf("Entrez les coordonnées de la case vers laquelle se deplacer / attaquer, séparées par un espace ( ex: '10 15' ), ou bien entrez '-1 -1' pour ne rien faire.\n\n");
  printLigneDelimitation();
}