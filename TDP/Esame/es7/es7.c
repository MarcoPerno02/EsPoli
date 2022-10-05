#include <stdio.h>
#include <stdlib.h>

int areaTot(FILE *fp) {
	int M[10][10];
	for(int i = 0; i < 10; i++) {
		for(int j = 0; j < 10; j++) {
			M[i][j] = 0;
		}
	}
	int x1, y1, x2, y2, areaTot = 0;
	while(fscanf(fp, "%d %d %d %d", &x1, &y1, &x2, &y2) != EOF) {
		for(int i = x1; i<x2; i++) {
			for(int j = y1; j<y2; j++) {
				M[i][j] = 1;
			}
		}
	}

	for(int i = 0; i<10; i++) {
		for(int j = 0; j<10; j++) {
			if(M[i][j] == 1)
				areaTot++;
		}
	}
	return areaTot;
}

int main(int agrvc, char argvs[]) {
	FILE *fp;
	if((fp = fopen("input.txt", "r")) == NULL) {
		printf("No file");
		return -1;
	}
	printf("%d", areaTot(fp));
	fclose(fp);
}