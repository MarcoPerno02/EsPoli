#include <stdio.h>
#include <stdlib.h>
#include "graph/graph.h"

int main() {
    FILE * fin;
    fin = fopen("input.txt", "r");
    Graph G = GRAPHInit(fin);
    GRAPHFunz1(G);
    GRAPHFunz2(G);
    GRAPHFree(G);
    fclose(fin);
}
