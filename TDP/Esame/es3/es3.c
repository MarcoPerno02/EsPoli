#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int pos;
	int len;
} sottovet;

void maxOdd(int v[], int N) {
	sottovet vettori[N];
	int cont = 0;
	int i = 0;
	int j = 0;
	int max = -1;
	while(i!=N) {
		if(v[i]%2 != 0) {
			cont++;
		}
		else if(cont!=0 || i==N-1) {
			if(cont > max) {
				max = cont;
				vettori[0].pos = i-cont;
				vettori[0].len = cont;
				j = 1;
				cont = 0;
			}
			else if(cont == max) {
				vettori[j].pos = i-cont;
				vettori[j].len = cont;
				j++;
				cont = 0;
			}
		}
		i++;
	}
	for(i=0;i<j;i++) {
		for(int z=0; z<vettori[i].len; z++) {
			printf("%d ", v[vettori[i].pos + z]);
		}
		printf("\n");
	}
	
}

int main() {
	int v[10] = {1, 3, 7, 1, 0, 1, 9, 3, 1, 0};
	maxOdd(v, 10);
}