#include <stdio.h>
#include <stdlib.h>

#define MAXR 3
#define MAXC 5

int buildMatrix(int V[], int N, int M[MAXR][MAXC], int nr, int nc) {
	// Controllo
	int n_el = 0;
	for(int i = 1; i < N; i+=2) {
		n_el+=V[i];
	}
	if(n_el  != nr*nc)
		return 0;
	int idx = 0;
	int num = V[idx];
	int reps = V[idx+1];
	for(int i = 0; i < nr; i++) {
		for(int j = 0; j < nc; j++) {
			M[i][j] = num;
			reps-=1;
			if(reps == 0) {
				if(idx+2 < N) { 
					idx+=2;
					num = V[idx];
					reps = V[idx+1];
				}
			}
		}
	}
	return 1;
}

int main(int argvc, char argvs[]) {
	int M[3][5];
	int V[14] = {1, 2, 17, 2, 3, 1, 8, 4, 6, 1, 7, 3, 5, 2};
	int ris = buildMatrix(V, 14, M, 3, 5);
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 5; j++) {
			printf("%d ", M[i][j]);
		}
		printf("\n");
	}
}