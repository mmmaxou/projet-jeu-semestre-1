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

/*
  Initialise une variable de type Monde
*/
void initialiserMonde( Monde *monde ) {
  int x,y;
  monde->tour = 0;
  monde->rouge.premier = NULL;
  monde->bleu.premier = NULL;
  for ( x=0; x<LONG; x++) {
    for ( y=0; y<LARG; y++) {
      monde->plateau[x][y] = NULL;
    }
  }
}

/*
  Cree une variable de type Unite 
  Retourne un code d'erreur :
  0: Erreur d'allocation memoire
  1: Pas d'erreur  
*/
int creerUnite( char type, Unite *unite ) {
  if ( unite != NULL ) {
    unite->genre = type;
    unite->suiv = NULL;
    return 1;
  } else {
    return 0;
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
  Affiche le plateau et les unites qu'il y a dessus
  Retourne un code d'erreur :
  0: ???
  1: Pas d'erreur
*/
int afficherPlateau( Monde *monde ) {
  int x,y;
  for ( x=0; x<LONG; x++ ) {
		
		/* affiche une ligne de bord */
		printborderline();
    for ( y=0; y<LARG; y++ ) {
      if ( monde->plateau[x][y] == NULL ) {
        printf("|   ");
      } else {
        printf("| %c ", monde->plateau[x][y]->genre);
      }
    }
    printf("|\n");
  }
	printborderline();
  return 1;
}

void printborderline() {
	int i;
	for ( i=0; i<LARG; i++ ) {
		printf("+---");
	}
	printf("+\n");	
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
  placerAuMonde( u4, monde, LONG-1, LARG-1, ROUGE);
  placerAuMonde( u5, monde, LONG-2, LARG-1, ROUGE);
  placerAuMonde( u6, monde, LONG-1, LARG-2, ROUGE);  
}

/*
	Deplace une unite sur le monde
	Renvoie :
	0 = Erreur destX ou destY non valide
	1 = Erreur position occupée
	2 = Succes
*/
int deplacerUnite( Unite *unite, Monde *monde, int destX, int destY ) {
	/* On verifie que la coordonnée entrée est valide */
	if ( destX<0 || destX>LARG || destY<0 || destY>LONG ) {
		printf("Position non valide\n");
		return 0;
	}
	/* On verifie que la coordonnée entrée est disponible */
	if ( monde->plateau[destX][destY] != NULL ) {
		printf("Position occupée\n");
		return 1;	
	}
	
	monde->plateau[unite->posX][unite->posY] = NULL;
	unite->posX = destX;
	unite->posY = destY;
	monde->plateau[destX][destY] = unite;
	printf("Deplacement réussi\n");
	return 2;
}


/*
	Supprime une unite du plateau et de l'equipe qui la possede
	Renvoie :
	0 = Erreur l'unite n'existe pas
	1 = Erreur suppression
	2 = Succes
*/
int enleverUnite( Unite *unite, Monde *monde ) {
	int errSuppression;
	/* On verifie que l'unite existe */
	if ( unite == NULL ) {
		printf("L'unite n'existe pas\n");
		return 0;
	}
	/* On supprime la reference a l'unite du plateau */
	monde->plateau[unite->posX][unite->posY] = NULL;
	
	/* On supprime la reference a l'unite de la liste correspondante */
	if ( unite->couleur == BLEU ) {
		errSuppression = supprimerUniteUListe( &(monde->bleu), unite ); 	
	}
	if ( unite->couleur == ROUGE ) {
		errSuppression = supprimerUniteUListe( &(monde->rouge), unite ); 	
	}
	
	if ( errSuppression == 0 ) {
		return 1;
	}
	
	/* On libere l'espace de l'unite */
	free(unite);
	printf("Unite enlevée\n");
	return 2;
	
}























