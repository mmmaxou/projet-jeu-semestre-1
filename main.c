/* Programme Tableaux statiques a deux dimensions */

#include <stdio.h>
#define N 4

void initialiseTab(int tab[N][N]) {
	printf("Remplissage du tableau ...\n");
	int i, j, n = 0;
	for ( i=0; i<N; i++) {
		for ( j=0; j<N; j++) {
			/* Question */
			/*
				scanf("%d", &n);
				tab[i][j] = n;
			*/
			
			
			/* Handy way */
			tab[i][j] = i+j+n;
		}
	}
}
void afficheTab(int tab[N][N]) {
	printf("Affichage du tableau ...\n");
	int i, j;
	for ( i=0; i<N; i++) {
		for ( j=0; j<N; j++) {
			printf("%d ", tab[i][j]);
		}
		printf("\n");
	}
}
void remplitDiagonale(int tab[N][N]) {
	printf("Remplissage des diagonales du tableau ...\n");
	int i, j;
	/*
	for ( i=0; i<N; i++) {
		for ( j=0; j<N; j++) {
			if ( i==j ) {
				tab[i][j] = 0;
			}
		}
	}
	*/
	
	for ( i=0, j=0; i<N && j<N; i++, j++) {
		tab[i][j] = 0;
	}
}
void remplitPartieSup(int tab[N][N]) {
	printf("Remplissage des parties superieures du tableau ...\n");
	int i, j;
	/*
	for ( i=0; i<N; i++) {
		for ( j=0; j<N; j++) {
			if ( i<j ) {
				tab[i][j] = 1;
			}
		}
	}
	*/
	for ( i=0; i<N; i++) {
		for ( j=i+1; j<N; j++) {
			tab[i][j] = 1;
		}
	}
	
}
void sym(int tab[N][N]) {
	printf("Symetrie n");
	int i, j;
	/*
	for ( i=0; i<N; i++) {
		for ( j=0; j<N; j++) {
			if ( j<i ) {
				tab[i][j] = tab[j][i];
			}
		}
	}
	*/
	
	for ( i=0; i<N; i++) {
		for ( j=i+1; j<N; j++) {
			tab[j][i] = tab[i][j];
		}
	}
}

int main(int argc, char *argv[]) {
	
	int tab[N][N];
	
	initialiseTab(tab);
	remplitDiagonale(tab);
	remplitPartieSup(tab);
	sym(tab);
	afficheTab(tab);
	
	return 0;
}

