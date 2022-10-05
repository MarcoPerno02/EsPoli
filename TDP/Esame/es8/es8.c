#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define DIM 5

void test(char *str, int vet[], int *vet2, float M[DIM][DIM]) {
    char *str_aus;
    str_aus = str;
    printf("%c ", *str_aus+1);
    int *vet_aus;
    vet_aus = vet;
    printf("%d ", *(vet_aus+1));
    vet_aus = vet2;
    printf("%d ", *(vet_aus+1));
    float *m_aus;
    m_aus = M[0];
    printf("%f", *(m_aus+10));
}

float matrixmaxDiag(float M[DIM][DIM], int n) {
    int start = 1;
    float media_max = 0;
    for(int j = 0; j < n; j++) {
        int i = 0;
        int j_aus = j;
        float media = 0;
        int cont = 0;
        while(j_aus < n && i < n) {
            media += M[i][j_aus];
            cont++;
            i++;
            j_aus++;
        }
        if(start = 1 || media_max < media/cont) {
            media_max = media/cont;
            start = 0;
        }
    }

    for(int i = 1; i < n; i++) {
        int j = 0;
        int i_aus = i;
        float media = 0;
        int cont = 0;
        while(i_aus < n && j < n) {
            media += M[i_aus][j];
            cont++;
            i_aus++;
            j++;
        }
        if(media_max < media/cont) {
            media_max = media/cont;
        }
    }
    return media_max;
}


int main(int argsc, char args[]) {
    float M[5][5] = {{1,2,3,4,5}, {2,2,2,2,-2}, {1.1, 2.2, 3.3, -4.4, 5.5}, {2.2, 2.2, -3.2, 4.2, 4.2}, {1.8, -2.3, 3.1, 4.9, 5.0}};
    char str[50] = "abcd";
    int vet[4] = {1,3,1,1};
    test(str, &vet[0], vet, M);
    //printf("%f", matrixmaxDiag(M, 5));
}