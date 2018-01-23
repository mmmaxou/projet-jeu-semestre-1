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
/* Couleurs */
#define RED   "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW   "\x1B[33m"
#define BLUE   "\x1B[34m"
#define MAGENTA   "\x1B[35m"
#define CYAN   "\x1B[36m"
#define WHITE   "\x1B[37m"
#define RESET "\x1B[0m"

/*
  Affiche le plateau et les unites qu'il y a dessus
  Retourne un code d'erreur :
  0: ???
  1: Pas d'erreur
*/
int afficherPlateau( Monde * monde ) {
  int x,y;
	char *s;
	
	printLigneHaut();
  for ( y=0; y<LONG; y++ ) {
		s = format3(y);
		
		/* affiche une ligne de bord */
		printLigneBord();
		printf("%s", s);
    for ( x=0; x<LARG; x++ ) {
      if ( monde->plateau[x][y].taille == 0 ) {
        printf("|   ");
      } else {
				printf("|");
				if ( monde->plateau[x][y].premier->couleur == BLEU ) {
					printf( BLUE "%c%s" RESET , monde->plateau[x][y].premier->genre, format2(monde->plateau[x][y].premier->pv));					
				}
				if ( monde->plateau[x][y].premier->couleur == ROUGE ) {
					printf( RED "%c%s" RESET , monde->plateau[x][y].premier->genre, format2(monde->plateau[x][y].premier->pv));					
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
	printf("   ");
	for ( i=0; i<LARG; i++ ) {
		printf("+---");
	}
	printf("+\n");	
}
void printLigneHaut() {
	int i;
	char * s;
	printf("   ");
	for ( i=0; i<LARG; i++ ) {
		s = format3(i);
		printf(" %s", s);
	}
	printf("  <- x\n");	
}
void printLigneDelimitation() {
  printf(">>> ••••••••••••••••••••••••••••••••••••••••••••••••• <<<\n");  
}
void afficherUnite( Unite * u ) {
	printf( u->couleur == ROUGE ? RED : BLUE );
	printf(" > %c(%d %d) PV:%d || PM: %d || atk: %d || id: %d\n", u->genre, u->posX, u->posY, u->pv, u->pm, u->atk, u->id );
	printf( RESET );
}
void afficherTutoriel() {
  printLigneDelimitation();
  printf("\nCe jeu ce joue à deux joueurs.\nChaque joueur possède:\n• 2 Serfs 's'\n• 1 Guerrier 'g'( Bat le Serf )\n• 1 Reine 'r' ( Immobile, elle produit des unites )\n  |> La reine créer des oeufs sur une position qui lui est adjacente\n  |> Les oeufs mettent 2 tours pour éclore.\nLe jeu se déroule en tour.\nChaque tour le joueur qui commence est choisi aléatoirement.\nDurant chaque tour de jeu, on demande au joueur ce qu'il souhaite faire.\n");
  printf("Entrez les coordonnées de la case vers laquelle se deplacer / attaquer, séparées par un espace ( ex: '10 15' ), ou bien entrez '-1 -1' pour ne rien faire.\n\n");
	printf("Il peut y avoir plusieurs unites sur une même case. Cela permet de défendre certaines unites.\nPar exemple, si il y à une reine, elle sera défendue par toutes les autres unites.\nAttention, seule l'unite du dessus sera affichée dans l'interface textuelle.\n\n");
  printLigneDelimitation();
}