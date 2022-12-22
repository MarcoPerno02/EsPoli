#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


int main() {
    FILE *fin;
    fin = fopen("grafo.txt", "r");
    if(fin == NULL) exit(-1);
    Graph g = GRAPHload(fin);
    GRAPHPrintEdgesOfEachVertex(g, 0);
    GRAPHCheckAdjacency(g, 0);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    char ch;
    printf("Eseguire funzioni con lista adiacenza?(Y/N)");
    scanf("%c", &ch);
    if(ch == 'Y') {
        GRAPHloadLadj(g);
        GRAPHPrintEdgesOfEachVertex(g, 1);
        GRAPHCheckAdjacency(g, 1);
    }
    GRAPHfree(g);
    fclose(fin);
}