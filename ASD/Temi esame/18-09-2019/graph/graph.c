#include <stdio.h>
#include <stdlib.h>
#include "../graph/graph.h"

typedef struct {
    int obstacle;
    int value;
} Item;

typedef struct {
    int id;
    int r;
    int c;
} Resource;

struct graph_s {
    int NR;
    int NC;
    int Z;
    int k;
    Item ** madj;
};

Graph GRAPHInit(int NR, int NC) {
    Graph G = malloc(sizeof(struct graph_s));
    G->NR = NR;
    G->NC = NC;
    G->madj = malloc(sizeof(Item *) * NR);
    for(int i = 0; i < NR; i++) {
        G->madj[i] = malloc(sizeof(Item) * NC);
        for(int j = 0; j < NC; j++) {
            Item tmp;
            tmp.obstacle = 0;
            tmp.value = 0;
            G->madj[i][j] = tmp;
        }
    }
    return G;
}

Graph GRAPHLoad(FILE * fin) {
    int NR, NC;
    fscanf(fin, "%d %d", &NR, &NC);
    Graph G = GRAPHInit(NR, NC);
    int r, c;
    while(fscanf(fin, "%d %d", &r, &c) != EOF) {
        G->madj[r][c].obstacle = 1;
    }
    return G;
}

Graph GRAPHCopy(Graph G) {
    Graph G_to_return = GRAPHInit(G->NR, G->NC);
    G_to_return->k = G->k;
    G_to_return->Z = G->Z;
    for(int i = 0; i < G->NR; i++) {
        for(int j = 0; j < G->NC; j++) {
            G_to_return->madj[i][j] = G->madj[i][j];
        }
    }
    return G_to_return;
}

void dispRip(int * source, int dim_source, int * sol, int k, int pos, Resource * neighbors, int * cont, int r, int c, int val) {
    if(pos == 2) {
        int sum = 0;
        for(int i = 0; i < k; i++) {
            if(sol[i] < 0) {
                sum += 0-sol[i];
            }
            else {
                sum += sol[i];
            }
            
        }
        if(sum >= 0-k && sum <= k) {
            for(int i = 0; i < k; i++) {
                printf("%d ", sol[i]);
            }
            printf("\n");
            Resource tmp;
            tmp.r = r + sol[0];
            tmp.c = c + sol[1];
            tmp.id = val;
            neighbors[*cont] = tmp;
            *cont += 1;
        }
    }
    else {
        for(int i = 0; i < dim_source; i++) {
            sol[pos] = source[i];
            dispRip(source, dim_source, sol, k, pos + 1, neighbors, cont, r, c, val);
        }
    }
}

Resource * generateNeighbors(int k, int r, int c, int val) {
    int dim = 0;
    dim = k*2+1;
    int cont = dim;
    while(cont > 0) {
        cont = cont - 2;
        dim += (cont*2);
    }
    Resource * neighbors = malloc(sizeof(int) * dim); 
    int source[k*2+1];
    for(int i = 0-k; i <= k; i++) {
        source[i+k] = i; 
    }
    int sol[k];
    int cont_vett = 0;
    dispRip(source, k*2+1, sol, k, 0, neighbors, &cont_vett, r, c, val);

}

void GRAPHValidateSolution(Graph G, Resource * resources) {
    for(int i = 0; i < G->Z; i++) {
        if(G->madj[resources[i].r][resources[i].c].value == resources[i].id) {
            int cont = 0;
            Resource * neighbors = generateNeighbors(G->k, resources[i].r, resources[i].c, resources[i].id);
        }
    }
}

void GRAPHReadSolution(Graph G, FILE * fin) {
    fscanf(fin, "%d %d", &(G->k), &(G->Z));
    Resource resources[G->Z];
    for(int i = 0; i < G->Z; i++) {
        Resource tmp;
        fscanf(fin, "%d %d", &(tmp.r), &(tmp.c));
        tmp.id = i+1;
        resources[i] = tmp;
    }

    Graph G_to_test = GRAPHCopy(G);
    int valid = 1;
    for(int i = 0; i < G->NR && valid == 1; i++) {
        for(int j = 0; j < G->NC && valid == 1; j++) {
            int val;
            fscanf(fin, "%d", &val);
            if(G_to_test->madj[i][j].obstacle == 1 && val != 0) {
                valid = 1;//////////////////////////////////////////////////////0
            }
            else {
                G_to_test->madj[i][j].value = val;
            }
        }
    }
    if(valid == 0 && 1!=1) {
        printf("Soluzione proposta non valida\n");
        return;
    }
    GRAPHValidateSolution(G_to_test, resources);
}


void GRAPHFree(Graph G) {
    for(int i = 0; i < G->NR; i++) {
        free(G->madj[i]);
    }
    free(G->madj);
    free(G);
}