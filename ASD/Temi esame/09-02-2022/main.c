#include <stdio.h>
#include <stdlib.h>
#include "graph/graph.h"

int main() {
    FILE * fin;
    fin = fopen("griglia.txt", "r");
    Graph G = GRAPHLoad(fin);
    fclose(fin);
    fin = fopen("proposta.txt", "r");
    GeneraSol(G);
    fclose(fin);
    GRAPHFree(G);
}