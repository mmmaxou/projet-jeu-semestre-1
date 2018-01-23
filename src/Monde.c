#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>
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

  /* afficherUListeClr( &(monde->bleu) ); */
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
  } else {
    unite = monde->bleu.premier;
  }

  /* Pour chacune des unites du joueur : */
  while ( unite != NULL ) {	
    /* Affiche les informations de l'état actuel */
    MLVactualiserPlateau(monde);
    MLVafficherUniteActive(unite);
		
    if ( unite->genre == REINE ) {
      /* On demande à l'utilisateur ou il veux produire */
      if ( unite->attente == 1 ) {
        /* La reine ne peut plus produire durant ce tour */
        unite->attente = 0;
        MLVafficherDansZoneTexte("La reine se repose après avoir créer une unite\n");
				MLVattendreValidation();
      } else {
				/* On propose de créer un oeuf */
				MLVafficherDansZoneTexte("La reine peut créer une unite sur une des cases qui lui\nest adjacente.\n -> Ou souhaitez vous créer une unité ?");
				
				do {
					/* Calcule la nouvelle position de l'unite active en fonction des coordonnees du clic de la souris */
					MLV_wait_mouse(&userX, &userY);
					userX = userX/30-1;
					userY = userY/30-1;

				} while( produireUnOeuf( unite, monde, userX, userY, joueur ) < 0 &&
								 MLVactiverNeRienFaireUnite( userX*30+1, userY*30+1 ) == 0 );
      }

    } else if ( unite->genre == OEUF ) {
      /* L'oeuf grandit en soit un GUERRIER soit un SERF de maniere aleatoire */
      if ( rand() % 2 == 0 ) {
        donnerStatsUnite( GUERRIER, unite );
        MLVafficherDansZoneTexte("L'oeuf grandit et devient un puissant Guerrier\n");
				MLVattendreValidation();
      } else {
        donnerStatsUnite( SERF, unite );
				/* Debug sale */
        MLVafficherDansZoneTexte("L'oeuf grandit et devient un faible Serf\n");
				MLVattendreValidation();
      }
    } else {

      /* Si ce n'est pas une reine */
      /* On demande à l'utilisateur ce qu'il veux faire */
      MLVafficherDansZoneTexte("Où souhaitez vous déplacer votre unité ?\n");
			
			do {
				/* Calcule la nouvelle position de l'unite active en fonction des coordonnees du clic de la souris */
				MLV_wait_mouse(&userX, &userY);
				userX = userX/30-1;
				userY = userY/30-1;

			} while( deplacerOuAttaquer(unite, monde, userX, userY) < 0 &&
							 MLVactiverNeRienFaireUnite(userX*30+1, userY*30+1) == 0 );
			
		/*
		 OLD
      printf("Ou aller ? ");
      scanf("%d %d", &userX, &userY);
      if ( userX != -1 && userY != -1 ) {
        deplacerOuAttaquer( unite, monde, userX, userY );   
      } else {     
        printf("L'unite attend\n");    
      }
			*/

    }

    /* Resultat et vide le monde */
    if ( monde->rouge.taille == 0 ) {
      MLVafficherDansZoneTexte("Le joueur BLEU à gagné !!\nBravo :) :) :)\n");
      viderMonde( monde );
      exit(0);
    } else if ( monde->bleu.taille == 0 ) {
      MLVafficherDansZoneTexte("Le joueur ROUGE à gagné !!\nBravo :) :) :)\n");    
      viderMonde( monde );
      exit(0);
    } 

    /* On passe à l'unite suivante */
    unite = unite->suivClr;
    MLVdesactiverNeRienFaire();
  }

  /* On termine le tour */
  MLVafficherDansZoneTexte("Votre tour est terminé !\n");
	MLVactualiserPlateau(monde);
	MLVattendreValidation();

}

/*
  Gere le tour des deux joueurs
  Incrémente le compteur de tours
*/
void gererTour( Monde *monde ) {
  gererDemiTour(ROUGE, monde);
  gererDemiTour(BLEU, monde);
  MLVactualiserPlateau(monde);
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
  - Prepare le plateauMLVafficherDansZoneTexte
  - Positionne les unites initiales sur le plateau
  - Laisse chaque joueur jouer
  - Propose d'arreter
  - Annonce le resultat et vide correctement le monde
*/
void gererPartie() {
  Monde monde;

  /* Prepare le plateau et positionne les unites initiales */
  srand(time(NULL));
  MLVinit();
  initialiserMonde( &monde );
	
  /* On affiche les instructions */
  MLVafficherTutoriel(&monde);
	
  /* On demander si l'on veut charger la derniere partie */
	if ( MLVactiverCharger() == 1) {
    if ( charger( &monde ) != 1 ) {
			/* Si il y a eu une erreur, on créer une nouvelle partie */
      remplirMonde( &monde );
    }		
	} else {
    remplirMonde( &monde );
	}
	MLVdesactiverCharger();
	
	/* DEBUG */
  /*
	genererUnitesCentre ( &monde );
	*/

  /* Laisse chaque joueur jouer */
  while ( monde.rouge.taille != 0 && monde.bleu.taille != 0) {
    gererTour( &monde );
		MLVgererFinTour( &monde );
  }
}

/* Debug function */
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