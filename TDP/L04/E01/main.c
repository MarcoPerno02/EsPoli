#include <stdio.h>
#define INPUT "input.txt"
#define DIM 30
//0 0 0 1 1 0 1 0 10 20 30 0 40 50 60 0 80 40 0 30 60 50
void sottoSequenze(int V[], int N);

int main(void)
{
    FILE *finput;
    int vet[DIM];
    if((finput = fopen(INPUT , "r")) == NULL) {
        printf("Errore nell'aprire il file %s\n", INPUT);
        return 1;
    }
    int len_vet = 0;
    while(len_vet < DIM && fscanf(finput, " %d", &vet[len_vet]) != -1) {
        len_vet++;
    }
    sottoSequenze(vet, len_vet);

    fclose(finput);
    return 0;
}

void sottoSequenze(int V[], int N) {
    int posMax[DIM];
    int elemMax = 0;
    int contMax = -1;
    int i = 0;
    int j = 0;
    while (i < N)
    {
        //printf("%d ", V[i]);
        if(V[i] != 0) {
            j++;
        }
        if(V[i] == 0 || i == N-1) {
            if(j > contMax) {
                elemMax = 0;
                if(i == N-1 && V[i] != 0)
                    posMax[elemMax] = i-j+1;
                else
                    posMax[elemMax] = i-j;
                contMax = j;
                j = 0;
            }
            else if(j == contMax) {
                elemMax++;
                if(i != N-1 && V[i] != 0)
                    posMax[elemMax] = i-j+1;
                else
                    posMax[elemMax] = i-j;
                j = 0;
            }
            else {
                j = 0;
            }
        }
        i++;      
    }
    for(i = 0; i < elemMax + 1; i++) {
        printf("[ ");
        for(j = 0; j < contMax; j++) {
            printf("%d ", V[posMax[i] + j]);
        }
        printf("]\n");
    }
}