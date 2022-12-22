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

Graph GRAPHload(FILE *fin) {
    ST st = STinit();
    EdgeArray edgesArray = EDGEReadEdges(fin, st);
    //EDGEPrintEdges(edgesArray);
    Graph g = GRAPHinit(STVertexCount(st));
    g->tab = st;
    for(int i = 0; i < edgesArray->N; i++) {
        GRAPHinsertE(g, &(edgesArray->edges[i]));
    }
    GRAPHPrintGraph(g);
    EDGEFree(edgesArray);
    return g;
}

void GRAPHPrintEdgesOfEachVertex(Graph g) {
    for(int i = 0; i < STVertexCount(g->tab); i++) {
        char * aa;
        printf("Archi per vertice %s:\n", STSearchById(g->tab, i));
        for(int j = 0; j < g->V; j++) {
            if(g->madj[i][j] != 0) {
                printf("\t- %s <--> %s. Peso: %d\n", STSearchById(g->tab, i), STSearchById(g->tab, j), g->madj[i][j]);
            }
        }
    }
}

void GRAPHCheckAdjacency(Graph g) {
    STPrintst(g->tab);
    char * name;
    int vertices[3];
    for(int i = 0; i < 3; i++) {
        printf("Inserisci vertice %d: ", i);
        scanf("%s", name);
        vertices[i] = STSearchByLabel(g->tab, name);
    }
    if(g->madj[vertices[0]][vertices[1]] != 0 && g->madj[vertices[0]][vertices[2]] != 0) {
        printf("Vertici connessi dagli archi:\n\t- %s <--> %s.\n\t- %s <--> %s\n", STSearchById(g->tab, vertices[0]), STSearchById(g->tab, vertices[1]), STSearchById(g->tab, vertices[0]), STSearchById(g->tab, vertices[2]));
    }
    else if(g->madj[vertices[1]][vertices[0]] != 0 && g->madj[vertices[1]][vertices[2]] != 0) {
        printf("Vertici connessi dagli archi:\n\t- %s <--> %s.\n\t- %s <--> %s\n", STSearchById(g->tab, vertices[1]), STSearchById(g->tab, vertices[0]), STSearchById(g->tab, vertices[1]), STSearchById(g->tab, vertices[2]));
    }
    else if(g->madj[vertices[2]][vertices[0]] != 0 && g->madj[vertices[2]][vertices[1]] != 0) {
        printf("Vertici connessi dagli archi:\n\t- %s <--> %s.\n\t- %s <--> %s\n", STSearchById(g->tab, vertices[2]), STSearchById(g->tab, vertices[0]), STSearchById(g->tab, vertices[2]), STSearchById(g->tab, vertices[1]));
    }
    else {
        printf("I vertici non sono connessi\n");
    }
}


