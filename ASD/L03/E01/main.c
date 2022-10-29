#include <stdio.h>
#include <stdlib.h>

int majority(int *, int);
int frequency(int *, int, int);

int main(void) {
	int a[] = {1, 1, 1, 4, 5, 6, 1};
	int N = 7;
	int m = majority(a, N);

	if (m!=-1) 
        printf("Elemento maggioritario: %d", m);
	else 
        printf("Il vettore non ha elemento maggioritario.");

	free(m);
	return 0;
}

int majority(int *a, int N) {
    // Splitto fino ad ottenere elementi uninitari e ritorno
	if (N==1) 
        return a[0];

	int lmaj, rmaj, m = N/2;

	lmaj = majority(a, m);
	rmaj = majority(a+m, m);
    
    // Una volta che so gli elementi maggioratori delle 2 metà dei sottovettori controllo chi è il maggioritario nel vettore originale se esiste
	if (lmaj==rmaj) 
        return lmaj;

	int lcnt = frequency(a, N, lmaj);
	int rcnt = frequency(a, N, rmaj);

	if (lcnt>N/2) 
        return lmaj;
	else if (rcnt>N/2) 
        return rmaj;
	else 
        return -1;
}

int frequency(int *a, int N, int el) {
	int i, cnt=0;
	for (i=0; i<N; i++) 
        if (a[i]==el) 
            cnt++;
	return cnt;
}