#include <stdio.h>
#include <stdlib.h>

int majority(int *, int);
int frequency(int *, int, int);

int main(void) {
	int a[] = {1, 1, 0, 0, 0, 0, 0, 1};
	int N = 8;
	int m = majority(a, N);

	if (m!=-1) 
        printf("Elemento maggioritario: %d", m);
	else 
        printf("Il vettore non ha elemento maggioritario.");

	return 0;
}

int majority(int *a, int N) {
    // Splitto fino ad ottenere elementi uninitari e ritorno
	if (N==1) 
        return a[0];

	int left_maj, rigth_maj, m = N/2;

	left_maj = majority(a, m);
	rigth_maj = majority(a+m, m);
    
    // Una volta che so gli elementi maggioratori delle 2 metà dei sottovettori controllo chi è il maggioritario nel vettore originale se esiste
	if (left_maj==rigth_maj) 
        return left_maj;

	int left_count = frequency(a, N, left_maj);
	int rigth_count = frequency(a, N, rigth_maj);

	if (left_count>N/2) 
        return left_maj;
	else if (rigth_count>N/2) 
        return rigth_maj;
	else 
        return -1;
}

int frequency(int *a, int N, int el) {
	int i, counter=0;
	for (i=0; i<N; i++) 
        if (a[i]==el) 
            counter++;
	return counter;
}