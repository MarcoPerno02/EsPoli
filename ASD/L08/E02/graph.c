#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "st.h"
#include "edge.h"

struct graph {
    int V; // Number of vertex
    int E; // Number of edges
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
    return G;
}

void GRAPHfree(Graph G)
{
    int i;
    for (i = 0; i < G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    STfree(G->tab);
    free(G);
}

void GRAPHinsertE(Graph G, Edge e) {
    if (G->madj[e->v][e->w] == 0)
        G->E++;
    G->madj[e->v][e->w] = e->weight; 
    G->madj[e->w][e->v] = e->weight;
}

Graph GRAPHload(FILE *fin) {
    ST st = STinit();
    EdgeArray edgesArray = EDGEReadEdges(fin, st);
    //EDGEPrintEdges(edgesArray);
    Graph g = GRAPHinit(edgesArray->N_vertex);
    g->tab = st;
    for(int i = 0; i < edgesArray->N; i++) {
        GRAPHinsertE(g, &(edgesArray->edges[i]));
    }
    //GRAPHPrintGraph(g);
    return g;
}

void GRAPHPrintGraph(Graph g) {
    for(int i = 0; i < g->V; i++) {
        for(int j = 0; j < g->V; j++) {
            printf("_______");
        }
        printf("\n");
        for(int j = 0; j < g->V; j++) {
            if(g->madj[i][j] < 10)
                printf("|  %d  |", g->madj[i][j]);
            else 
                printf("| %d  |", g->madj[i][j]);
        }
        printf("\n");
    }
}
