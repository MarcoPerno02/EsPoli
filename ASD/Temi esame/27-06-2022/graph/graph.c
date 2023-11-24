#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../graph/graph.h"

typedef struct node_s * link;
struct node_s {
    int vertex;
    link next;
};

struct graph_s {
    int N_edges;
    int N_ladj;
    link z;
    link * ladj;
};

Graph GRAPHInit() {
    Graph G = malloc(sizeof(struct graph_s));
    G->z = malloc(sizeof(struct node_s));
    G->z->next = NULL;
    G->z->vertex = -1;
    G->N_edges = 0;
    G->ladj = NULL;
    G->N_ladj = 0;
}


Graph GRAPHLoad(FILE * fin) {
    Graph G = GRAPHInit();
    fscanf(fin, "%d", &(G->N_ladj));
    G->ladj = malloc(sizeof(link) * G->N_ladj);
    for(int i = 0; i < G->N_ladj; i++) {
        G->ladj[i] = G->z;
    }
    int u, v;
    while(fscanf(fin, "%d %d", &u, &v) != EOF) {
        link ex_head = G->ladj[u];
        link new_head = malloc(sizeof(struct node_s));
        new_head->vertex = v;
        new_head->next = ex_head;
        G->ladj[u] = new_head;

        ex_head = G->ladj[v];
        new_head = malloc(sizeof(struct node_s));
        new_head->vertex = u;
        new_head->next = ex_head;
        G->ladj[v] = new_head;

        G->N_edges+=1;
    }
    for(int i = 0; i < G->N_ladj; i++) {
        printf("Vertice %d connesso a: ", i);
        for(link x = G->ladj[i]; x->next != NULL; x = x->next) {
            printf("%d, ", x->vertex);
        }
        printf("\n");
    }
    return G;
}

void GRAPHFree(Graph G) {
    for(int i = 0; i < G->N_ladj; i++) {
        for(link x = G->ladj[i]; x->next != NULL; ) {
            link tmp = x->next;
            free(x);
            x = tmp;
        }
    }
    free(G->z);
    free(G);
}

int checkPresenceLadj(int el, link list) {
    for(link x = list; x->next != NULL; x = x->next) {
        if(x->vertex == el)
            return 1;
    }
    return 0;
}

int checkpresenceInSubset(int el, int * vet, int N) {
    for(int  i = 0; i < N; i++) {
        if(el == vet[i]) 
            return 1;
    }
    return 0;
}

int verifySolution(int ** domain_set, int * dim_domain_set, int k, Graph G) {
    for(int i = 0; i < k; i++) {
        for(int j = 0; j < G->N_ladj; j++) {
            if(checkpresenceInSubset(j, domain_set[i], dim_domain_set[i]) == 0){
                int validate = 0;
                for(int y = 0; y < dim_domain_set[i] && validate == 0; y++) {
                    if(checkPresenceLadj(j, G->ladj[domain_set[i][y]]) == 1)
                        validate = 1; 
                }
                if(validate == 0)
                    return -1;
            }
        }
    }
    return 1;
}

void ER(int * sol, int pos, int m, int k, int N, Graph G, int * exit) {
    if(pos == N) {
        if(m == k) {
            //Terminal case
            int dim_domain_set[k];
            int cont_domain_set[k];
            for(int i = 0; i < k; i++) {
                dim_domain_set[i] = 0;
                cont_domain_set[i] = 0;
            }
            for (int i=0; i<m; i++) {
                fprintf(stdout, "{ ");
                for (int j=0; j<N; j++) {
                    if (sol[j]==i) {
                        fprintf(stdout, "%d ", j);
                        dim_domain_set[i]++;
                    }
                }
                fprintf(stdout, "}  ");
            }
            fprintf(stdout, "\n");
            int * domain_set[k];
            for(int i = 0; i < k; i++) {
                domain_set[i] = malloc(sizeof(int) * dim_domain_set[i]);
            }
            for(int i = 0; i < N; i++) {
                domain_set[sol[i]][cont_domain_set[sol[i]]] = i;
                cont_domain_set[sol[i]]++;
            }
            if(verifySolution(domain_set, dim_domain_set, k, G) == 1) {
                printf("Trovato\n");
                *exit = 1;
            }

        }
    }
    else {
        for(int i = 0; i < m && *exit == 0; i++) {
            sol[pos] = i;
            ER(sol, pos + 1, m , k, N, G, exit);
        }
        sol[pos] = m;
        ER(sol, pos + 1, m + 1, k, N, G, exit);
    }
}


void powersetER(Graph G) {
    int sol[G->N_ladj];
    int exit = 0;
    for(int i = 6; i > 0 && exit == 0; i--) {
        ER(sol, 0, 0, i, G->N_ladj, G, &exit);
        printf("");
    }
    
}