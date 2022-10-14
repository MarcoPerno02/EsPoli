#include <stdio.h>
#include <stdlib.h>


void malloc2dP(int*** mat);
void separa(int **mat, int nr, int nc, int **vetBianco, int **vetNero);

int nr;
int nc;

int main() 
{   
    int **mat = NULL;
    malloc2dP(&mat);
    if(mat != NULL) {
        int *vetBianco;
        int *vetNero;
        int dimBianco = (nr*nc/2);
        int dimNero = dimBianco;
        if(nr*nc % 2 != 0) 
            dimBianco++;
        vetBianco = (int *) malloc(dimBianco*sizeof(int));
        vetNero = (int *) malloc(dimNero*sizeof(int));
        separa(mat, nr, nc, &vetBianco, &vetNero);
        printf("Vet bianco:\n");
        for(int i = 0; i < dimBianco; i++) {
            printf("%d ", vetBianco[i]);
        }
        printf("\n");
        printf("Vet nero:\n");
        for(int i = 0; i < dimNero; i++) {
            printf("%d ", vetNero[i]);
        }
        free(mat);
        free(vetBianco);
        free(vetNero);
    }
}

void malloc2dP(int*** mat) 
{
    FILE *fMat;
    if((fMat = fopen("mat.txt", "r")) == NULL) {
        printf("Errore nell'aprire il file corse.txt\n");
    }
    else {
        fscanf(fMat, "%d %d", &nr, &nc);
        int **righe;
        righe = (int **)malloc(nr*sizeof(int *));
        for(int i = 0; i < nr; i++) {
            righe[i] = (int *)malloc(nc*sizeof(int));
            for(int j = 0; j < nc; j++) {
                int cella;
                fscanf(fMat, "%d", &cella);
                righe[i][j] = cella;
            }
        }
        *mat = righe;
        fclose(fMat);
    }
    
}

void separa(int **mat, int nr, int nc, int **vetBianco, int **vetNero) 
{
    int contVetBianco = 0, contVetNero = 0;
    for(int i = 0; i < nr; i++) {
        for(int j = 0; j < nc; j++) {
            if((i+j) % 2 == 0) {
                (*vetBianco)[contVetBianco] = mat[i][j];
                contVetBianco++;
            }
            else {
                (*vetNero)[contVetNero] = mat[i][j];
                contVetNero++;
            }
        }
    }
}