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

/*
  Initialise une variable de type Monde
*/
void initialiserMonde( Monde *monde ) {
  int x,y;	
  monde->tour = 1;
  monde->rouge.premier = NULL;
  monde->rouge.dernier = NULL;
	monde->rouge.taille = 0;
  monde->bleu.premier = NULL;
  monde->bleu.dernier = NULL;
	monde->bleu.taille = 0;
  for ( x=0; x<LARG; x++) {
    for ( y=0; y<LONG; y++) {
      monde->plateau[x][y].premier = NULL;
      monde->plateau[x][y].dernier = NULL;
      monde->plateau[x][y].taille = 0;
    }
  }
}

/*
  Place une unite qui vient d'etre creee a la position souhaitee dans le monde sous le controle de son nouveau maitre.
  Retourne un code d'erreur :
	0: Erreur insertion liste
  1: Pas d'erreur  
*/
int placerAuMonde( Unite *unite, Monde *monde, int posX, int posY, char couleur ) {
	unite->couleur = couleur;
	unite->posX = posX;
	unite->posY = posY;
	
	/* On ajoute a la liste de la case */
	ajouterDebutUListeTile( &( monde->plateau[posX][posY] ), unite );
	if ( couleur == ROUGE ) {
		ajouterDebutUListeClr( &(monde->rouge), unite );
	} else if ( couleur == BLEU ) {
		ajouterDebutUListeClr( &(monde->bleu), unite );			
	} else {
		printf("Erreur insertion Liste\n");
		return 0;
	}
	afficherUnite ( unite );
	return 1;
}

/*
  Fonction utilitaire pour remplir le monde
*/
void remplirMonde ( Monde *monde ) {	
	Unite *u1 = malloc(sizeof(Unite));
	Unite *u2 = malloc(sizeof(Unite));
	Unite *u3 = malloc(sizeof(Unite));
	Unite *u4 = malloc(sizeof(Unite));
	Unite *u5 = malloc(sizeof(Unite));
	Unite *u6 = malloc(sizeof(Unite));
	Unite *u7 = malloc(sizeof(Unite));
	Unite *u8 = malloc(sizeof(Unite));
	
	creerUnite(GUERRIER, u1);
	creerUnite(SERF, u2);
	creerUnite(SERF, u3);
	creerUnite(GUERRIER, u4);
	creerUnite(SERF, u5);
	creerUnite(SERF, u6);
	creerUnite(REINE, u7);
	creerUnite(REINE, u8);

	placerAuMonde( u1, monde, 2, 2, BLEU);
	placerAuMonde( u2, monde, 2, 0, BLEU);
	placerAuMonde( u3, monde, 0, 2, BLEU);
	placerAuMonde( u4, monde, 15, 9, ROUGE);
	placerAuMonde( u5, monde, 17, 9, ROUGE);
	placerAuMonde( u6, monde, 15, 11, ROUGE);   
	placerAuMonde( u7, monde, 0, 0, BLEU);   
	placerAuMonde( u8, monde, 17, 11, ROUGE);
	
	afficherUListeClr( &(monde->bleu) );
}

/*
  Gere toutes les actions du joueur pendant un tour
*/
void gererDemiTour( char joueur, Monde *monde ) {
  Unite * unite;
  int userX, userY;
  
  /* Pour un joueur <joueur> donnée : */
  if( joueur == ROUGE ) {
    unite = monde->rouge.premier;
  } else if ( joueur == BLEU ) {
    unite = monde->bleu.premier;
  }
  
  /* Pour chacune des unites du joueur : */
  while ( unite != NULL ) {
    /* On affiche les informations de l'état actuel */
    afficherPlateau( monde );
    afficherUnite( unite );
		printf( "Taille rouge : %d\n", monde->rouge.taille );
		printf( "Taille bleu : %d\n", monde->bleu.taille );
		
		if ( unite->genre == REINE ) {
			/* On demande à l'utilisateur ou il veux produire */
			if ( unite->attente == 1 ) {
				/* La reine ne peut plus produire durant ce tour */
				unite->attente = 0;
				printf("La reine se repose après avoir créer une unite\n");
			} else {
				printf("Ou souhaitez vous créer une unite ? ");
				scanf("%d %d", &userX, &userY);

				if ( userX != -1 && userY != -1 ) {
					/* Cas normal */
					produireUnOeuf( unite, monde, userX, userY, joueur );
				} else {     
					/* Ne rien faire */
					printf("ERREUR : La reine attend\n");    
				}
			}
			
		} else if ( unite->genre == OEUF ) {
			/* L'oeuf grandit en soit un GUERRIER soit un SERF de maniere aleatoire */
			if ( rand() % 2 == 0 ) {
        donnerStatsUnite( GUERRIER, unite );
        printf("L'oeuf grandit et devient un puissant Guerrier\n");
			} else {
        donnerStatsUnite( SERF, unite );
        printf("L'oeuf grandit et devient un faible Serf\n");
			}
			unite->pm = 2;
			
		} else {
			
			/* Si ce n'est pas une reine */
			/* On demande à l'utilisateur ce qu'il veux faire */
			printf("Ou aller ? ");
			scanf("%d %d", &userX, &userY);
			if ( userX != -1 && userY != -1 ) {
				/* Cas normal */
				deplacerOuAttaquer( unite, monde, userX, userY );   
			} else {     
				/* Ne rien faire */
				printf("L'unite attend\n");    
			}
			
		}
    
    /* On passe à l'unite suivante */
    unite = unite->suivClr;
  }
  
  /* On termine le tour */
  printLigneDelimitation();
  printf("Votre tour est terminé !\n");
  
}

/*
  Gere le tour des deux joueurs
  Incrémente le compteur de tours
*/
void gererTour( Monde *monde ) {
	
	/* Choix du joueur aléatoire */
  printf("Tour actuel : %d\n", monde->tour);
  printLigneDelimitation();
	if (  rand() % 2 == 0 ) {
		/* Le rouge joue en 1er */
		printf("Tour du joueur ROUGE\n");
		printLigneDelimitation();
		gererDemiTour( ROUGE, monde );
		
		printLigneDelimitation();
		
		printf("Tour du joueur BLEU\n");
		printLigneDelimitation();
		gererDemiTour( BLEU, monde );
		
	} else {		
		/* Le bleu joue en 1er */
		printf("Tour du joueur BLEU\n");
		printLigneDelimitation();
		gererDemiTour( BLEU, monde );
		
		printLigneDelimitation();
		
		printf("Tour du joueur ROUGE\n");
		printLigneDelimitation();
		gererDemiTour( ROUGE, monde );		
	}
  printLigneDelimitation();
  monde->tour++;
}

/*
  Vide le monde
  Libere toute la memoire
  Reinitialise la structure Monde
*/
void viderMonde( Monde *monde ) {
  /* Supprime les unites */
	
  while ( monde->rouge.taille != 0 ) {
		enleverUnite( monde->rouge.premier, monde );
		/*afficherUListe ( &(monde->rouge) );*/
  }
  while ( monde->bleu.taille != 0 ) {
    enleverUnite( monde->bleu.premier, monde );
		/*afficherUListe ( &(monde->bleu) );*/
  }
  initialiserMonde( monde );
}

/*
  Effectue une partie :
  - Prepare le plateau
  - Positionne les unites initiales sur le plateau
  - Laisse chaque joueur jouer
  - Propose d'arreter
  - Annonce le resultat et vide correctement le monde
*/
void gererPartie() {
  char c;
  int forceStop = 0;
  
  /* Prepare le plateau et positionne les unites initiales */
	srand(time(NULL));
  Monde monde;	
  initialiserMonde( &monde );
		
	/* On demander si l'on veut charger la derniere partie */
	
	/*
	printf("Voulez vous charger la derniere partie ? (Y/n)\n");
	scanf(" %c", &c);
	if ( c == 'Y' || c == 'y' ) {
		if ( charger( &monde ) != 1 ) {
			remplirMonde( &monde );
		}
	} else {
		remplirMonde( &monde );
	}
	*/
	
	genererUnitesCentre ( &monde );
	
	/* On affiche les instructions */
	afficherTutoriel();
  
  /* Laisse chaque joueur jouer */
  while ( monde.rouge.taille != 0 && monde.bleu.taille != 0 && forceStop == 0) {
    
		gererTour( &monde );
				
		/* On demander si l'on veut sauvegarder la partie */
		printf("Voulez vous Sauvegarder la partie ? (Y/n)\n");
    scanf(" %c", &c);
    if ( c == 'Y' || c == 'y' ) {
			sauvegarder ( &monde );
    }
		
		/* On demande si l'on veut arreter la partie */
    printf("Voulez vous arreter la ? (Y/n)\n");
    scanf(" %c", &c);
    if ( c == 'Y' || c == 'y' ) {
      printf("D'accord ! Salut :)\n");
      forceStop = 1;
    }		   
  }
  
  /* Resultat et vide le monde */
  if ( monde.rouge.taille == 0 && forceStop == 0 ) {
    printf("Le joueur BLEU à gagné !!\nBravo :) :) :)\n");
  } else if ( monde.bleu.taille == 0 && forceStop == 0 ) {
    printf("Le joueur ROUGE à gagné !!\nBravo :) :) :)\n");    
  } 
	viderMonde( &monde );
  
}


void genererUnitesCentre ( Monde * monde ) {
	Unite *u1 = malloc(sizeof(Unite));
	Unite *u2 = malloc(sizeof(Unite));
	Unite *u3 = malloc(sizeof(Unite));
	Unite *u4 = malloc(sizeof(Unite));
	
	creerUnite(GUERRIER, u1);
	creerUnite(SERF, u2);
	creerUnite(REINE, u3);
	creerUnite(SERF, u4);
	
	placerAuMonde( u1, monde, 6, 6, BLEU);
	placerAuMonde( u2, monde, 7, 7, ROUGE);	
	placerAuMonde( u3, monde, 7, 6, ROUGE);	
	placerAuMonde( u4, monde, 6, 7, BLEU);	
}
