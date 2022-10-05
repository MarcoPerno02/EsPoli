#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    char id[5];
    float conto;
    int real;
} cliente;

void anlyseBill(FILE *fp, int *num) {
    cliente clienti[10];
    for(int i = 0; i < 10; i++) {
        char aus[5] = "C00";
        char num_aus[2];
        itoa(i, num_aus, 10);
        strcat(aus, num_aus);
        strcpy(clienti[i].id, aus);
        clienti[i].conto = 0;
        clienti[i].real = 0;
    }
    char id[5];
    float num_conto;
    while(fscanf(fp, "%s %f", id, &num_conto) != EOF) {
        int i = 0;
        while (strcmp(clienti[i].id, id) != 0)
        {
            i++;
        }
        clienti[i].conto += num_conto;
        clienti[i].real = 1;
    }
    *num = 0;
    int start = 1, max = 0, id_max = -1;
    for(int i = 0; i < 10; i++) {
        if(clienti[i].real == 1) {
            printf("Customer %s: %.2f\n", clienti[i].id, clienti[i].conto);
            (*num)++;
            if(start == 1 || clienti[i].conto > max) {
                max = clienti[i].conto;
                start = 0;
                id_max = i;
            }
        }
    } 
    printf("Customer highest debt: %s %.2f", clienti[id_max].id, clienti[id_max].conto);
}

int main() {
    FILE *fp;
    int num;
    fp = fopen("bills.txt", "r");
    if(fp == NULL)
        return -1;
    anlyseBill(fp, &num);
}