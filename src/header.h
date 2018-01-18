#ifndef UNITE_H
#define UNITE_H

#define LARG 18
#define LONG 12
#define ROUGE 'R'
#define BLEU 'B'
#define SERF 's'
#define GUERRIER 'g'
#define REINE 'r'
#define OEUF 'o'

/* STRUCTURES */
typedef struct unite {
  int posX, posY; /* Pour stocker les coordonnees de l'unite*/
  char couleur; /* ROUGE ou BLEU */
  char genre; /* GUERRIER ou SERF ou REINE */
	int pm; /* Points de mouvements */
	int attente; /* Tour de recharge pour la reine */
	int pv;
	int atk;
	int id;
  struct unite *suivTile;
  struct unite *suivClr;
  struct unite *precTile;
  struct unite *precClr;
} Unite;

typedef struct doublelist {
	Unite * premier;
	Unite * dernier;	
	int taille;
} UListe;

typedef struct monde {
  UListe plateau[LARG][LONG];
  UListe rouge, bleu; /* Listes des deux joueurs */
  int tour; /* Numero du tour */
} Monde;

/* Affichage */
int afficherPlateau ( Monde *monde );
void afficherUnite( Unite * u );
void printLigneBord ();
void printLigneHaut ();
void printLigneDelimitation ();
void afficherTutoriel ();

/* Monde */
void initialiserMonde ( Monde *monde );
int placerAuMonde ( Unite *unite, Monde *monde, int posX,int posY, char couleur );
void remplirMonde ( Monde *monde );
void gererDemiTour ( char joueur, Monde *monde );
void gererTour ( Monde *monde );
void viderMonde ( Monde *monde );
void gererPartie ();

/* Unite */
int creerUnite ( char type, Unite *unite );
void donnerStatsUnite ( char type, Unite *unite );
void deplacerUnite ( Unite *unite, Monde *monde, int destX, int destY );
int enleverUnite ( Unite *unite, Monde *monde );
int attaquer ( Unite *unite, Monde *monde, int posX, int
posY, int riposte );
int deplacerOuAttaquer (Unite *unite, Monde *monde, int destX, int destY);
int produireUnOeuf ( Unite *unite, Monde *monde, int destX, int destY, char joueur );
int donnerValeur ( Unite * unite );

/* Utils */
int abs ( int x );
char* format2( int n );
char* format3( int n );

/* UListe */
void ajouterDebutUListeTile ( UListe * liste , Unite * unite );
void ajouterFinUListeTile ( UListe * liste , Unite * unite );
void ajouterDebutUListeClr ( UListe * liste , Unite * unite );
void ajouterFinUListeClr ( UListe * liste , Unite * unite );
void afficherUListeTile ( UListe * liste );
void afficherUListeClr ( UListe * liste );
int supprimerUniteUListeTile (  UListe * liste, int id );
int supprimerUniteUListeClr (  UListe * liste, int id );

/* Sauvegarder */
int sauvegarder ( Monde * monde );
void ecrireUnite ( Unite * unite, FILE * fichier );
int charger ( Monde * monde );
int lireUnite ( FILE * fichier, Monde * monde );

/* Tests */
void genererUnitesCentre ( Monde * monde );


#endif



