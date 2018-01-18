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

#define LARG_CASE 30 /* Dimension d'un cote d'une case */
static MLV_Image *gR;
static MLV_Image *sR;
static MLV_Image *rR;
static MLV_Image *oR;
static MLV_Image *gB;
static MLV_Image *sB;
static MLV_Image *rB;
static MLV_Image *oB;

/* TO DO :
Calcule userX userY en fonction du clic de la souris
Modifier les couleurs d'affichage
Afficher boutons Sauvegarde, Quitter
Afficher infos unite clic droit*/

/*
  Affiche le plateau et les unites qu'il y a dessus
  Retourne un code d'erreur :
  0: ???
  1: Pas d'erreur
*/

void MLVinit() {
  	MLV_create_window("Stratagème", "Stratagème", 600, 600);
	/* Cree la fenetre et affiche son fond colore */
	MLV_draw_filled_rectangle(0, 0, 600, 600, MLV_COLOR_SNOW4);

	gR = MLV_load_image("./img/guerrierROUGE.png");
	sR = MLV_load_image("./img/serfROUGE.png");
	rR = MLV_load_image("./img/reineROUGE.png");
	oR = MLV_load_image("./img/oeufROUGE.png");
	gB = MLV_load_image("./img/guerrierBLEU.png");
	sB = MLV_load_image("./img/serfBLEU.png");
	rB = MLV_load_image("./img/reineBLEU.png");
	oB = MLV_load_image("./img/oeufBLEU.png");

	MLV_resize_image_with_proportions(gR, LARG_CASE-6, LARG_CASE-6);
	MLV_resize_image_with_proportions(sR, LARG_CASE-6, LARG_CASE-6);
	MLV_resize_image_with_proportions(rR, LARG_CASE-6, LARG_CASE-6);
	MLV_resize_image_with_proportions(oR, LARG_CASE-6, LARG_CASE-6);

	MLV_resize_image_with_proportions(gB, LARG_CASE-6, LARG_CASE-6);
	MLV_resize_image_with_proportions(sB, LARG_CASE-6, LARG_CASE-6);
	MLV_resize_image_with_proportions(rB, LARG_CASE-6, LARG_CASE-6);
	MLV_resize_image_with_proportions(oB, LARG_CASE-6, LARG_CASE-6);
}


int MLVafficherPlateau(Monde *monde) {
  int testParite, posX, posY, x, y;
  posX = 30; posY = 30; testParite = 0;
  char numLignes[3], numColonnes[3];


  /* Affiche la zone de texte */
  /*MLV_draw_filled_rectangle(30, 420, 540, 150, MLV_COLOR_MEDIUM_SEA_GREEN);*/

  /* Parcourt les lignes et les colonnes */
  for(x = 0; x < LARG; x++) {

    for(y = 0; y < LONG; y++) {

      /* Affiche les numéros de lignes */
      if(posX == 30) {
      	sprintf(numLignes, "%d", (posY/30)-1);
      	MLV_draw_text(7, posY+7, numLignes, MLV_COLOR_WHITE);
      }

      /* Affiche le plateau quadrille */
	  if(testParite%2 == 0) {
	  	MLV_draw_filled_rectangle(posX, posY, LARG_CASE, LARG_CASE, MLV_COLOR_WHITE);
	  } else {
	  	MLV_draw_filled_rectangle(posX, posY, LARG_CASE, LARG_CASE, MLV_COLOR_SNOW3);
	  }

	  posY += 30;
	  testParite++;
	}

	/* Affiche les numéros de colonnes */
	sprintf(numColonnes, "%d", (posX/30)-1);
    MLV_draw_text(posX+7, 10, numColonnes, MLV_COLOR_WHITE);
    
	posY = 30;
	posX += 30;
	testParite++;
  }

  /* Affiche les infos */
  /*MLV_draw_text(60, 450, "Bla bla bla", MLV_COLOR_DARK_SLATE_GRAY);
  MLV_draw_text(60, 480, "12 34 56", MLV_COLOR_ANTIQUE_WHITE);*/
  /* Affiche les joueurs */

  return 1;
}

void MLVactualiserPlateau(Monde *monde) {
	MLVafficherPlateau(monde);
	MLVafficherToutesUnites(monde);
  	MLV_actualise_window();
}

void MLVafficherUniteSelectionee(Unite * u) {
  printf(">>> X: %d || Y: %d || clr: %c || genre: %c\n", u->posX, u->posY, u->couleur, u->genre );

  MLV_draw_filled_rectangle((u->posX+1) * LARG_CASE, (u->posY+1) * LARG_CASE, LARG_CASE, LARG_CASE, MLV_COLOR_GOLD1);
  
  MLVafficherUnite(u);
  MLV_actualise_window();

  /*
  #B82121 ROUGE
  #0B60B5 BLEU
  */

}

void MLVafficherUnite(Unite * u) {
	if ( u->couleur == ROUGE ) {
		if ( u->genre == SERF ) {
			MLV_draw_image(sR, (u->posX+1) * LARG_CASE+3, (u->posY+1) * LARG_CASE+3);
		} else if ( u->genre == GUERRIER ) {
			MLV_draw_image(gR, (u->posX+1) * LARG_CASE+3, (u->posY+1) * LARG_CASE+3);
		} /*else if ( u->genre == REINE ) {
			MLV_draw_image(rR, (u->posX+1) * LARG_CASE+3, (u->posY+1) * LARG_CASE+3);
		} else if ( u->genre == OEUF ) {
			MLV_draw_image(oR, (u->posX+1) * LARG_CASE+3, (u->posY+1) * LARG_CASE+3);
		}*/
	}

	if ( u->couleur == BLEU ) {
		if ( u->genre == SERF ) {
			MLV_draw_image(sB, (u->posX+1) * LARG_CASE+3, (u->posY+1) * LARG_CASE+3);
		} else if ( u->genre == GUERRIER ) {
			MLV_draw_image(gB, (u->posX+1) * LARG_CASE+3, (u->posY+1) * LARG_CASE+3);
		} /*else if ( u->genre == REINE ) {
			MLV_draw_image(rB, (u->posX+1) * LARG_CASE+3, (u->posY+1) * LARG_CASE+3);
		} else if ( u->genre == OEUF ) {
			MLV_draw_image(oB, (u->posX+1) * LARG_CASE+3, (u->posY+1) * LARG_CASE+3);
		}*/
	}
}

void MLVafficherToutesUnites(Monde * monde) {
	Unite * u = monde->rouge.premier;
	while (u != NULL) {		
  		MLVafficherUnite(u);
		u = u->suiv;
  	}

  	u = monde->bleu.premier;
	while (u != NULL) {
  		MLVafficherUnite(u);
		u = u->suiv;
  	}

}

void MLVafficherTutoriel(Monde * monde) {
	/*printLigneDelimitation();
	printf("\nCe jeu ce joue à deux joueurs.\nChaque joueur possède 2 Serfs (représentés par un 's') et un Guerrier (représenté par un 'g')\n Le jeu se déroule en tour. Le joueur ROUGE (en bas) commence la partie. Durant chaque tour de jeu, on demande au joueur ce qu'il souhaite faire.\n");
	printf("Entrez les coordonnées de la case vers laquelle se deplacer / attaquer, séparées par un espace (ex: '10 15'), ou bien entrez '-1 -1' pour ne rien faire.\n\n");
	printLigneDelimitation();*/

  	/* Affiche le tutorial */
  	char tutoriel[750] = "Ce jeu se joue à deux joueurs.\nChaque joueur possède deux Serfs et un Guerrier.\nLe jeu se déroule en tour. Le joueur ROUGE (en bas) \ncommence la partie. Durant chaque tour de jeu, \non demande au joueur ce qu'il souhaite faire.\nCliquez sur la case vers laquelle vous souhaitez que \nvotre unité active (celle dont la case est jaune) \nse déplace/attaque.";
  	MLVafficherDansZoneTexte(tutoriel);
	MLVafficherPlateau(monde);
	MLVafficherToutesUnites(monde);
  	MLV_actualise_window();
}

void MLVafficherDansZoneTexte(char *texte) {
	MLV_draw_text_box(30, 420, 420, 150, texte, 2, MLV_COLOR_SNOW3, MLV_COLOR_GREY21, MLV_COLOR_SNOW3, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_TOP);
}

void MLVafficherSauvegarder() {
	MLV_draw_text_box(460, 420, 110, 30, "SAUVEGARDER", 2, MLV_COLOR_GREY21, MLV_COLOR_SNOW3, MLV_COLOR_GREY21, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	/* Appel de la fonction SAUVEGARDER */
}

void MLVafficherQuitter() {
	MLV_draw_text_box(460, 460, 110, 30, "QUITTER", 2, MLV_COLOR_GREY21, MLV_COLOR_SNOW3, MLV_COLOR_GREY21, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	/* Appel de la fonction QUITTER */
}