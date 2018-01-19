#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#define LONG 12
#define LARG 18
#define ROUGE 'R'/* Identifiant du premier joueur */
#define BLEU 'B' /* Identifiant du deuxieme joueur */
#define SERF 's'/* Identifiant du Serf */
#define GUERRIER 'g'/* Identifiant du Guerrier */


/*
  Insere une nouvelle unite dans une liste
*/
void insertionUListe ( UListe * liste, Unite * unite ) {
  if ( liste->premier == NULL ) {
    liste->premier = unite;
  } else {
    unite->suiv = liste->premier;
    liste->premier = unite;
  }
}

/*
  Fonction utilitaire pour afficher une liste
*/
void afficherUListe ( UListe * liste ) {
  Unite * actuel = liste->premier;
  
  while ( actuel != NULL ) {
    printf("%c -> ", actuel->genre);
    actuel = actuel->suiv;
  }
  printf("NULL\n");
}

int supprimerUniteUListe ( UListe * liste, Unite * unite ) {
	Unite * actuel, * precedent;
	
	/* On trouve l'objet dans la liste */
	actuel = liste->premier;
	precedent = NULL;
	
	while ( actuel != NULL ) {
		if ( actuel == unite ) {
			if ( precedent == NULL ) {
				liste->premier = actuel->suiv;
			} else if ( actuel->suiv == NULL ) {
				precedent->suiv = NULL;
			} else {
				precedent->suiv = actuel;
			}
			/*printf("Suppression réussie\n");*/
			return 1;
		}		
		precedent = actuel;
		actuel = actuel->suiv;
	}
	
	printf("ERREUR : suppression \n");
	return 0;	
}
