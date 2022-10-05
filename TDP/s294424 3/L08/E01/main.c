#include <stdio.h>
#include <stdlib.h>
#define NR 50
#define NC 50

typedef struct {
    int indice_riga;
    int indice_colonna;
    int altezza;
    int larghezza;
    int area;
} rettangolo;


int leggiMatrice(int matrice[][NC], int maxR, int *nr, int *nc);
void analizzaMatrice(int nr, int nc, int matrice[][NC]);
int riconosciRegione(int matrice[][NC], int nr, int nc, int r, int c, int *b, int *h);

int main(void) {
    int aus;
    int nr, nc;
    int matrice[NR][NC];
    if(leggiMatrice(matrice, NR, &nr, &nc) != 1)
        analizzaMatrice(nr, nc, matrice);
    return 0;
}

int leggiMatrice(int matrice[][NC], int maxR, int *nr, int *nc) {
    FILE *finput;
    if((finput = fopen("input.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file input.txt");
        return 1;
    }
    fscanf(finput, "%d", nr);
    fscanf(finput, "%d", nc);
    int n, ris;
    int i = 0, j = 0;
    while((ris = fscanf(finput, "%d", &n) != -1)) {
        matrice[i][j] = n;
        if(j == *nc - 1) {
            i++;
            j = 0;
        }
        else {
            j++;
        }
    }
    fclose(finput);
    return 0;
}

void analizzaMatrice(int nr, int nc, int matrice[][NC]) {
    for(int i = 0; i < nr; i++) {
        for(int j = 0; j < nc; j++) {
            int b, h;
            if(riconosciRegione(matrice, nr, nc, i, j, &b, &h) == 1) {
                printf("Rettangolo: estremo=(%d,%d), altezza=%d, larghezza=%d\n", i, j, h, b);
            }
        }
    }
}

int riconosciRegione(int matrice[][NC], int nr, int nc, int r, int c, int *b, int *h) {
    if(matrice[r][c] == 1 && (r-1 == -1 || matrice[r-1][c] == 0) && (c-1 == -1 || matrice[r][c-1] == 0)) {
        // Calcolo dimensioni rettangolo
        int i_aus = r + 1;
        int j_aus = c + 1;
        while(i_aus < nc && matrice[i_aus][c] == 1)
            i_aus++;
        while(j_aus < nr && matrice[r][j_aus] == 1)
            j_aus++;
        *b = (j_aus - c);
        *h = (i_aus - r);
        return 1;
    }
    else {
        return 0;
    }
}