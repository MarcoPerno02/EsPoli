#ifndef GRAPH_H_DEFINED
#define GRAPH_H_DEFINED
#include <stdio.h>
#include <stdlib.h>

typedef struct graph_s* Graph;
typedef struct edge Edge;

Graph GRAPHLoad(FILE *fin);
void GRAPHfree(Graph G);
void GRAPHReturnPossibleDag(Graph G, Edge  *** edges_array_to_return, int *N_dag_edges_array_to_return, int * N_edges_deleted);
int GRAPHPrintDagThatDontHaveMaxWeight(Graph G, Edge ** edges_array, int N, int N_edges_deleted);
void GRAPHspBF(Graph G_to_copy, Edge * edge_array, int N_edges_deleted);
void GRAPHFreeEdgesArray(Edge ** edges_array, int N);
#endif


