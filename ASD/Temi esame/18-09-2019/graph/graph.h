#ifndef GRAPH_H_DEFINED
#define GRAPH_H_DEFINED
#include <stdio.h>
#include <stdlib.h>

typedef struct graph_s * Graph;

Graph GRAPHLoad(FILE * fin);
void GRAPHFree(Graph G);
void GRAPHReadSolution(Graph G, FILE * fin);

#endif