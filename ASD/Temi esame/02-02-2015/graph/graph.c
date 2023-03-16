#include <stdio.h>
#include <stdlib.h>
#include "../graph/graph.h"
#include <string.h>
#include "../st/st.h"

typedef struct {
    int u;
    int v;
} Edge;

typedef struct node_s * link;
struct node_s {
    int vertex;
    link next;
};

struct graph_s {
    ST st;
    Edge * edges;
    int N_edges;
    int Max_N_edges;
    link * ladj;
    link z;
};

Edge EDGEcreate(int u, int v) {
    Edge edge;
    edge.u = u;
    edge.v = v;
    return edge;
}

Graph GRAPHInit() {
    Graph G = malloc(sizeof(struct graph_s));
    G->z = malloc(sizeof(struct node_s));
    G->z->next = NULL;
    G->z->vertex = -1;
    G->Max_N_edges = 1;
    G->edges = malloc(sizeof(Edge)* G->Max_N_edges);
    G->N_edges = 0;
    G->st = STInit(1);
    G->ladj = NULL;
}

Graph GRAPHLoad(FILE * fin) {
    Graph G = GRAPHInit();
    Item_st item1;
    Item_st item2;
    while(fscanf(fin, "%s %s", item1.key.name, item2.key.name) != EOF) {
        STInsert(G->st, item1);
        STInsert(G->st, item2);
        int u = STsearch(G->st, item1.key);
        int v = STsearch(G->st, item2.key);
        Edge e = EDGEcreate(u, v);
        if(G->N_edges == G->Max_N_edges) {
            G->Max_N_edges *= 2;
            G->edges = realloc(G->edges, sizeof(Edge) * G->Max_N_edges);
        }
        G->edges[G->N_edges] = e;
        G->N_edges += 1;
    }
    G->ladj = malloc(sizeof(link) * STcount(G->st));
    for(int i = 0; i < STcount(G->st); i++) {
        G->ladj[i] = G->z;
    }
    for(int i = 0; i < G->N_edges; i++) {
        link ex_head = G->ladj[G->edges[i].u];
        link new_head = malloc(sizeof(struct node_s));
        new_head->vertex = G->edges[i].v;
        new_head->next = ex_head;
        G->ladj[G->edges[i].u] = new_head;

        ex_head = G->ladj[G->edges[i].v];
        new_head = malloc(sizeof(struct node_s));
        new_head->vertex = G->edges[i].u;
        new_head->next = ex_head;
        G->ladj[G->edges[i].v] = new_head;
    }
    for(int i = 0; i < STcount(G->st); i++) { 
        Key_st tmp = STsearchByIndex(G->st, i);
        printf("%s: ", tmp.name);
        for(link x = G->ladj[i]; x->next != NULL; ) {
            link tmp = x->next;
            printf("%s, ", STsearchByIndex(G->st, x->vertex));
            x = tmp;
        }
        printf("\n");
    }
    //printf("aa");
    return G;
}

int verifySolution(Graph G, char *** solution, int N_partition, int * dim_sub_array) {
    int valid = 1;
    int found = 0;
    int i;
    for(i = 0; i < STcount(G->st) && valid == 1; i++) {// Iterate on friend
        for(int j = 0; j < N_partition && valid == 1; j++) {// iterate on partiton
            for(int k = 0; k < dim_sub_array[j] && valid == 1; k++) { // Search friend in partiton
                Key_st tmp;
                strcpy(tmp.name, solution[j][k]);
                if(STsearch(G->st, tmp) == i) {// friend found
                    found = 1;
                    int x;
                    for(x = 0; x < dim_sub_array[j]  && valid == 1; x++) {
                        if(strcmp(solution[j][x], solution[j][k]) != 0) {
                            for(link node = G->ladj[i]; node->next != NULL && valid == 1; node = node->next) {
                                Key_st tmp2;
                                strcpy(tmp2.name, solution[j][x]);
                                if(STsearch(G->st, tmp2) == node->vertex) {
                                    valid = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
        if(found == 1) {
            found = 0;
        }
        else {
            valid = 0;
        }
    }
    if(valid == 1) {
        printf("Sol corretta");
        return 1;
    }
    else {
        printf("Sol non corretta");
        return 0;
    }
}

void readSolution(Graph G, FILE * fin) {
    int row;
    fscanf(fin, "%d", &row);
    char ** solution[row];
    int dim_sub_array[row];
    for(int i = 0; i < row; i++) {
        int N; 
        fscanf(fin, "%d", &N);
        char ** tmp = malloc(sizeof(char *) * N);
        dim_sub_array[i] = N;
        for(int j = 0; j < N; j++) {
            tmp[j] = malloc(sizeof(char) * 16);
            fscanf(fin, "%s", tmp[j]);
            //printf("%s", tmp[j]);
        }
        solution[i] = tmp;
    }
    int ris = verifySolution(G, solution, row, dim_sub_array);
}

void ER(int * sol, int pos, int n, int k, int m, Graph G, int * exit) {
    if(pos == n) {
        if(m == k) {
            int row = k;
            char ** solution[row];
            int dim_sub_array[k];
            for(int i = 0; i < k; i++) {
                dim_sub_array[i] = 0;
            }
            for (int i=0; i<m; i++) {
                char ** tmp = malloc(sizeof(char *) * n);
                int cont = 0;
                fprintf(stdout, "{ ");
                for (int j=0; j<n; j++) {
                    if (sol[j]==i) {
                        tmp[cont] = malloc(sizeof(char) * 16);
                        Key_st key = STsearchByIndex(G->st, j);
                        strcpy(tmp[cont], key.name);
                        fprintf(stdout, "%d %s, ", j, key.name);
                        dim_sub_array[i] += 1;
                        cont++;
                    }
                }
                solution[i] = tmp;
                fprintf(stdout, "}  ");
            }
            fprintf(stdout, "\n");
            if(verifySolution(G, solution, k, dim_sub_array) == 1) {
                *exit = 1;
            }
            for(int i = 0; i < m; i++) {
                for(int j = 0; j < dim_sub_array[i]; j++) {
                    free(solution[i][j]);
                }
                free(solution[i]);
            }
            int a = 2;
        }
    }
    else {
        for(int i = 0; i < m && *exit == 0; i++) {
            sol[pos] = i;
            ER(sol, pos + 1, n, k , m, G, exit);
        }
        sol[pos] = m;
        ER(sol, pos + 1, n, k, m+1, G, exit);
    }
}

void wrapperER(Graph G) {
    int * sol = malloc(STcount(G->st) * sizeof(int));
    int exit = 0;
    for(int k = 1; k <= STcount(G->st) && exit == 0; k++) {
        printf("Partizione da %d:\n", k);
        ER(sol, 0, STcount(G->st), k, 0, G, &exit);
    }
}


void GRAPHFree(Graph G) {
    for(int i = 0; i < STcount(G->st); i++) {
        for(link x = G->ladj[i]; x->next != NULL; ) {
            link tmp = x->next;
            free(x);
            x = tmp;
        }
    }
    free(G->edges);
    free(G->z);
    STFree(G->st);
    free(G);
}