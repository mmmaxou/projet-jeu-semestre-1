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
#define REINE 'r'/* Identifiant de la Reine */
#define OEUF 'o'/* Identifiant de l'oeuf */
#define LARG_CASE 30 /* Dimension d'un cote d'une case */
#define WIDTH 600
#define HEIGHT 600
static MLV_Image *gR;
static MLV_Image *sR;
static MLV_Image *rR;
static MLV_Image *oR;
static MLV_Image *gB;
static MLV_Image *sB;
static MLV_Image *rB;
static MLV_Image *oB;


/*
	Initialise l'environnement pour le code MLV
	Créer la fenetre
	Charge les images dont on se sert
	Redimensionne les images pour les utiliser correctement
*/
void MLVinit() {
	/* Cree la fenetre et affiche son fond colore */
  MLV_create_window("Stratagème", "Stratagème", WIDTH, HEIGHT);
	MLV_draw_filled_rectangle(0, 0, WIDTH, HEIGHT, MLV_COLOR_SNOW4);

	/* Charge les images */
	gR = MLV_load_image("./img/guerrierROUGE.png");
	sR = MLV_load_image("./img/serfROUGE.png");
	rR = MLV_load_image("./img/reineROUGE.png");
	oR = MLV_load_image("./img/oeufROUGE.png");
	gB = MLV_load_image("./img/guerrierBLEU.png");
	sB = MLV_load_image("./img/serfBLEU.png");
	rB = MLV_load_image("./img/reineBLEU.png");
	oB = MLV_load_image("./img/oeufBLEU.png");

	/* Redimensionne les images */
	MLV_resize_image_with_proportions(gR, LARG_CASE-6, LARG_CASE-6);
	MLV_resize_image_with_proportions(sR, LARG_CASE-6, LARG_CASE-6);
	MLV_resize_image_with_proportions(rR, LARG_CASE-6, LARG_CASE-6);
	MLV_resize_image_with_proportions(oR, LARG_CASE-6, LARG_CASE-6);
	MLV_resize_image_with_proportions(gB, LARG_CASE-6, LARG_CASE-6);
	MLV_resize_image_with_proportions(sB, LARG_CASE-6, LARG_CASE-6);
	MLV_resize_image_with_proportions(rB, LARG_CASE-6, LARG_CASE-6);
	MLV_resize_image_with_proportions(oB, LARG_CASE-6, LARG_CASE-6);
}


/*
  Affiche le plateau
  Retourne un code d'erreur :
  0: ???
  1: Pas d'erreur
*/
int MLVafficherPlateau(Monde * monde) {
  int testParite, posX, posY, x, y;
  char numLignes[3], numColonnes[3];
  posX = 30; 
	posY = 30; 
	testParite = 0;

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
	testParite++;MLV_actualise_window();
  }

  return 1;
}

/*
	Affiche le plateau et affiche toutes les unites
	On l'appelle après chaque action du joueur
*/
void MLVactualiserPlateau(Monde * monde) {
	MLVafficherPlateau(monde);
	MLVafficherToutesUnites(monde);
  MLV_actualise_window();
}

/* 
	Colore en jaune la case sous l'unite active (en cours de déplacement)
	Affiche les informations de l'unite active dans la case en bas
*/
void MLVafficherUniteActive(Unite * u) {
  char infos[100];
	/* Affiche les informations de l'unite active dans la case en bas */
  sprintf(infos, "%s (%d %d)\nPM: %d|| PV: %d\nAttaque: %d", genre(u->genre), u->posX, u->posY, u->pm, u->pv, u->atk);
  MLV_draw_text_box(460, 510, 110, 60, infos, 1, MLV_COLOR_WHITE, MLV_COLOR_GREY21, MLV_COLOR_WHITE, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

	/* Affiche la case en jaune */
  MLV_draw_filled_rectangle((u->posX+1) * LARG_CASE, (u->posY+1) * LARG_CASE, LARG_CASE, LARG_CASE, MLV_COLOR_GOLD1);
	
	/* Réaffiche l'unité */
  MLVafficherUnite(u);
  MLV_actualise_window();
}

/* 
	Affiche l'image représentant l'unité en fonction de sa couleur et de son genre
*/
void MLVafficherUnite(Unite * u) {
	if ( u->couleur == ROUGE ) {
		if ( u->genre == SERF ) {
			MLV_draw_image(sR, (u->posX+1) * LARG_CASE+3, (u->posY+1) * LARG_CASE+3);
		} else if ( u->genre == GUERRIER ) {
			MLV_draw_image(gR, (u->posX+1) * LARG_CASE+3, (u->posY+1) * LARG_CASE+3);
		} else if ( u->genre == REINE ) {
			MLV_draw_image(rR, (u->posX+1) * LARG_CASE+3, (u->posY+1) * LARG_CASE+3);
		} else if ( u->genre == OEUF ) {
			MLV_draw_image(oR, (u->posX+1) * LARG_CASE+3, (u->posY+1) * LARG_CASE+3);
		}
	}
	if ( u->couleur == BLEU ) {
		if ( u->genre == SERF ) {
			MLV_draw_image(sB, (u->posX+1) * LARG_CASE+3, (u->posY+1) * LARG_CASE+3);
		} else if ( u->genre == GUERRIER ) {
			MLV_draw_image(gB, (u->posX+1) * LARG_CASE+3, (u->posY+1) * LARG_CASE+3);
		} else if ( u->genre == REINE ) {
			MLV_draw_image(rB, (u->posX+1) * LARG_CASE+3, (u->posY+1) * LARG_CASE+3);
		} else if ( u->genre == OEUF ) {
			MLV_draw_image(oB, (u->posX+1) * LARG_CASE+3, (u->posY+1) * LARG_CASE+3);
		}
	}
	MLV_actualise_window();
}

/* 
	Affiche toutes les unités en parcourant la liste chainée et en appelant la fonction précédente
*/
void MLVafficherToutesUnites(Monde * monde) {
	Unite * u = monde->rouge.premier;
	while (u != NULL) {		
		MLVafficherUnite(u);
		u = u->suivClr;
	}
	u = monde->bleu.premier;
	while (u != NULL) {
		MLVafficherUnite(u);
		u = u->suivClr;
	}
}


/* 
	Affiche le tutorial en début de partie
*/
void MLVafficherTutoriel(Monde * monde) {
	
	MLVafficherPlateau(monde);
	MLVafficherDansZoneTexte("Ce jeu se joue à deux joueurs.\nChaque joueur possède:\n• 2 Serfs 's'\n• 1 Guerrier 'g'( Bat le Serf )\n• 1 Reine 'r' ( Immobile, elle produit des unites )\n  |> La reine crée des oeufs sur une position qui lui est\n      adjacente\n  |> Les oeufs mettent 1 tour pour éclore.");
	MLVattendreValidation();	
	
	MLVafficherDansZoneTexte("Le jeu se déroule au tour par tour.\nChaque tour le joueur qui commence est choisi\naléatoirement. A chaque tour, le joueur peut effectuer une\naction pour chacune de ses unités. Le joueur clique sur la\ncase vers laquelle il souhaite que son unité active\n(celle dont la case est jaune) se déplace ou attaque.\nPour passer à l'unité suivante sans rien faire,\nil peut double-cliquer sur le bouton 'NE RIEN FAIRE'.");
	MLVattendreValidation();
	
	MLVafficherDansZoneTexte("Il peut y avoir plusieurs unités sur une même case.\nCela permet de défendre certaines unités plus fragiles.\nPar exemple, s'il y a une reine, elle sera défendue par\ntoutes les autres unités.\nAttention, seule l'unité du dessus est affichée.\nA la fin de chaque tour, il est possible de sauvegarder\nla partie, quitter le jeu ou continuer.");
	MLVattendreValidation();
	
	MLVafficherToutesUnites(monde);
	MLVdesactiverQuitter();
	MLVdesactiverNeRienFaire();
	MLVdesactiverSauvegarder();
	MLV_actualise_window();
}

/* 
	Affiche du texte entré en paramètre dans la zone de texte sous le plateau.
*/
void MLVafficherDansZoneTexte(char *texte) {
	MLV_draw_text_box(30, 420, 420, 150, texte, 2, MLV_COLOR_SNOW3, MLV_COLOR_GREY21, MLV_COLOR_SNOW3, MLV_TEXT_LEFT, MLV_HORIZONTAL_LEFT, MLV_VERTICAL_TOP);
	MLV_actualise_window();
}

/* 
	Affiche le bouton quitter la partie
*/
void MLVactiverQuitter() {
	MLV_draw_text_box(460, 420, 110, 20, "QUITTER", 2, MLV_COLOR_GREY21, MLV_COLOR_WHITE, MLV_COLOR_GREY21, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_actualise_window();
}

/* 
	Affiche le bouton continuer
*/
void MLVactiverNeRienFaire() {
	MLV_draw_text_box(460, 450, 110, 20, "CONTINUER", 2, MLV_COLOR_GREY21, MLV_COLOR_WHITE, MLV_COLOR_GREY21, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_actualise_window();
}

/*
	Affiche le bouton sauvegarder la partie
*/
void MLVactiverSauvegarder() {
	MLV_draw_text_box(460, 480, 110, 20, "SAUVEGARDER", 2, MLV_COLOR_GREY21, MLV_COLOR_WHITE, MLV_COLOR_GREY21, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_actualise_window();
}

/* 
	Propose de ne pas déplacer l'unité
	Renvoi :
	0 = Ne clique pas sur le bouton
	1 = Clique sur le bouton
*/
int MLVactiverNeRienFaireUnite(int userX, int userY) {
	MLV_draw_text_box(460, 450, 110, 20, "NE RIEN FAIRE", 2, MLV_COLOR_GREY21, MLV_COLOR_WHITE, MLV_COLOR_GREY21, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_actualise_window();
	MLV_wait_mouse(&userX, &userY);
    
	if (userX >= 460 && userX <= 570 && userY >= 450 && userY <= 470) {
		MLV_actualise_window();
		return 1;
	} else {
		return 0;
	}
}

/* 
	Propose de charger la derniere partie
	Renvoi :
	 0 = Ne souhaite pas charger
	 1 = Souhaite charger
	-1 = Erreur 
*/
int MLVactiverCharger() {
	int userX, userY;
	int valide = 1;
	MLVafficherDansZoneTexte("Souhaitez vous :\n -> Charger la dernière partie\n -> Commencer une nouvelle partie\n");
	MLV_draw_text_box(460, 510, 110, 20, "CHARGER", 2, MLV_COLOR_GREY21, MLV_COLOR_WHITE, MLV_COLOR_GREY21, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_draw_text_box(460, 540, 110, 20, "NOUVEAU", 2, MLV_COLOR_GREY21, MLV_COLOR_WHITE, MLV_COLOR_GREY21, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_actualise_window();
	
	do {		
		MLV_wait_mouse(&userX, &userY);    
		if (userX >= 460 && userX <= 570 && userY >= 510 && userY <= 530) {
			/* Charger */
			MLV_actualise_window();
			valide = 0;
			return 1;
		} else if (userX >= 460 && userX <= 570 && userY >= 540 && userY <= 560){
			/* Ne pas charger */
			MLV_actualise_window();
			valide = 0;
			return 0;
		} 
	} while ( valide == 1 );
	return -1;
}

/*
	Fonction qui gere la fin du tour
	Elle propose de quitte, sauvbegarder et continuer
	Si l'on sauvegarde, on peut ensuite choisir à nouveau de quitter ou continuer
	Si l'on quitte, le monde est vidé et le programme se fermer
	Si l'on continue, la fonction se termine et le programme continue 
*/
void MLVgererFinTour(Monde * monde) {	
	int userX, userY;
	int valide = 0;
	int sauvegarde = 0;
	MLVactiverQuitter();
	MLVactiverNeRienFaire();
	MLVactiverSauvegarder();
	
	do {
		MLVafficherDansZoneTexte("Souhaitez-vous :\n -> Arrêter\n -> Sauvegarder \n -> Ne rien faire et continuer ?");
		MLV_wait_mouse(&userX, &userY);
		if (userX >= 460 && userX <= 570 && userY >= 480 && userY <= 500 && sauvegarde == 0) {
			/* Appel de la fonction SAUVEGARDER */
			MLVafficherDansZoneTexte("Sauvegarde en cours ...\n");
			sauvegarder( monde );
			MLVafficherDansZoneTexte("Sauvegarde terminée\n");
			MLVattendreValidation();
			MLVdesactiverSauvegarder();
			sauvegarde = 1;
		} else if (userX >= 460 && userX <= 570 && userY >= 450 && userY <= 470) {
			/* Ne rien faire */
			MLV_actualise_window();
			valide = 1;
		} else if (userX >= 460 && userX <= 570 && userY >= 420 && userY <= 440) {
			/* Quitter */
			valide = 1;
			exit(0);
		} else {
			MLVafficherDansZoneTexte("Sélection invalide\nVeuillez choisir une action.");
			MLV_actualise_window();
		}
	} while ( valide == 0 );
		
	MLVdesactiverQuitter();
	MLVdesactiverNeRienFaire();
	MLVdesactiverSauvegarder();
}

/*
	Cache le bouton quitter la partie
*/
void MLVdesactiverQuitter() {
	MLV_draw_text_box(460, 420, 110, 20, "QUITTER", 2, MLV_COLOR_SNOW3, MLV_COLOR_SNOW4, MLV_COLOR_SNOW3, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_actualise_window();
}

/*
	Cache le bouton continuer
*/
void MLVdesactiverNeRienFaire() {
	MLV_draw_text_box(460, 450, 110, 20, "NE RIEN FAIRE", 2, MLV_COLOR_SNOW3, MLV_COLOR_SNOW4, MLV_COLOR_SNOW3, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_actualise_window();
}

/*
	Cache le bouton sauvegarder la partie
*/
void MLVdesactiverSauvegarder() {
	MLV_draw_text_box(460, 480, 110, 20, "SAUVEGARDER", 2, MLV_COLOR_SNOW3, MLV_COLOR_SNOW4, MLV_COLOR_SNOW3, MLV_TEXT_LEFT, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_actualise_window();
}

/*
	Cache le bouton charger
*/
void MLVdesactiverCharger() {
	MLV_actualise_window();
}

/*
	Affiche un message qui indique à l'utilisateur que l'on attend sa validation
	Le joueur doit cliquer n'importe ou sur l'ecran pour continuer 
*/
void MLVattendreValidation() {
	int userX, userY;	
	MLV_draw_text( 170, HEIGHT-22, "Cliquez n'importe où pour continuer", MLV_COLOR_GOLD1);
	MLV_actualise_window();
	MLV_wait_mouse(&userX, &userY);
	MLV_draw_filled_rectangle(0, HEIGHT-25, WIDTH, 25, MLV_COLOR_SNOW4);
	MLV_actualise_window();
}

