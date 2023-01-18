#include <stdio.h>
#include <stdlib.h>
#include "graph/graph.h"

int main() {
    FILE *fin;
    fin = fopen("grafo4.txt", "r");
    if(fin == NULL) exit(-1);
    Graph g = GRAPHLoad(fin);
    fclose(fin);
    Edge ** edges_array;
    int N, N_edges_deleted;
    GRAPHReturnPossibleDag(g, &edges_array, &N, &N_edges_deleted);
    if(edges_array != NULL) {
        int id = GRAPHPrintDagThatDontHaveMaxWeight(g, edges_array, N, N_edges_deleted);
        //printf("%d\n", id);
        GRAPHspBF(g, edges_array[id], N_edges_deleted);
    }
    else {
        printf("Il grafo originale era già un dag\n");
    }
    GRAPHFreeEdgesArray(edges_array, N);
    GRAPHfree(g);
}