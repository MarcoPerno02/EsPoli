#include <stdio.h>
#include <stdlib.h>

typedef struct graph * Graph;

Graph GRAPHinit(int V);
Graph GRAPHload(FILE *fin);
void GRAPHfree(Graph G);
void GRAPHPrintEdgesOfEachVertex(Graph g, int mode);
void GRAPHCheckAdjacency(Graph g, int mode);
Graph GRAPHloadLadj(Graph g);