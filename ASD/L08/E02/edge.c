#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edge.h"
#include "st.h"

Edge EDGEcreate(int v, char * v_name, char * v_subnet, int w, char * w_name, char * w_subnet, int weight) {
    Edge edge_to_add = malloc(sizeof(struct edge));
    edge_to_add->v = v;
    strcpy(edge_to_add->v_name, v_name);
    strcpy(edge_to_add->v_subnet, v_subnet);
    edge_to_add->w = w;
    strcpy(edge_to_add->w_name, w_name);
    strcpy(edge_to_add->w_subnet, w_subnet);
    edge_to_add->weight = weight;
    return edge_to_add;
}

EdgeArray EDGEReadEdges(FILE *fin, ST st) {
    int max_vertex = -1;
    int dim = 2;
    Edge edges = malloc(sizeof(struct edge) * dim);
    int i = 0;
    char v_name[30+1];
    char v_subnet[30+1];
    char w_name[30+1];
    char w_subnet[30+1];
    int weight;
    while(fscanf(fin, "%s %s %s %s %d", v_name, v_subnet, w_name, w_subnet, &(weight)) != EOF) {
        int v = STSearch(st, v_name);
        if(v > max_vertex)
            max_vertex = v;
        int w = STSearch(st, w_name);
        if(w > max_vertex)
            max_vertex = w;

        Edge edge_to_add = EDGEcreate(v, v_name, v_subnet, w, w_name, w_subnet, weight);

        if(i == dim) {
            dim *= 2;
            edges = realloc(edges, sizeof(struct edge) * dim);
        }
        edges[i] = *edge_to_add;
        i++;
    }
    EdgeArray edgesArray = malloc(sizeof(struct edgeArray));
    edgesArray->edges = edges;
    edgesArray->N = i;
    edgesArray->N_vertex = max_vertex;
    return edgesArray;
}


void EDGEPrintEdges(EdgeArray edgesArray) {
    for(int i = 0; i < edgesArray->N; i++) {
        printf("%d %s %s %d %s %s %d\n", edgesArray->edges[i].v, edgesArray->edges[i].v_name, edgesArray->edges[i].v_subnet, edgesArray->edges[i].w, edgesArray->edges[i].w_name, edgesArray->edges[i].w_subnet, edgesArray->edges[i].weight);
    }
}

int EDGECountEdges(Edge edges) {

}