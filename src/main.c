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

int main(int argc, char *argv[]) {

	
	/*testDeplacement(&monde);*/
	/*testSuppression(&monde);*/
	/*testAttaque(&monde);*/
  
  gererPartie();
	
  return 0;
	
}
