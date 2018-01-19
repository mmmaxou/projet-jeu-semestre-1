#ifndef UNITE_H
#define UNITE_H

#define LARG 18
#define LONG 12
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
  Unite * premier;
} UListe;
typedef struct monde {
  Unite * plateau[LARG][LONG];
  UListe rouge, bleu; /* Listes des deux joueurs */
  int tour; /* Numero du tour */
} Monde;

/* Affichage */
int afficherPlateau(Monde * monde);
void afficherUnite(Unite * u);
void printLigneBord();
void printLigneHaut();
void printLigneDelimitation();
void afficherTutoriel();

/* Affichage MLV */
void MLVinit ();
int MLVafficherPlateau(Monde * monde);
void MLVafficherDansZoneTexte(char *texte);
void MLVafficherUnite(Unite * u);
void MLVafficherUniteActive(Unite * u);
void MLVafficherTutoriel(Monde * monde);
void MLVactualiserPlateau(Monde * monde);
void MLVafficherToutesUnites(Monde * monde);
int MLVactiverQuitter();
int MLVactiverNeRienFaire(int userX, int userY);
int MLVactiverSauvegarder();
void MLVdesactiverQuitter();
void MLVdesactiverNeRienFaire();
void MLVdesactiverSauvegarder();

/* Monde */
void initialiserMonde(Monde * monde);
int placerAuMonde(Unite * unite, Monde * monde, int posX, int posY, char couleur);
void remplirMonde(Monde * monde);
void gererDemiTour(char joueur, Monde * monde);
void gererTour(Monde * monde);
void viderMonde(Monde * monde);
void gererPartie();

/* Unite */
int creerUnite(char type, Unite * unite);
void deplacerUnite(Unite * unite, Monde * monde, int destX, int destY);
int enleverUnite(Unite * unite, Monde * monde);
int attaquer(Unite * unite, Monde * monde, int posX, int posY);
int deplacerOuAttaquer(Unite * unite, Monde * monde, int destX, int destY);

/* Utils */
int abs(int x);
char* format(int n);

/* UListe */
void insertionUListe(UListe * l, Unite * u);
void afficherUListe(UListe * liste);
int supprimerUniteUListe(UListe * liste, Unite * unite);
#endif

/* TESTS */

/*
void testDeplacement(Monde * monde);
void testSuppression(Monde * monde);
*/
