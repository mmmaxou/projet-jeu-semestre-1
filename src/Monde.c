#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
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
void initialiserMonde(Monde * monde) {
  int x,y;
  monde->tour = 1;
  monde->rouge.premier = NULL;
  monde->bleu.premier = NULL;
  for (x=0; x<LARG; x++) {
    for (y=0; y<LONG; y++) {
      monde->plateau[x][y] = NULL;
    }
  }
}

/*
  Place une unite qui vient d'etre creee a la position souhaitee dans le monde sous le controle de son nouveau maitre.
  Retourne un code d'erreur :
  0: Case designee deja occupee
  1: Pas d'erreur  
*/
int placerAuMonde(Unite * unite, Monde * monde, int posX, int posY, char couleur) {
  if (monde->plateau[posX][posY] != NULL) {
    return 0;
  } else {
    unite->couleur = couleur;
    unite->posX = posX;
    unite->posY = posY;
    monde->plateau[posX][posY] = unite;
    if (couleur == ROUGE) {
      insertionUListe(&(monde->rouge), unite);
    } else if (couleur == BLEU) {
      insertionUListe(&(monde->bleu), unite);
    }
    return 1;
  }  
}

/*
  Fonction utilitaire pour remplir le monde
*/
void remplirMonde (Monde * monde) {
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
  
  placerAuMonde(u1, monde, 0, 0, BLEU);
  placerAuMonde(u2, monde, 1, 0, BLEU);
  placerAuMonde(u3, monde, 0, 1, BLEU);
  placerAuMonde(u4, monde, 17, 11, ROUGE);
  placerAuMonde(u5, monde, 17, 10, ROUGE);
  placerAuMonde(u6, monde, 16, 11, ROUGE);   
}

/*
  Gere toutes les actions du joueur pendant un tour
*/
void gererDemiTour(char joueur, Monde * monde) {
  Unite * unite;
  int userX, userY;
  
  /* Pour un joueur <joueur> donnée : */
  if(joueur == ROUGE) {
    unite = monde->rouge.premier;
  } else {
    unite = monde->bleu.premier;
  }
  
  /* Pour chacune des unites du joueur : */
  while (unite != NULL) {

    /* Affiche les informations de l'état actuel */
    MLVactualiserPlateau(monde);
    MLVafficherUniteActive(unite);
    
    /* Demande à l'utilisateur ce qu'il veux faire
    MLVafficherDansZoneTexte("Où souhaitez-vous aller ?\nPour ne rien faire, double-cliquez sur le bouton à droite.");*/
    
    do {
      /* Cas normal */
      /* Calcule la nouvelle position de l'unite active en fonction des coordonnees du clic de la souris */
      MLV_wait_mouse(&userX, &userY);
      userX = userX/30-1;
      userY = userY/30-1;

    } while(deplacerOuAttaquer(unite, monde, userX, userY) < 0 && MLVactiverNeRienFaire(userX*30+1, userY*30+1) == 0);
    
    MLVdesactiverNeRienFaire();

    /* On passe à l'unite suivante */
    unite = unite->suiv;
  }
  
  /* Le tour se termine */
  MLVafficherDansZoneTexte("Votre tour est terminé.\nAu suivant !");
  
}

/*
  Gere le tour des deux joueurs
  Incrémente le compteur de tours
*/
void gererTour(Monde * monde) {
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
void viderMonde(Monde * monde) {
  /* Supprime les unites */
  while (monde->rouge.premier != NULL) {
    enleverUnite(monde->rouge.premier, monde);
  }
  while (monde->bleu.premier != NULL) {
    enleverUnite(monde->bleu.premier, monde);
  }
  initialiserMonde(monde);
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
  int forceStop = 0;

  /* Prepare le plateau et positionne les unites initiales */
  Monde monde;
  MLVinit();
  initialiserMonde(&monde);
  remplirMonde(&monde);
  MLVafficherTutoriel(&monde);
  
  /* Laisse chaque joueur jouer */
  while (monde.rouge.premier != NULL && monde.bleu.premier != NULL && forceStop == 0) {
    gererTour(&monde);
    MLVafficherDansZoneTexte("Souhaitez-vous arreter là ?\nCliquez n'importe où pour continuer.");
    if (MLVactiverQuitter() == 1) {
      forceStop = 1;
    }
    MLVdesactiverQuitter();
  }
  
  /* Affiche le resultat et vide le monde */
  if (monde.rouge.premier == NULL && forceStop == 0) {
    MLVafficherDansZoneTexte("Le joueur BLEU a gagné.\nBravo !");
  } else if (monde.bleu.premier == NULL && forceStop == 0) {
    MLVafficherDansZoneTexte("Le joueur ROUGE a gagné.\nBravo !");
  }
  viderMonde(&monde);
}