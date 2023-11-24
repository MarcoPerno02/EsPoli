#ifndef GRAPH_H_DEFINED
#define GRAPH_H_DEFINED
#include <stdio.h>
#include <stdlib.h>

typedef struct graph_s * Graph;

Graph GRAPHLoad(FILE * fin);
void GRAPHFree(Graph G);
void commonPath(Graph G, FILE * fin);
void funz2(Graph G, char * vertex1, char * vertex2, int k, int p);

#endif