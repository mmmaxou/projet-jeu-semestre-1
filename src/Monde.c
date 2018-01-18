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
void initialiserMonde(Monde *monde) {
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
int placerAuMonde(Unite *unite, Monde *monde, int posX, int posY, char couleur) {
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
void remplirMonde (Monde *monde) {
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
void gererDemiTour(char joueur, Monde *monde) {
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

    /* On affiche les informations de l'état actuel */
    MLVactualiserPlateau(monde);
    MLVafficherUniteSelectionee(unite);
    
    /* On demande à l'utilisateur ce qu'il veux faire */
    printf("Ou aller ? ");
    scanf("%d %d", &userX, &userY);
    if (userX != -1 && userY != -1) {
      /* Cas normal */
      deplacerOuAttaquer(unite, monde, userX, userY);   
    } else {     
      /* Ne rien faire */
      printf("L'unite attend\n");    
    }
    
    /* On passe à l'unite suivante */
    unite = unite->suiv;
  }
  
  /* On termine le tour */
  printLigneDelimitation();
  printf("Votre tour est terminé !\n");
  
}

/*
  Gere le tour des deux joueurs
  Incrémente le compteur de tours
*/
void gererTour(Monde *monde) {
  printf("Tour actuel : %d\n", monde->tour);
  printLigneDelimitation();
  gererDemiTour(ROUGE, monde);
  printLigneDelimitation();
  gererDemiTour(BLEU, monde);
  printLigneDelimitation();
  monde->tour++;
}

/*
  Vide le monde
  Libere toute la memoire
  Reinitialise la structure Monde
*/
void viderMonde(Monde *monde) {
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
  char c;
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
    printf("Voulez vous arreter la ? (Y/n)\n");
    scanf(" %c", &c);
    if (c == 'Y' || c == 'y') {
      printf("D'accord ! Salut :(\n");
      forceStop = 1;
    }
  }
  
  /* Resultat et vide le monde */
  
  if (monde.rouge.premier == NULL && forceStop == 0) {
    printf("Le joueur BLEU à gagné !!\nBravo :) :) :)\n");
  } else if (monde.bleu.premier == NULL && forceStop == 0) {
    printf("Le joueur rouge à gagné !!\nBravo :) :) :)\n");    
  }
  viderMonde(&monde);
}