#ifndef UNITE_H
#define UNITE_H

#define LONG 12
#define LARG 18
#define ROUGE 'R'
#define BLEU 'B'
#define SERF 's'
#define GUERRIER 'g'

/* STRUCTURES */
typedef struct unite {
  int posX, posY; /* Pour stocker les coordonnees de l'unite*/
  char couleur; /* ROUGE ou BLEU */
  char genre; /* GUERRIER ou SERF*/
  struct unite *suiv; /* liste des unites suivantes*/
} Unite;
typedef struct liste { 
  Unite *premier;
} UListe;
typedef struct monde {
  Unite *plateau[LONG][LARG];
  UListe rouge, bleu; /* Listes des deux joueurs */
  int tour; /* Numero du tour */
} Monde;

/* DECLARATIONS DES FONCTIONS */
void initialiserMonde( Monde *monde );
int creerUnite( char type, Unite *unite );
int placerAuMonde( Unite *unite, Monde *monde, int posX,int posY, char couleur );
int deplacerUnite( Unite *unite, Monde *monde, int destX, int destY );
int afficherPlateau( Monde *monde );
void printborderline();
void remplirMonde ( Monde *monde );
int enleverUnite( Unite *unite, Monde *monde );
int attaquer( Unite *unite, Monde *monde, int posX, int
posY );

/* UListe */
void insertionUListe ( UListe *l, Unite *u );
void afficherUListe ( UListe *liste );
int supprimerUniteUListe ( UListe *liste, Unite *unite );
#endif