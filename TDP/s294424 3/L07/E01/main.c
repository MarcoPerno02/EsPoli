#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int indice_riga;
    int indice_colonna;
    int altezza;
    int larghezza;
    int area;
} rettangolo;


void leggiMatrice(FILE* finput, int nr, int nc, int matrice[nr][nc]);
void analizzaMatrice(int nr, int nc, int matrice[nr][nc]);

int main(void) {
    FILE *finput;
    if((finput = fopen("input.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file input.txt");
        return 1;
    }

    int aus;
    const int nr = fscanf(finput, "%d", &aus) * aus;
    const int nc = fscanf(finput, "%d", &aus) * aus;
    int matrice[nr][nc];
    leggiMatrice(finput, nr, nc, matrice);
    analizzaMatrice(nr, nc, matrice);
    fclose(finput);
    return 0;
}

void leggiMatrice(FILE* finput, int nr, int nc, int matrice[nr][nc]) {
    int n, ris;
    int i = 0, j = 0;
    while((ris = fscanf(finput, "%d", &n) != -1)) {
        matrice[i][j] = n;
        if(j == nc - 1) {
            i++;
            j = 0;
        }
        else {
            j++;
        }
    }
}

void analizzaMatrice(int nr, int nc, int matrice[nr][nc]) {
    rettangolo rettangolo_max_area;
    rettangolo_max_area.area = -1;

    rettangolo rettangolo_max_larghezza;
    rettangolo_max_larghezza.altezza = 0;
    rettangolo_max_larghezza.indice_riga = -1;
    rettangolo_max_larghezza.indice_colonna = -1;
    rettangolo_max_larghezza.larghezza = -1;

    rettangolo rettangolo_max_altezza;
    rettangolo_max_altezza.altezza = 0;
    rettangolo_max_altezza.indice_riga = -1;
    rettangolo_max_altezza.indice_colonna = -1;
    rettangolo_max_altezza.larghezza = -1;

    rettangolo rettangolo_aus;
    rettangolo_aus.larghezza = 0;
    rettangolo_aus.altezza = 0;

    for(int i = 0; i < nr; i++) {
        for(int j = 0; j < nc; j++) {
            if(matrice[i][j] == 1) {
                // Calcolo dimensioni rettangolo
                int i_aus = i + 1;
                int j_aus = j + 1;
                while(i_aus < nc && matrice[i_aus][j] == 1)
                    i_aus++;
                while(j_aus < nr && matrice[i][j_aus] == 1)
                    j_aus++;
                rettangolo_aus.larghezza = (j_aus - j);
                rettangolo_aus.altezza = (i_aus - i);
                rettangolo_aus.area = rettangolo_aus.larghezza * rettangolo_aus.altezza;

                // Gestione casi
                if(rettangolo_aus.area > rettangolo_max_area.area) {
                    rettangolo_max_area.larghezza = (j_aus - j);
                    rettangolo_max_area.altezza = (i_aus - i);
                    rettangolo_max_area.indice_riga = i;
                    rettangolo_max_area.indice_colonna = j;
                    rettangolo_max_area.area = rettangolo_max_area.larghezza * rettangolo_max_area.altezza;
                }

                if(rettangolo_aus.altezza > rettangolo_max_altezza.altezza) {
                    rettangolo_max_altezza.larghezza = (j_aus - j);
                    rettangolo_max_altezza.altezza = (i_aus - i);
                    rettangolo_max_altezza.indice_riga = i;
                    rettangolo_max_altezza.indice_colonna = j;
                    rettangolo_max_altezza.area = rettangolo_max_altezza.larghezza * rettangolo_max_altezza.altezza;
                }

                if(rettangolo_aus.larghezza > rettangolo_max_larghezza.larghezza) {
                    rettangolo_max_larghezza.larghezza = (j_aus - j);
                    rettangolo_max_larghezza.altezza = (i_aus - i);
                    rettangolo_max_larghezza.indice_riga = i;
                    rettangolo_max_larghezza.indice_colonna = j;
                    rettangolo_max_larghezza.area = rettangolo_max_larghezza.larghezza * rettangolo_max_larghezza.altezza;
                }
                rettangolo_aus.area = 0;
            }
        }
    }
    printf("Max altezza: estremo=(%d,%d), altezza=%d, larghezza=%d, area=%d\n", rettangolo_max_altezza.indice_riga, rettangolo_max_altezza.indice_colonna, rettangolo_max_altezza.altezza, rettangolo_max_altezza.larghezza, rettangolo_max_altezza.area);
    printf("Max larghezza: estremo=(%d,%d), altezza=%d, larghezza=%d, area=%d\n", rettangolo_max_larghezza.indice_riga, rettangolo_max_larghezza.indice_colonna, rettangolo_max_larghezza.altezza, rettangolo_max_larghezza.larghezza, rettangolo_max_larghezza.area);
    printf("Max area: estremo=(%d,%d), altezza=%d, larghezza=%d, area=%d\n", rettangolo_max_area.indice_riga, rettangolo_max_area.indice_colonna, rettangolo_max_area.altezza, rettangolo_max_area.larghezza, rettangolo_max_area.area);

}