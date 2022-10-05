#include <stdio.h>
#include <stdlib.h>

void leggiMatrice(FILE* finput, int nr, int nc, int matrice[nr][nc]);
void stampaMatrice(int nr, int nc, int matrice[nr][nc]);

int main(void)
{
    FILE *finput;
    char nomeFile[20];
    printf("Inserisci nome file: ");
    scanf("%s", nomeFile);
    if((finput = fopen(nomeFile , "r")) == NULL) {
        printf("Errore nell'aprire il file %s\n", nomeFile);
        return 1;
    };

    int aus, dim, dim_aus;
    const int nr = fscanf(finput, "%d", &aus) * aus;
    const int nc = fscanf(finput, "%d", &aus) * aus;
    int matrice[nr][nc];
    leggiMatrice(finput, nr, nc, matrice);



    printf("Inserisci dim: ");
    if((dim = scanf("%d", &dim_aus) * dim_aus) > 0 && dim >= 1 && dim <= nr && dim <= nc) {
        int matrice_max[dim][dim], matrice_aus[dim][dim];
        int sum_max = 0;
        printf("Sottomatrici: \n");
        for(int i = 0; i <= nr - dim; i++) {
            for(int j = 0; j <= nc - dim; j++) {
                int i_aus, j_aus, sum = 0;
                for(i_aus = 0; i_aus < dim; i_aus++) {
                    for(j_aus = 0; j_aus < dim; j_aus++) {
                        matrice_aus[i_aus][j_aus] = matrice[i + i_aus][j + j_aus];
                        sum += matrice[i + i_aus][j + j_aus];
                    }
                }
                stampaMatrice(dim, dim, matrice_aus);
                printf("\n");
                if(sum > sum_max) {
                    for(i_aus = 0; i_aus < dim; i_aus++) {
                        for(j_aus = 0; j_aus < dim; j_aus++) {
                            matrice_max[i_aus][j_aus] = matrice_aus[i_aus][j_aus];
                        }
                    }
                    sum_max = sum;
                }
            }
        }
        printf("Matrice max con somma %d:\n", sum_max);
        stampaMatrice(dim, dim, matrice_max);
    }
    else {
        printf("Dim non corretta");
    }

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

void stampaMatrice(int nr, int nc, int matrice[nr][nc]) {
    for(int i = 0; i < nr; i++) {
        for(int j = 0; j < nc; j++) {
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }
}