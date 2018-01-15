#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#define LONG 12
#define LARG 18
#define ROUGE 'R'/* Identifiant du premier joueur */
#define BLEU 'B' /* Identifiant du deuxieme joueur */
#define SERF 's'/* Identifiant du Serf */
#define GUERRIER 'g'/* Identifiant du Guerrier */
#define REINE 'r'/* Identifiant de la Reine */
#define OEUF 'o'/* Identifiant de l'oeuf */

void ajouterDebutUListe ( UListe * liste , Unite * unite ) {
	
	if ( liste->taille == 0 ) {
		liste->premier = unite;
		liste->dernier = unite;		
	} else {
		liste->premier->prec = unite;
		unite->suiv = liste->premier;
		liste->premier = unite;
	}
	
	liste->taille++;
}

void ajouterFinUListe ( UListe * liste , Unite * unite ) {
	
	if ( liste->taille == 0 ) {
		liste->premier = unite;
		liste->dernier = unite;		
	} else {
		liste->dernier->suiv = unite;
		unite->prec = liste->dernier;
		liste->dernier = unite;
	}
	
	liste->taille++;
}

void afficherUListe ( UListe * liste ) {
	Unite * actuel = liste->premier;
	printf("Taille : %d  |  ", liste->taille);
  while ( actuel != NULL ) {
    printf("%c -> ", actuel->genre);
    actuel = actuel->suiv;
  }
  printf("NULL\n");
}

int supprimerUniteUListe ( UListe * liste, int id ) {
	Unite *tmp = liste->premier;
	int found = 0;
	
	while ( tmp != NULL && !found ) {
		if ( tmp->id == id ) {
			if ( liste->taille == 1 ) {
				liste->premier = NULL;	
				liste->dernier = NULL;	
			} else if ( tmp->suiv == NULL ) {
				liste->dernier = tmp->prec;
				liste->dernier->suiv = NULL;
			} else if ( tmp->prec == NULL ) {
				liste->premier = tmp->suiv;
				liste->premier->prec = NULL;				
			} else {
				tmp->suiv->prec = tmp->prec;
				tmp->prec->suiv = tmp->suiv;
			}
			found = 1;
			liste->taille--;
		} else {
			tmp = tmp->suiv;
		}
	}
	
	return 1;	
}
