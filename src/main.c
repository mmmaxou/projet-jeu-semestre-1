#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#define LARG 18
#define LONG 12
#define ROUGE 'R'/* Identifiant du premier joueur */
#define BLEU 'B' /* Identifiant du deuxieme joueur */
#define SERF 's'/* Identifiant du Serf */
#define GUERRIER 'g'/* Identifiant du Guerrier */

int main(int argc, char *argv[]) {

  Monde monde;  
  initialiserMonde(&monde);
  remplirMonde(&monde);
	
	testDeplacement(&monde);
	/*testSuppression(&monde);*/
	/*testAttaque(&monde);*/
	
	
	
  return 0;
	
}
