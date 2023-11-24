#include <stdio.h>
#include <stdlib.h>
#include "graph/graph.h"

int main(char ** argv, int argc) {
    FILE * fin;
    fin = fopen("input1.txt", "r");
    Graph G = GRAPHLoad(fin);
    fclose(fin);
    fin = fopen("input2.txt", "r");
    commonPath(G, fin);
    char name1[21] = "A0";
    char name2[21] = "fF";
    int k = 6, p = 7;
    /*printf("Inserisci nome vertice1: ");
    scanf("%s", name1);
    printf("Inserisci nome vertice2: ");
    scanf("%s", name2);
    printf("Inserisci k: ");
    scanf("%d", &k);
    printf("Inserisci p: ");
    scanf("%d", &p);*/
    funz2(G, name1, name2, k, p);
    GRAPHFree(G);
}