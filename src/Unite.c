#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"
#define LARG 18
#define LONG 12
#define ROUGE 'R'/* Identifiant du premier joueur */
#define BLEU 'B' /* Identifiant du deuxieme joueur */
#define SERF 's'/* Identifiant du Serf */
#define GUERRIER 'g'/* Identifiant du Guerrier */
#define REINE 'r'/* Identifiant de la Reine */
#define OEUF 'o'/* Identifiant de l'oeuf */

static int id = 0;

/*
  Cree une variable de type Unite 
  Retourne un code d'erreur :
  0: Erreur d'allocation memoire
  1: Pas d'erreur  
*/
int creerUnite( char type, Unite *unite ) {
  if ( unite != NULL ) {
    unite->genre = type;
		unite->attente = 0;
    unite->suiv = NULL;
    unite->prec = NULL;
		unite->id = id;
		id++;
		donnerStatsUnite ( type, unite );
    return 1;
  } else {
		printf("ERREUR : Allocation memoire\n");
    return 0;
  }
}

void donnerStatsUnite ( char type, Unite *unite ) {
	switch ( type ) {
		case REINE:
			unite->pm = 0;
			unite->atk = 0;
			unite->pv = 30;
			break;
		case GUERRIER:
			unite->pv = 20;
			unite->atk = 4;
			unite->pm = 2;
			break;
		case SERF:
			unite->pv = 10;
			unite->atk = 3;
			unite->pm = 3;
			break;
		case OEUF:
			unite->pv = 1;
			unite->atk = 0;
			unite->pm = 0;
			break;
		default:
			unite->pv = 1;
			unite->atk = 0;
			unite->pm = 0;
			break;			
	}
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
	
	/* On verifie que l'unite existe */
	if ( unite == NULL ) {
		printf("ERREUR : L'unite n'existe pas\n");
		return 0;
	}
	/* On supprime la reference a l'unite du plateau */
	monde->plateau[unite->posX][unite->posY] = NULL;
	
	/* On supprime la reference a l'unite de la liste correspondante */
	if ( unite->couleur == ROUGE ) {
		supprimerUniteUListe( &(monde->rouge), unite->id );
	} else if ( unite->couleur == BLEU ) {
		supprimerUniteUListe( &(monde->bleu), unite->id );
	}	
	/* On libere l'espace de l'unite */
	free( unite );
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
	-3 = ERREUR : tir allié => Empiler
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
	
	/*
		On verifie que la coordonnée entrée est voisine
	*/
	delta += abs( unite->posX - destX );
	delta += abs( unite->posY - destY );
	/*printf("delta : %d\n", delta);*/
	
	/*
		Le deplacement maximum possible est la quantite de PM de l'unite
	*/
	if ( delta > unite->pm ) {
		printf("ERREUR : Position non voisine\n");
		return -2;
	}
	
	if ( monde->plateau[destX][destY] != NULL )	{
		
		/* Il y a une unite a la case ciblée */		
		cible = monde->plateau[destX][destY];
		
		/* On verifie que l'unite n'attaque pas son allié */
		if ( cible->couleur == unite->couleur ) {
			printf("Les unites s'empilent\n");
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

/*
	Fonction qui créer un oeuf de la reine à une emplacement adjacent à la reine.
	Retourne :
	 0 = SUCCES
	-1 = ERREUR : coordonnees invalides
	-2 = ERREUR : coordonnees non adjacentes
*/
int produireUnOeuf ( Unite *unite, Monde *monde, int destX, int destY, char joueur ) {
	int delta = 0;	
	Unite *oeuf = malloc(sizeof(Unite));
	
	/* On verifie que la coordonnée entrée est valide */
	if ( destX<0 ||
			 destX>LARG ||
			 destY<0 ||
			 destY>LONG ) {
		printf("ERREUR : Position non valide\n");
		return -1;
	}
	
	/* On verifie que la coordonnée entrée est voisine */
	delta += abs( unite->posX - destX );
	delta += abs( unite->posY - destY );
	if ( delta != 1 ) {
		printf("ERREUR : Position non adjacente à la reine\n");
		return -2;
	}
	
	/* 
		On cree un nouvel oeuf, on le place sur le monde et on met la reine en attente
	*/
	if ( creerUnite( OEUF, oeuf ) == 1 ) {
		if ( placerAuMonde( oeuf, monde, destX, destY, joueur ) == 1 ) {
			unite->attente = 1;			
		}		
	}
	
	printf("Unite ajoutee ... affichage : \n");
	
	return 0;
}







