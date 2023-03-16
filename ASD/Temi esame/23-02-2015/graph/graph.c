#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../graph/graph.h"
#include "../st/st.h"

typedef struct {
    int u;
    int v;
    int wt;
} Edge;

typedef struct {
    int vertex;
    int new;
} Item;

typedef struct node_s * link;
struct node_s {
    int vertex;
    int wt;
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

Edge EDGEcreate(int u, int v, int wt) {
    Edge edge;
    edge.u = u;
    edge.v = v;
    edge.wt = wt;
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
    Item_st item1, item2;
    int wt;
    while(fscanf(fin, "%s %d %s", item1.key.name, &wt, item2.key.name) != EOF) {
        STInsert(G->st, item1);
        STInsert(G->st, item2);
        int u = STsearch(G->st, item1.key);
        int v = STsearch(G->st, item2.key);
        Edge e = EDGEcreate(u, v, wt);
        if(G->Max_N_edges == G->N_edges) {
            G->Max_N_edges *= 2;
            G->edges = realloc(G->edges, sizeof(Edge)* G->Max_N_edges);
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
        new_head->wt = G->edges[i].wt;
        new_head->next = ex_head;
        G->ladj[G->edges[i].u] = new_head;
    }
    return G;
}

void commonPath(Graph G, FILE * fin) {
    int N1;
    fscanf(fin, "%d", &N1);
    N1 += 1;
    int path1[N1];
    for(int i = 0; i < N1; i++) {
        Key_st tmp;
        fscanf(fin, "%s", tmp.name);
        path1[i] = STsearch(G->st, tmp);
    }
    int N2;
    fscanf(fin, "%d", &N2);
    N2 += 1;
    int path2[N2];
    for(int i = 0; i < N2; i++) {
        Key_st tmp;
        fscanf(fin, "%s", tmp.name);
        path2[i] = STsearch(G->st, tmp);
    }
    for(int i = 0; i < N1; i++) {
        int exit = 0;
        for(int j = 0; j < N2 && exit == 0; j++) {
            if(path1[i] == path2[j]) {
                Key_st tmp = STsearchByIndex(G->st, path2[j]);
                printf("%s\n", tmp.name);
                exit = 1;
            }
        }
    }
}

int checkExitenceOfAvertexInSol(Item ** sol, int N, int vertex) {
    for(int i = 0; i < N ; i++) {
        if(vertex == (*sol)[i].vertex) {
            return 1;
        }
    }
    return 0;
}


void searchPathR(Item ** sol, int *wt, int * N_sol, int pos, int final_vertex, int * current_k, int * current_p, int k, int p, Graph G, Item ** best_sol, int * max_wt, int * N_best_sol, int cont) {
    if((*sol)[pos - 1].vertex == final_vertex && *wt > *max_wt) {
        //Final case
        if(*N_best_sol == 0) {
            *best_sol = malloc(sizeof(Item) * pos);
        }
        else {
            *best_sol = realloc(*best_sol, sizeof(Item) * pos);
        }
        *N_best_sol = pos;
        for(int i = 0; i < pos; i++) {
            (*best_sol)[i] = (*sol)[i];
        }
        *max_wt = *wt;

    }
    else {
        for(link x = G->ladj[(*sol)[pos - 1].vertex]; x->next != NULL; x = x->next) {
            // Controllo k
            int exitence = checkExitenceOfAvertexInSol(sol, pos, x->vertex);
            printf("vertice: %s, %d\n", STsearchByIndex(G->st, x->vertex), x->vertex);
            if(exitence == 0 || ( exitence == 1 && *current_k + 1 <= k)) {
                // Controllo p
                int increment_p = 0;
                if((*sol)[pos-1].new == 1 && exitence == 1) {
                    increment_p = 1;
                }
                if(*current_p + increment_p <= p) {
                    printf("ok -> livello %d\n", cont);
                    // Check dimension of array solution
                    if(pos == *N_sol) {
                        *N_sol *= 2;
                        (*sol) = (Item *) realloc(*sol, sizeof(Item) * (*N_sol));
                    }
                    if(exitence == 1) {
                        *current_k += 1;
                        (*sol)[pos].new = 0;
                    }
                    else {
                        (*sol)[pos].new = 1;
                    }
                    *current_p += increment_p;
                    (*sol)[pos].vertex = x->vertex;
                    *wt += x->wt;
                    if(cont == 3 && (*sol)[1].vertex == 3 && (*sol)[2].vertex == 1 && x->vertex == 4)
                        printf("%d", *wt);
                    if(cont == 4 && x->vertex == 5) 
                        printf("%d", *wt);
                    if(cont == 5 && x->vertex == 6)
                        printf("%d", *wt);
                    if(cont == 6 && x->vertex == 7)
                        printf("%d", *wt);
                    if(cont == 7 && x->vertex == 2)
                        printf("%d", *wt);
                    if(cont == 8 && x->vertex == 3)
                        printf("%d", *wt);
                    if(cont == 9 && x->vertex == 1)
                        printf("%d", *wt);
                    if(cont == 10 && x->vertex == 5)
                        printf("%d", *wt);
                    if(cont == 11 && x->vertex == 6)
                        printf("%d", *wt);
                    if(cont == 12 && x->vertex == 7)
                        printf("%d", *wt);
                    if(cont == 13 && x->vertex == 2)
                        printf("%d", *wt);
                    if(cont == 13 && x->vertex == 0)
                        printf("%d", *wt);
                    printf("%d", *wt);
                    searchPathR(sol, wt, N_sol, pos + 1, final_vertex, current_k, current_p, k, p, G, best_sol, max_wt, N_best_sol, cont + 1);
                    // Smarca
                    *wt -= x->wt;
                    if(exitence == 1) {
                        *current_k -= 1;
                    }
                    *current_p -= increment_p;
                }
            }
        }
    }
}



void funz2(Graph G, char * _vertex1, char * _vertex2, int k, int p) {
    Key_st tmp;
    strcpy(tmp.name, _vertex1);
    int vertex1 = STsearch(G->st, tmp);
    strcpy(tmp.name, _vertex2);
    int vertex2 = STsearch(G->st, tmp);
    Item * sol;
    Item * best_sol;
    int N_sol = 1;
    sol = (Item *) malloc(sizeof(Item) * N_sol);
   
    int N_best_sol = 0;
    int max_wt = 0;
    int wt;
    int current_k = 0;
    int current_p = 0;
    sol[0].vertex = vertex1;
    sol[0].new = 1;
    //test(&sol, &N_sol);
    wt = 0;
    searchPathR(&sol, &wt, &N_sol, 1, vertex2, &current_k, &current_p, k, p, G, &best_sol, &max_wt, &N_best_sol, 1);
    printf("Max wt: %d.\n", max_wt);
    for(int i = 0; i < N_best_sol; i++) {
        Key_st tmp;
        tmp = STsearchByIndex(G->st, best_sol[i].vertex);
        printf("%s ", tmp.name);
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
