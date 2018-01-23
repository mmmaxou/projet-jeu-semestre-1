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

/*
	Ajoute une unite au début de la liste doublement chainée <Tile>
*/
void ajouterDebutUListeTile ( UListe * liste , Unite * unite ) {
	
	if ( liste->taille == 0 ) {
		liste->premier = unite;
		liste->dernier = unite;		
	} else {
		liste->premier->precTile = unite;
		unite->suivTile = liste->premier;
		liste->premier = unite;
	}
	
	liste->taille++;
}

/*
	Ajoute une unite au début de la liste doublement chainée <Couleur>
*/
void ajouterDebutUListeClr ( UListe * liste , Unite * unite ) {
	
	if ( liste->taille == 0 ) {
		liste->premier = unite;
		liste->dernier = unite;		
	} else {
		liste->premier->precClr = unite;
		unite->suivClr = liste->premier;
		liste->premier = unite;
	}
	
	liste->taille++;
}

/*
	Ajoute une unite à la fin de la liste doublement chainée <Tile>
*/
void ajouterFinUListeTile ( UListe * liste , Unite * unite ) {
	
	if ( liste->taille == 0 ) {
		liste->premier = unite;
		liste->dernier = unite;		
	} else {
		liste->dernier->suivTile = unite;
		unite->precTile = liste->dernier;
		liste->dernier = unite;
	}
	
	liste->taille++;
}

/*
	Ajoute une unite à la fin de la liste doublement chainée <Couleur>
*/
void ajouterFinUListeClr ( UListe * liste , Unite * unite ) {
	
	if ( liste->taille == 0 ) {
		liste->premier = unite;
		liste->dernier = unite;		
	} else {
		liste->dernier->suivClr = unite;
		unite->precClr = liste->dernier;
		liste->dernier = unite;
	}
	
	liste->taille++;
}

/*
	Affiche la liste Tile	
*/
void afficherUListeTile ( UListe * liste ) {
	Unite * actuel = liste->premier;
  /*
	printf("Taille : %d  |  ", liste->taille);
  */
  while ( actuel != NULL ) {
    printf("%c -> ", actuel->genre);
    actuel = actuel->suivTile;
  }
  printf("NULL\n");
	
}

/*
	Affiche la liste Couleur
*/
void afficherUListeClr ( UListe * liste ) {
	Unite * actuel = liste->premier;
  /*
	printf("Taille : %d  |  ", liste->taille);
  */
  while ( actuel != NULL ) {
    printf("%c -> ", actuel->genre);
    actuel = actuel->suivClr;
  }
  printf("NULL\n");
}

/*
	Supprime une unite de la liste doublement chainée Tile
	L'unite a supprimer est identifiée par son id
*/
int supprimerUniteUListeTile ( UListe * liste, int id ) {
	Unite *tmp = liste->premier;
	int found = 0;
	
	while ( tmp != NULL && !found ) {
		if ( tmp->id == id ) {
			if ( liste->taille == 1 ) {
				liste->premier = NULL;	
				liste->dernier = NULL;
			} else if ( tmp->suivTile == NULL ) {
				liste->dernier = tmp->precTile;
				liste->dernier->suivTile = NULL;
			} else if ( tmp->precTile == NULL ) {
				liste->premier = tmp->suivTile;
				liste->premier->precTile = NULL;				
			} else {
				tmp->suivTile->precTile = tmp->precTile;
				tmp->precTile->suivTile = tmp->suivTile;
			}
			found = 1;
			liste->taille--;
		} else {
			tmp = tmp->suivTile;
		}
	}
	
	return 1;	
}

/*
	Supprime une unite de la liste doublement chainée Couleur
	L'unite a supprimer est identifiée par son id
*/
int supprimerUniteUListeClr ( UListe * liste, int id ) {
	Unite *tmp = liste->premier;
	int found = 0;
	
	while ( tmp != NULL && !found ) {
		if ( tmp->id == id ) {
			if ( liste->taille == 1 ) {
				liste->premier = NULL;	
				liste->dernier = NULL;
			} else if ( tmp->suivClr == NULL ) {
				liste->dernier = tmp->precClr;
				liste->dernier->suivClr = NULL;
			} else if ( tmp->precClr == NULL ) {
				liste->premier = tmp->suivClr;
				liste->premier->precClr = NULL;				
			} else {
				tmp->suivClr->precClr = tmp->precClr;
				tmp->precClr->suivClr = tmp->suivClr;
			}
			found = 1;
			liste->taille--;
		} else {
			tmp = tmp->suivClr;
		}
	}
	
	return 1;	
}
