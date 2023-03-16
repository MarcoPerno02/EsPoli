#ifndef GRAPH_H_DEFINED
#define GRAPH_H_DEFINED
#include <stdio.h>
#include <stdlib.h>

typedef struct graph_s * Graph;

Graph GRAPHInit(FILE * fin);
Graph GRAPHFree(Graph G);
void GRAPHFunz1(Graph G);
void GRAPHFunz2(Graph G);
#endif