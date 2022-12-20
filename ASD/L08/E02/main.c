#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


int main() {
    FILE *fin;
    fin = fopen("grafo.txt", "r");
    if(fin == NULL) exit(-1);
    Graph g = GRAPHload(fin);
    fclose(fin);
}