#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#define LARG 18
#define LONG 12
#define ROUGE 'R'/* Identifiant du premier joueur */
#define BLEU 'B' /* Identifiant du deuxieme joueur */
#define SERF 's'/* Identifiant du Serf */
#define GUERRIER 'g'/* Identifiant du Guerrier */

int abs ( int x ) {
	return x < 0 ? -x : x;
}

char* format( int n ) {
	char *s = malloc(3 * sizeof(*s));
	s[0] = '0';
	s[1] = '0';
	s[2] = '0';
	
	if ( n == 0 ) {
		return "000";
	}
	
	s[2] += n % 10;
	if( n >= 10) {
		s[1] += (n-(n%10)) / 10;
	}
	return s;
}