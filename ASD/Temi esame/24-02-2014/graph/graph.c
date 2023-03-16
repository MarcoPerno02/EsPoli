#include <stdio.h>
#include <stdlib.h>
#include "../graph/graph.h"
#include "../st/st.h"

typedef struct {
    int u;
    int v;
    int wt;
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

Graph GRAPHInit(FILE * fin) {
    Graph G = malloc(sizeof(struct graph_s));
    G->st = STInit(1);
    Item_st item1;
    Item_st item2;
    int u, v, wt;
    G->Max_N_edges = 1;
    G->edges = malloc(sizeof(Edge) * G->Max_N_edges);
    G->N_edges = 0;
    while(fscanf(fin, "%s %d %s", item1.key.name, &wt, item2.key.name) != EOF) {
        STInsert(G->st, item1);
        STInsert(G->st, item2);
        if(G->N_edges == G->Max_N_edges) {
            G->Max_N_edges *= 2;
            G->edges = realloc(G->edges, sizeof(Edge) * G->Max_N_edges);
        }
        Edge edge;
        edge.u = STsearch(G->st, item1.key);
        edge.v = STsearch(G->st, item2.key);
        edge.wt = wt;
        G->edges[G->N_edges] = edge;
        G->N_edges++;
    }
    G->ladj = malloc(sizeof(link) * STcount(G->st));
    G->z = malloc(sizeof(struct node_s));
    G->z->next = NULL;
    G->z->vertex = -1;
    for(int i = 0; i < STcount(G->st); i++) {
        G->ladj[i] = G->z;
    }
    for(int i = 0; i < G->N_edges; i++) {
        link ex_head = G->ladj[G->edges[i].u];
        link new_head = malloc(sizeof(struct node_s));
        new_head->vertex = G->edges[i].v;
        new_head->next = ex_head;
        G->ladj[G->edges[i].u] = new_head;
    }
    return G;
}

void GRAPHFunz1(Graph G) {
    int mat[STcount(G->st)][2];
    for(int i = 0; i < STcount(G->st); i++) {
        mat[i][0] = 0;
        mat[i][1] = 0;
    }
    for(int i = 0; i < G->N_edges; i++) {
        mat[G->edges[i].u][1]++;
        mat[G->edges[i].v][0]++;
    }
    int ok = 1;
    int tmp = mat[0][0];
    for(int i = 0; i < G->N_edges && ok == 1; i++) {
        if(mat[i][0] == tmp && mat[i][1] == tmp) {

        }
        else {
            ok = -1;
        }
    }
    if(ok == 1) {
        printf("stessi degree\n");
    }
    else {
        printf("non stessi degree\n");
    }
}

void printR(Graph G, int * st, int id) {
    for(int i = 0; i < STcount(G->st); i++) {
        if(st[i] == id && i != id) {
            Key_st key1 = STsearchByIndex(G->st, id);
            Key_st key2 = STsearchByIndex(G->st, i);
            printf("%s è collegato a %s\n", key1.name, key2.name);
            printR(G, st, i);
        }
    }
}

void GRAPHFunz2(Graph G) {
    Key_st key;
    int relax[STcount(G->st)];
    int st[STcount(G->st)];
    printf("Ibserire nome: ");
    scanf("%s", key.name);
    int id = STsearch(G->st, key);
    for(int i = 0; i < STcount(G->st); i++) {
        if(i != id) {
            relax[i] = -10;
            st[i] = -1;
        }
        else {
            relax[i] = 0;
            st[i] = i;
        }
    }
    int check_changes = 1;
    int exit = 0;
    while(exit  == 0) {
        for(int i = 0; i < G->N_edges; i++) {
            if(i == 0) {
                check_changes = 0;
            }
            if(relax[G->edges[i].u] + G->edges[i].wt > relax[G->edges[i].v] && G->edges[i].v != id) {
                relax[G->edges[i].v] = relax[G->edges[i].u] + G->edges[i].wt;
                st[G->edges[i].v] = G->edges[i].u;
                check_changes = 1;
            }
            if(i == G->N_edges - 1 && check_changes == 0) {
                exit = 1;
            }
        }
    }
    Key_st key_to_stamp = STsearchByIndex(G->st, id);
    printf("Partenza in %s\n", key_to_stamp.name);
    printR(G, st, id);
    
} 

Graph GRAPHFree(Graph G) {
    for(int i = 0; i < STcount(G->st); i++) {
        link test;
        test = G->ladj[i];
        while(test->next != NULL) {
            link tmp = test;
            test = test->next;
            free(tmp);
        }
    }
    STFree(G->st);
    free(G->z);
    free(G);
}
