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
  Initialise une variable de type Monde
*/
void initialiserMonde( Monde *monde ) {
  int x,y;
  monde->tour = 0;
  monde->rouge.premier = NULL;
  monde->bleu.premier = NULL;
  for ( x=0; x<LARG; x++) {
    for ( y=0; y<LONG; y++) {
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
  placerAuMonde( u4, monde, 17, 11, ROUGE);
  placerAuMonde( u5, monde, 17, 10, ROUGE);
  placerAuMonde( u6, monde, 16, 11, ROUGE);   
}

/*
	Deplace une unite sur le monde
*/
void deplacerUnite( Unite *unite, Monde *monde, int destX, int destY ) {
	monde->plateau[unite->posX][unite->posY] = NULL;
	unite->posX = destX;
	unite->posY = destY;
	monde->plateau[destX][destY] = unite;
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
		printf("ERREUR : L'unite n'existe pas\n");
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
	/*printf("Unite enlevée\n");*/
	return 2;
	
}

/*
	Gere le combat
	L'unite passée en argument attaquera la case spécifiée par <destX> et <destY>
	
	Le GUERRIER bat le SERF
	Les deux meur 1ent en cas d'égalité
	
	Renvoi :
	0 = Perte de l'unite attaquante
	1 = Victoire
	2 = Erreur inconnue
*/
int attaquer( Unite *unite, Monde *monde, int posX, int
posY ) {
	Unite *cible = monde->plateau[posX][posY];
	
	/* 
	Recherche du gagnant, il y a plusieurs cas :
		- Les deux unites sont de meme genre -> 2 morts
		- Une unite bat l'autre -> 1 mort
	*/
	/* Cas 1 : Meme genre */
	if ( cible->genre == unite->genre ) {
		enleverUnite(cible, monde);
		enleverUnite(unite, monde);
		printf("Double KO\n");
		return 0;
	} else {
		/* Cas 2 : L'un bat l'autre */
		if ( cible->genre == SERF ) {
			enleverUnite(cible, monde);
			printf("Victoire !!!\n");
			return 1;
		} else if ( unite->genre == SERF ) {
			enleverUnite(unite, monde);
			printf("Defaite :(\n");
			return 0;			
		} else {
			printf("ERREUR INCONNUE : Le genre n'est pas bon\n");
			return 2;
		}		
	}
}

/*
	Gere le deplacement et le combat
	Renvoi :
	-1 = ERREUR : coordonnees invalides
	-2 = ERREUR : coordonnees non voisines
	-3 = ERREUR : tir allié
	 1 = Deplacement reussi
	 2 = Combat : Victoire
	 3 = Combat : Defaite
*/
int deplacerOuAttaquer( Unite *unite, Monde *monde, int destX, int destY ) {
	Unite *cible;
	int delta = 0;
	int resultatAttaque;
	
	/* 
		On verifie que la coordonnée entrée est valide 
	*/
	if ( destX<0 ||
			 destX>LARG ||
			 destY<0 ||
			 destY>LONG ) {
		printf("ERREUR : Position non valide\n");
		return -1;
	}
	
	afficherUnite(unite);
	/*
		On verifie que la coordonnée entrée est voisine
	*/
	delta += abs( unite->posX - destX );
	delta += abs( unite->posY - destY );
	/*printf("delta : %d\n", delta);*/
	
	if ( delta > 2 ) {
		printf("ERREUR : Position non voisine\n");
		return -2;
	}
	
	if ( monde->plateau[destX][destY] != NULL )	{
		
		/* Il y a une unite a la case ciblée */		
		cible = monde->plateau[destX][destY];
		printf("OUI\n");
		
		/* On verifie que l'unite n'attaque pas son allié */
		if ( cible->couleur == unite->couleur ) {
			printf("ERREUR : La case attaquée est un allié\n");
			return -3;
		}
		
		resultatAttaque = attaquer(unite, monde, destX, destY);
		/* DEFAITE */
		if ( resultatAttaque == 0 ) {
			return 3;
		}
		/* VICTOIRE */
		if ( resultatAttaque == 1 ) {
			return 2;
		}
		
	} 
	else
	{
		/* La case ciblée est vide */
		deplacerUnite(unite, monde, destX, destY);
		return 1;
	}
	
	return 0;
	
}

int abs ( int x ) {
	return x < 0 ? -x : x;
}

char* format( int n ) {
	char *s = malloc(3 * sizeof(*s));
	s[0] = '0';
	s[1] = '0';
	s[2] = '0';
	
	s[2] += n % 10;
	if( n >= 10) {
		s[1] += (n-(n%10)) / 10;
	}
	return s;
}













