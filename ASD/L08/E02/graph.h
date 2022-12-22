#include <stdio.h>
#include <stdlib.h>

typedef struct graph * Graph;

Graph GRAPHinit(int V);
Graph GRAPHload(FILE *fin);
void GRAPHfree(Graph G);
void GRAPHPrintEdgesOfEachVertex(Graph g);
void GRAPHCheckAdjacency(Graph g);
