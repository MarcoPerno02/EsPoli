#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "st.h"
#include "edge.h"

struct graph {
    int V;
    int E;
    int **madj;
    ST tab;
};

static int **MATRIXint(int r, int c, int val)
{
    int i, j;
    int **t = malloc(r * sizeof(int *));
    for (i = 0; i < r; i++)
        t[i] = malloc(c * sizeof(int));
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            t[i][j] = val;
    return t;
}

Graph GRAPHinit(int V)
{
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->E = 0;
    G->madj = MATRIXint(V, V, 0);
    G->tab = STinit(V);
    return G;
}

void GRAPHinsertE(Graph G, Edge e) {
    //insertE(G, e);
}

Graph GRAPHload(FILE *fin) {
    ST st = STinit();
    EdgeArray edgesArray = EDGEReadEdges(fin, st);
    EDGEPrintEdges(edgesArray);
    Graph g = GRAPHinit(edgesArray->N_vertex);
    for(int i = 0; i < edgesArray->N; i++) {

    }
}