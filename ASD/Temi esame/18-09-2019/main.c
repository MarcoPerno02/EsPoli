#include <stdio.h>
#include <stdlib.h>
#include "graph/graph.h"

int main() {
    FILE * fin;
    fin = fopen("mappa.txt", "r");
    Graph G = GRAPHLoad(fin);
    fclose(fin);
    fin = fopen("proposta.txt", "r");
    GRAPHReadSolution(G, fin);
    fclose(fin);
    GRAPHFree(G);
    
}