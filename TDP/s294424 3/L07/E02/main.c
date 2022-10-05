#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int n_scambi;
    int n_iterazioni_ciclo_esterno;
    int n_iterazioni_ciclo_interno;
    int n_iterazioni;
} dettagli;


void leggiVettore(FILE* finput, int vettore[], int n);
int copiaVettore(int originale[], int copia[], int N);
void selectionSort(int A[], int N, dettagli *dettaglio);
void insertionSort(int A[], int N, dettagli *dettaglio);
void shellSort(int A[], int N, dettagli *dettaglio);

int main(void) {
    FILE *finput;
    if((finput = fopen("sort.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file sort.txt");
        return 1;
    }

    int aus;
    const int nr = fscanf(finput, "%d", &aus) * aus;
    for(int i = 0; i < nr; i++) {
        dettagli dettaglio[3];
        const int N = fscanf(finput, "%d", &aus) * aus;
        int vet[N];
        leggiVettore(finput, vet, N);
        
        int A[N];
        copiaVettore(vet, A, N);
        selectionSort(A, N, &dettaglio[0]);
        copiaVettore(vet, A, N);
        insertionSort(A, N, &dettaglio[0]);
        copiaVettore(vet, A, N);
        shellSort(A, N, &dettaglio[0]);
    }
}

void leggiVettore(FILE* finput, int vettore[], int n) {
    printf("Vettore: [ ");
    for(int i = 0; i < n; i++) {
        fscanf(finput, "%d", &vettore[i]);
        printf("%d ", vettore[i]);
    }
    printf("]\n");
}

int copiaVettore(int originale[], int copia[], int N) {
    for(int i = 0; i < N; i++) {
        copia[i] = originale[i];
    }
}

void selectionSort(int A[], int N, dettagli *dettaglio) {
    dettaglio->n_iterazioni_ciclo_esterno = 0;
    dettaglio->n_iterazioni_ciclo_interno = 0;
    dettaglio->n_scambi = 0;
    int i, j, l = 0, r = N - 1, min;
    int temp;
    for (i = l; i < r; i++)
    {
        dettaglio->n_iterazioni_ciclo_esterno++;
        min = i;
        for (j = i + 1; j <= r; j++){
            dettaglio->n_iterazioni_ciclo_interno++;
            if (A[j] < A[min])
                min = j;
        }
        if (min != i)
        {
            dettaglio->n_scambi++;
            temp = A[i];
            A[i] = A[min];
            A[min] = temp;
        }
    }
    dettaglio->n_iterazioni = dettaglio->n_iterazioni_ciclo_esterno + dettaglio->n_iterazioni_ciclo_interno;
    printf("Selection Sort:\n\tN_iterazioni: %d\n\tN_iterazioni_ciclo_esterno: %d\n\tN_iterazioni_ciclo_interno: %d\n\tN_scambi: %d\n", dettaglio->n_iterazioni, dettaglio->n_iterazioni_ciclo_esterno, dettaglio->n_iterazioni_ciclo_interno, dettaglio->n_scambi);
}

void insertionSort(int A[], int N, dettagli *dettaglio)
{
    dettaglio->n_iterazioni_ciclo_esterno = 0;
    dettaglio->n_iterazioni_ciclo_interno = 0;
    dettaglio->n_scambi = 0;
    int i, j, l = 0, r = N - 1, x;
    for (i = l + 1; i <= r; i++)
    {
        dettaglio->n_iterazioni_ciclo_esterno++;
        x = A[i];
        j = i - 1;
        while (j >= l && x < A[j])
        {
            dettaglio->n_iterazioni_ciclo_interno++;
            dettaglio->n_scambi++;
            A[j + 1] = A[j];
            j--;
        }
        dettaglio->n_scambi++;
        A[j + 1] = x;
    }
    dettaglio->n_iterazioni = dettaglio->n_iterazioni_ciclo_esterno + dettaglio->n_iterazioni_ciclo_interno;
    printf("Inserction Sort:\n\tN_iterazioni: %d\n\tN_iterazioni_ciclo_esterno: %d\n\tN_iterazioni_ciclo_interno: %d\n\tN_scambi: %d\n", dettaglio->n_iterazioni, dettaglio->n_iterazioni_ciclo_esterno, dettaglio->n_iterazioni_ciclo_interno, dettaglio->n_scambi);
}

void shellSort(int A[], int N, dettagli *dettaglio)
{
    dettaglio->n_iterazioni_ciclo_esterno = 0;
    dettaglio->n_iterazioni_ciclo_interno = 0;
    dettaglio->n_scambi = 0;
    int i, j, x, l = 0, r = N - 1, h = 1;
    while (h < N / 3)
        h = 3 * h + 1;
    while (h >= 1)
    {
        for (i = l + h; i <= r; i++)
        { 
            dettaglio->n_iterazioni_ciclo_esterno++;
            j = i;
            x = A[i];
            while (j >= l + h && x < A[j - h])
            {
                dettaglio->n_iterazioni_ciclo_interno++;
                dettaglio->n_scambi++;
                A[j] = A[j - h];
                j -= h;
            }
            dettaglio->n_scambi++;
            A[j] = x;
        }
        h = h / 3;
    }
    dettaglio->n_iterazioni = dettaglio->n_iterazioni_ciclo_esterno + dettaglio->n_iterazioni_ciclo_interno;
    printf("Shell Sort:\n\tN_iterazioni: %d\n\tN_iterazioni_ciclo_esterno: %d\n\tN_iterazioni_ciclo_interno: %d\n\tN_scambi: %d\n", dettaglio->n_iterazioni, dettaglio->n_iterazioni_ciclo_esterno, dettaglio->n_iterazioni_ciclo_interno, dettaglio->n_scambi);
}