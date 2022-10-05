#include <stdio.h>
#include <stdlib.h>
#define NOME_FILE "numeri.txt"

void gestioneNum(int scartato, FILE *finput, int *num1, int *num2, int *num3, int *num_scartati, int *eof, int *max, int *min);
void trovaMax(int *max, int num);
void trovaMin(int *min, int num);

int main(void)
{
    FILE *finput;
    int num1, num2, num3, eof = 0, num_scartati = 0, max, min;
    if((finput = fopen(NOME_FILE , "r")) == NULL) {
        printf("Errore nell'aprire il file %s\n", NOME_FILE);
        return 1;
    }
    fscanf(finput, " %d", &num1);
    fscanf(finput, " %d", &num2);

    max = num1;
    min = num1;
    trovaMax(&max, num2);
    trovaMin(&min, num2);
    trovaMax(&max, num3);
    trovaMin(&min, num3);

    fscanf(finput, " %d", &num3);
    do {
        // Assumo che nel file ci siano almeno tre valori quindi non faccio il controllo se è gia stato letto eof
        if(num3 != num1 + num2 && num3 != num1 * num2 && num3 != num1 - num2 ) {
            if(num2 == 0) {
                gestioneNum(1, finput, &num1, &num2, &num3, &num_scartati, &eof, &max, &min);
            }
            else if (num3 != num1 / num2) {
                gestioneNum(1, finput, &num1, &num2, &num3, &num_scartati, &eof, &max, &min);
            }
            else {
                gestioneNum(0, finput, &num1, &num2, &num3, &num_scartati, &eof, &max, &min);
            }
        }
        else {
            gestioneNum(0, finput, &num1, &num2, &num3, &num_scartati, &eof, &max, &min);
        }
    } while(eof != -1);
    fclose(finput);
    printf("Num scartati: %d\n", num_scartati);
    printf("Max: %d ", max);
    printf("Min: %d", min);
    return 0;
}

void gestioneNum(int scartato, FILE *finput, int *num1, int *num2, int *num3, int *num_scartati, int *eof,  int *max, int *min) {
    // La funzione gestisce anche quando si arriva all'eof cambiando il valore della varaibile eof che verrà poi controllato dal do while
    if(scartato == 0) {
        trovaMax(max, *num3);
        trovaMin(min, *num3);
        *num1 = *num2;
        *num2 = *num3;
    }
    else {
        *num_scartati = *num_scartati + 1;
    }
    *eof = fscanf(finput, " %d", num3);
}

void trovaMax(int *max, int num) {
    if(num > *max)
        *max = num;
}

void trovaMin(int *min, int num) {
    if(num < *min)
        *min = num;
}