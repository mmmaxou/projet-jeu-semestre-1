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
#define ATTAQUE 0
#define RIPOSTE 1

static int id = 0;

/*
  Cree une variable de type Unite 
  Retourne un code d'erreur :
  0: Erreur d'allocation memoire
  1: Pas d'erreur  
*/
int creerUnite( char type, Unite *unite ) {
  if ( unite != NULL ) {
		unite->attente = 0;
    unite->suivTile = NULL;
    unite->suivClr = NULL;
    unite->precTile = NULL;
    unite->precClr = NULL;
		unite->id = id;
		id++;
		donnerStatsUnite ( type, unite );
    return 1;
  } else {
		printf("ERREUR : Allocation mémoire\n");
    return 0;
  }
}

/*
	Fonction d'aide qui donne les stats a une unite, on l'appelle quand on créer une unite, ou quand un oeuf éclot
*/
void donnerStatsUnite ( char type, Unite *unite ) {
  unite->genre = type;
	switch ( type ) {
		case REINE:
			unite->pv = 30;
			unite->atk = 0;
			unite->pm = 0;
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
      unite->genre = type;
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
	Si la case cible contient une unite alliée, les unites s'empilent correctement
*/
void deplacerUnite( Unite *unite, Monde *monde, int destX, int destY ) {
	/* On supprime l'unite de la liste du plateau qui lui correspond */
	supprimerUniteUListeTile( &(monde->plateau[unite->posX][unite->posY]), unite->id );
  /* afficherUListeTile( &(monde->plateau[unite->posX][unite->posY]) ); */
  
	/* On modifie les coordonnées propres de l'unite */	
	unite->posX = destX;
	unite->posY = destY;
	
	/* On deplace l'unite vers une nouvelle liste destination du plateau */
	
  ajouterDebutUListeTile( &(monde->plateau[destX][destY]), unite );
  
	/* afficherUListeTile( &(monde->plateau[destX][destY]) ); */
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
	if (unite == NULL) {
		return 0;
	}
	/* On supprime la reference a l'unite du plateau */
	supprimerUniteUListeTile( &(monde->plateau[unite->posX][unite->posY]), unite->id );
	
	/* On supprime la reference a l'unite de la liste correspondante */
	if ( unite->couleur == ROUGE ) {
		supprimerUniteUListeClr( &(monde->rouge), unite->id );
	} else if ( unite->couleur == BLEU ) {
		supprimerUniteUListeClr( &(monde->bleu), unite->id );
	}	
	/* On libere l'espace de l'unite */
	free( unite );
	return 2;
}

/*
	Gere le combat
	L'unite passée en argument attaquera la case spécifiée par <destX> et <destY>
	
	Inflige le nombre de dégat de l'unite attaquante à l'unite cible
	Si elle survie, la cible riposte
	
	Le champs riposte est à 1 si c'est une riposte, 0 autrement
	
	Renvoi :
	0 = Perte de l'unite attaquante
	1 = Victoire
	2 = Pas de victime
*/
int attaquer( Unite *unite, Monde *monde, int posX, int posY, int riposte ) {
	Unite * tile = monde->plateau[posX][posY].premier;
	Unite * cible = tile;
	int currentValue, maxValue;
	int resultatAttaque;
	
	/* On choisit la cible */
	/* Ordre : GUERRIER > SERF > OEUF > REINE */
	maxValue = donnerValeur ( cible );
	while ( tile != NULL ) {
		currentValue = donnerValeur ( tile );
		if ( currentValue > maxValue ) {
			maxValue = currentValue;
			cible = tile;			
		}
		tile = tile->suivTile;
	} 
	
	
	/* La cible perds des pv */
	cible->pv -= unite->atk;
	/* On verifie si elle passe en dessous de 0 */
	if ( cible->pv <= 0 ) {
		/* On la supprime, elle est morte */
		enleverUnite(cible, monde);
		if ( riposte == ATTAQUE ) {
			MLVafficherDansZoneTexte("La cible a été éliminée !\n");
			MLVattendreValidation();
		}
		return 1;
	} else {
		/* Si c'est une attaque, la cible riposte */
		if ( riposte == ATTAQUE) {
			resultatAttaque = attaquer(cible, monde, unite->posX, unite->posY, RIPOSTE);
			if ( resultatAttaque == 1) {
				MLVafficherDansZoneTexte("Vous avez été vaincu\n");
				MLVattendreValidation();
				return 0;
			} else {
				MLVafficherDansZoneTexte("Pas de victime\n");
				MLVattendreValidation();
			}
 		}
		return 2;
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
	int delta = 0;
	int resultatAttaque;
	
	/* 
		On verifie que la coordonnée entrée est valide 
	*/
	if (destX < 0 ||
			 destX>LARG ||
			 destY<0 ||
			 destY>LONG) {
		MLVafficherDansZoneTexte("ERREUR : Position non valide");
		MLVattendreValidation();
		return -1;
	}
	
	/*
		On verifie que la coordonnée entrée est atteignable
		Le deplacement maximum possible est la quantite de PM de l'unite
	*/
	delta += abs( unite->posX - destX );
	delta += abs( unite->posY - destY );
	/*printf("delta : %d\n", delta);*/
	if ( delta > unite->pm ) {
		MLVafficherDansZoneTexte("ERREUR : Position non voisine\n");
		MLVattendreValidation();
		return -2;
	}
	
	/* La case n'est pas vide */
	if ( monde->plateau[destX][destY].taille != 0 )	{
		
		/* On verifie que l'unite n'attaque pas son allié */
		if ( monde->plateau[destX][destY].premier->couleur == unite->couleur ) {
			deplacerUnite(unite, monde, destX, destY);
			return 1;
		} else {		
			resultatAttaque = attaquer(unite, monde, destX, destY, ATTAQUE);
			/* DEFAITE */
			if ( resultatAttaque == 0 ) {
				return 3;
			}
			/* VICTOIRE */
			if ( resultatAttaque == 1 ) {
				return 2;
			}
		}		
	} else 	{
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
		MLVafficherDansZoneTexte("ERREUR : Position non adjacente à la reine\n");
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
	
	return 0;
}

/* Fonction utilitaire qui donne la valeure d'une unite pour faciliter le choix de la cible d'une attaque */
int donnerValeur ( Unite * unite ) {
	switch ( unite->genre ) {
			case GUERRIER:
				return 30;
				break;
			case SERF:
				return 20;
				break;
			case OEUF:
				return 10;
				break;
			case REINE:
				return 0;
				break;
			default:
				return 0;
				break;
		}
}
