#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#define LARG 18
#define LONG 12
#define ROUGE 'R'/* Identifiant du premier joueur */
#define BLEU 'B' /* Identifiant du deuxieme joueur */
#define SERF 's'/* Identifiant du Serf */
#define GUERRIER 'g'/* Identifiant du Guerrier */
#define REINE 'r'/* Identifiant de la Reine */
#define OEUF 'o'/* Identifiant de l'oeuf */

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
		s = format3(y);
		
		/* affiche une ligne de bord */
		printLigneBord();
		printf("%s ", s);
    for ( x=0; x<LARG; x++ ) {
      if ( monde->plateau[x][y] == NULL ) {
        printf("|    ");
      } else {
				printf("|%c%c%s", monde->plateau[x][y]->couleur, monde->plateau[x][y]->genre, format2(monde->plateau[x][y]->pv));
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
		printf("+----");
	}
	printf("+\n");	
}
void printLigneHaut() {
	int i;
	char * s;
	printf("    ");
	for ( i=0; i<LARG; i++ ) {
		s = format3(i);
		printf(" %s ", s);
	}
	printf("  <- x\n");	
}
void printLigneDelimitation() {
  printf(">>> ••••••••••••••••••••••••••••••••••••••••••••••••• <<<\n");  
}
void afficherUnite( Unite * u ) {
	printf(">>> UNITE (%d %d) >>> clr: %c || genre: %c || PM: %d || atk: %d || id: %d\n", u->posX, u->posY, u->couleur, u->genre, u->pm, u->atk, u->id );
}
void afficherTutoriel() {
  printLigneDelimitation();
  printf("\nCe jeu ce joue à deux joueurs.\nChaque joueur possède:\n• 2 Serfs 's'\n• 1 Guerrier 'g'( Bat le Serf )\n• 1 Reine 'r' ( Immobile, elle produit des unites )\n  |> La reine créer des oeufs sur une position qui lui est adjacente\n  |> Les oeufs mettent 2 tours pour éclore.\nLe jeu se déroule en tour.\nChaque tour le joueur qui commence est choisi aléatoirement.\nDurant chaque tour de jeu, on demande au joueur ce qu'il souhaite faire.\n");
  printf("Entrez les coordonnées de la case vers laquelle se deplacer / attaquer, séparées par un espace ( ex: '10 15' ), ou bien entrez '-1 -1' pour ne rien faire.\n\n");
  printLigneDelimitation();
}