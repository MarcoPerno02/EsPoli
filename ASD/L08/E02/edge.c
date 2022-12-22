#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edge.h"
#include <math.h>
#include "st.h"

void addVertex(VertexArray vertexArray, char * vertex) {
    int i;
    for(i = 0; i < vertexArray->N && strcmp(vertexArray->vertices[i], vertex) != 0; i++) {

    }
    if(i == vertexArray->N) {
        if(i == vertexArray->M) {
            vertexArray->M *= 2;
            vertexArray->vertices = realloc(vertexArray->vertices, (vertexArray->M)*sizeof(char **));
        }
        vertexArray->vertices[i] = malloc(sizeof(char) * 31);
        strcpy(vertexArray->vertices[i], vertex);
        vertexArray->N += 1;
    }
}

int min(int a, int b) {
    if(a<b)
        return a;
    else 
        return b;
}

void Merge(char * A[], char * B[], int l, int q, int r)
{
    int i, j, k;
    i = l;
    j = q + 1;
    for (k = l; k <= r; k++)
        if (i > q)
            B[k] = A[j++];
        else if (j > r)
            B[k] = A[i++];
        else if (strcmp(A[i], A[j]) < 0 || strcmp(A[i], A[j]) == 0)
            B[k] = A[i++];
        else
            B[k] = A[j++];
    for (k = l; k <= r; k++)
        A[k] = B[k];
    return;
}

void BottomUpMergeSort(char * A[], int N) {
    char ** B = (char **) malloc(sizeof(char * ) * N);
    if(B == NULL) exit(-1);
    int i, q, m, l = 0, r = N - 1;
    for (m = 1; m <= r - l; m = m + m)
        for (i = l; i <= r - m; i += m + m)
        {
            q = i + m - 1;
            Merge(A, B, i, q, min(i + m + m - 1, r));
        }
    free(B);
}

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
    int dim = 2;
    Edge edges = malloc(sizeof(struct edge) * dim);
    int i = 0;
    char v_name[30+1];
    char v_subnet[30+1];
    char w_name[30+1];
    char w_subnet[30+1];
    int weight;
    VertexArray vertexArray = malloc(sizeof(struct vertexArray_s));
    vertexArray->M = 1;
    vertexArray->N = 0;
    vertexArray->vertices = malloc(sizeof(char *));
    while(fscanf(fin, "%s %s %s %s %d", v_name, v_subnet, w_name, w_subnet, &(weight)) != EOF) {
        addVertex(vertexArray, v_name);
        addVertex(vertexArray, w_name);
        Edge edge_to_add = EDGEcreate(-1, v_name, v_subnet, -1, w_name, w_subnet, weight);

        if(i == dim) {
            dim *= 2;
            edges = realloc(edges, sizeof(struct edge) * dim);
        }
        edges[i] = *edge_to_add;
        i++;
    }
    BottomUpMergeSort(vertexArray->vertices, vertexArray->N);
    for(int i = 0; i < vertexArray->N; i++) {
        STInsert(st, vertexArray->vertices[i]);
    }
    for(int i = 0; i < dim; i++) {
        edges[i].v = STSearchByLabel(st, edges[i].v_name);
        edges[i].w = STSearchByLabel(st, edges[i].w_name);
    }
    EdgeArray edgesArray = malloc(sizeof(struct edgeArray));
    edgesArray->edges = edges;
    edgesArray->N = i;
    edgesArray->M = dim;
    for(int i = 0; i < vertexArray->N; i++) {
        free(vertexArray->vertices[i]);
    }
    free(vertexArray);
    return edgesArray;
}


void EDGEPrintEdges(EdgeArray edgesArray) {
    for(int i = 0; i < edgesArray->N; i++) {
        printf("%d %s %s %d %s %s %d\n", edgesArray->edges[i].v, edgesArray->edges[i].v_name, edgesArray->edges[i].v_subnet, edgesArray->edges[i].w, edgesArray->edges[i].w_name, edgesArray->edges[i].w_subnet, edgesArray->edges[i].weight);
    }
}

void EDGEFree(EdgeArray edgesArray) {
    free(edgesArray->edges);
    free(edgesArray);
}

