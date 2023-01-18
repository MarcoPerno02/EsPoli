#include <stdio.h>
#include <stdlib.h>
#include "graph/graph.h"

int main() {
    FILE *fin;
    fin = fopen("grafo1.txt", "r");
    if(fin == NULL) exit(-1);
    Graph g = GRAPHLoad(fin);
    fclose(fin);
    GRAPHReturnPossibleDag(g);
    GRAPHfree(g);



}