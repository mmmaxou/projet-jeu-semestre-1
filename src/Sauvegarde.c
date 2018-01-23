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
	Effectue une sauvegarde complete du monde
	Retourne :
	 1 = SUCCES
	-1 = ERREUR : Impossible d'ouvrir le fichier
*/
int sauvegarder ( Monde * monde ) {
	FILE *fichier = NULL;	
	Unite *unite = NULL;
	fichier = fopen("./data/save.txt", "w+");
	if ( fichier != NULL ) {
		
		/* On sauvegarde les unites rouges */
		unite = monde->rouge.premier;
		while ( unite != NULL ) {
			ecrireUnite( unite, fichier );
			unite = unite->suivClr;
		}
		
		/* On sauvegarde les unites bleues */
		unite = monde->bleu.premier;
		while ( unite != NULL ) {
			ecrireUnite( unite, fichier );
			unite = unite->suivClr;
		}
		
		fputc('$', fichier);
		fclose( fichier );
	}	else {
		MLVafficherDansZoneTexte("ERREUR : Impossible d'ouvrir le fichier\n");
		return -1;
	}	
	return 1;
}

/*
	Format d'ecriture : 
	X;Y;COULEUR;GENRE;PV;PM;ATTENTE;ATK;$
	$ > Fin de la ligne
*/
void ecrireUnite ( Unite * u, FILE * fichier ) {	
	afficherUnite( u );
	fprintf(fichier, "%d;%d;%c;%c;%d;%d;%d;%d;$\n", u->posX, u->posY, u->couleur, u->genre, u->pv, u->pm, u->attente, u->atk );		
}


/*
	Charge la derniere sauvegarde
	Retourne :
	 1 = SUCCES
	-1 = ERREUR : Impossible d'ouvrir le fichier
*/
int charger ( Monde * monde ) {
	FILE *fichier = NULL;
	fichier = fopen("./data/save.txt", "r");
	if ( fichier != NULL ) {
		while ( lireUnite ( fichier, monde ) != 0 )
		;
		fclose( fichier );
	}	else {
		MLVafficherDansZoneTexte("ERREUR : Impossible d'ouvrir le fichier\n");
		return -1;
	}	
	return 1;
}

	
/* 
	On lis chaque ligne du fichier que l'on charge dans le monde
	Retourne :
	0 = Fichier non fini
	1 = Fichier fini
*/
int lireUnite ( FILE * fichier, Monde * monde ) {
	int x, y, pm, attente, atk, pv;
	char couleur, genre;
	int eof;
	Unite *unite = malloc(sizeof(Unite));
	
	eof = fscanf(fichier, "%d;%d;%c;%c;%d;%d;%d;%d;$\n", &x, &y, &couleur, &genre, &pv, &pm, &attente, &atk );

	if ( eof != 0 ) {
		creerUnite( genre, unite );
		unite->attente = attente;
		unite->pm = pm;
		unite->atk = atk;
		unite->pv = pv;
		placerAuMonde( unite, monde, x, y, couleur );
	}
	
	return eof;
}
