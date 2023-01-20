
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../st/st.h"
#include "../graph/graph.h"

typedef struct node *link;
struct node { int v; int wt; link next; } ;
struct edge { int v; int w; int wt; };
struct graph_s {int V; int E; link *ladj; ST tab; Edge * edge_array; int DIM_edge_array; link z;} ;

static link NEW(int v, int wt, link next) {
    link x = malloc(sizeof *x);
    x->v = v; x->wt = wt; x->next = next;
    return x;
}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->E = 0;
    G->z = NEW(-1, -1, NULL);
    G->DIM_edge_array = 4;
    G->edge_array = malloc(sizeof(Edge) * G->DIM_edge_array);
    G->ladj = malloc(G->V*sizeof(link));
    for (int v = 0; v < G->V; v++)
        G->ladj[v] = G->z;
    G->tab = STInit(V);
    return G;
}

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v; e.w = w; e.wt = wt;
    return e;
}

static void insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;
    G->ladj[v] = NEW(w, wt, G->ladj[v]);
    if(G->E == G->DIM_edge_array) {
        G->DIM_edge_array *= 2;
        G->edge_array = realloc(G->edge_array, G->DIM_edge_array*sizeof(Edge));
    }
    G->edge_array[G->E] = e;
    G->E++;
        
}

static void removeE(Graph G, Edge e)
{
    // This function doesnt remove the edge form the edge array
    int v = e.v, w = e.w;
    link x, p;
    for (x = G->ladj[v], p = NULL; x != G->z; p = x, x = x->next)
    {
        if (x->v == w)
        {
            if (x == G->ladj[v])
                G->ladj[v] = x->next;
            else
                p->next = x->next;
            break;
        }
    }
    G->E--;
    free(x);
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}

Graph GRAPHLoad(FILE *fin) {
    int V, i, id1, id2, wt;
    char label1[31], label2[31];
    Graph G;
    fscanf(fin, "%d", &V);
    G = GRAPHinit(V);
    STLoad(fin, G->tab);
    while (fscanf(fin, "%s %s %d", label1, label2, &wt) == 3)
    {
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >= 0)
            GRAPHinsertE(G, id1, id2, wt);
        else
            exit(-1);
    }
    return G;
}

Graph GRAPHCopyWithFilterEdges(Graph graph_to_copy, int * filter) {
    int i, id1, id2, wt;
    char label1[31], label2[31];
    Graph G;
    G = GRAPHinit(graph_to_copy->V);
    STCopy(G->tab, graph_to_copy->tab);
    i = 0;
    while (i !=graph_to_copy->E )
    {
        if(filter[i] == 0 ){
            strcpy(label1, STsearchByIndex(graph_to_copy->tab, graph_to_copy->edge_array[i].v));
            strcpy(label2, STsearchByIndex(graph_to_copy->tab, graph_to_copy->edge_array[i].w));
            wt = graph_to_copy->edge_array[i].wt;
            id1 = STsearch(G->tab, label1);
            id2 = STsearch(G->tab, label2);
            if (id1 >= 0 && id2 >= 0)
                GRAPHinsertE(G, id1, id2, wt);
            else
                exit(-1);
        }
        i++;
    }
    return G;
}



void GRAPHfree(Graph G) {
    int v;
    link t, next;
    for (v=0; v < G->V; v++)
    for (t=G->ladj[v]; t != G->z; t = next) {
    next = t->next;
    free(t);
    }
    STFree(G->tab);
    free(G->ladj); 
    free(G->z);
    free(G->edge_array);
    free(G);
}

int dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st)
{   int ris = 1;
    link t;
    int v, w = e.w;
    Edge x;
    if (e.v != e.w)
        printf("(%s, %s): T \n", STsearchByIndex(G->tab, e.v), STsearchByIndex(G->tab, e.w));
    st[e.w] = e.v;
    pre[w] = (*time)++;
    for (t = G->ladj[w]; t != G->z && ris == 1; t = t->next) {
        if (pre[t->v] == -1)
            ris = dfsR(G, EDGEcreate(w, t->v, t->wt), time, pre, post, st);
        else
        {
            v = t->v;
            x = EDGEcreate(w, v, t->wt);
            if (post[v] == -1) {
                printf("(%s, %s): B\n", STsearchByIndex(G->tab, x.v), STsearchByIndex(G->tab, x.w));
                ris = -1;
                return ris;
            }
            else if (pre[v] > pre[w])
                printf("(%s,%s):F\n", STsearchByIndex(G->tab, x.v), STsearchByIndex(G->tab, x.w));
            else
                printf("(%s,%s):C\n", STsearchByIndex(G->tab, x.v), STsearchByIndex(G->tab, x.w));
        }
    }
    post[w] = (*time)++;
    return ris;
}

int dfsrWrapper(Graph G) {
    int id = G->edge_array[0].v;
    int v, time = 0;
    int * pre = malloc(G->V * sizeof(int));
    int * post  = malloc(G->V * sizeof(int));
    int * st = malloc(G->V * sizeof(int));
    for (v = 0; v < G->V; v++)
    {
        pre[v] = -1;
        post[v] = -1;
        st[v] = -1;
    }
    int ris = dfsR(G, EDGEcreate(id, id, 0), &time, pre, post, st);
    if(ris == 1) {
        for (v = 0; v < G->V; v++)
        if (pre[v] == -1)
            ris = dfsR(G, EDGEcreate(v, v, 0), &time, pre, post, st);
            if(ris == 1)
                printf("No back\n");
            else {
                printf("si back");
                return  -1;
            }
                
    }
    else {
        printf("si back");
        return  -1;
    }
    return 1;
}

void disp_rip(int * sol, int pos, int N, Graph G, int *** dag_edges_array, int * N_dag_edges_array, int * DIM_MAX_dag_edges_array, int * n_edges_deleted) {
    if(pos == N) {
        // Final case
        /*for(int i = 0; i < N; i++) {
            printf("%d ", sol[i]);
        }
        printf("\n");*/
        Graph G_copy = GRAPHCopyWithFilterEdges(G, sol);
        if(G_copy->E != 0) {
            int tmp_n_edges_deleted = 0;
            for(int i = 0; i < N; i++) {
                if(sol[i] == 1)
                    tmp_n_edges_deleted += 1;
            }
            if(*N_dag_edges_array == 0 || (tmp_n_edges_deleted == *n_edges_deleted)) {
                int ris = dfsrWrapper(G_copy);
                if(ris == 1) {
                    *n_edges_deleted = tmp_n_edges_deleted;
                    if(*N_dag_edges_array == *DIM_MAX_dag_edges_array) {
                        *DIM_MAX_dag_edges_array *= 2;
                        *dag_edges_array = realloc(*dag_edges_array, *DIM_MAX_dag_edges_array * sizeof(int *));
                    }
                    (*dag_edges_array)[*N_dag_edges_array] = malloc(sizeof(int) * N);
                    for(int i = 0; i < N; i++) {
                        (*dag_edges_array)[*N_dag_edges_array][i] = sol[i];
                    }
                    *N_dag_edges_array += 1;
                }
            }
            
        }
        GRAPHfree(G_copy);
    }
    else {
        for(int i = 0; i < 2; i++) {
            sol[pos] = i;
            disp_rip(sol, pos + 1, N, G, dag_edges_array, N_dag_edges_array, DIM_MAX_dag_edges_array, n_edges_deleted);
        }
    }
}

void disp_rip_wrapper(int N, Graph G, int *** dag_edges_array, int * N_dag_edges_array, int * DIM_MAX_dag_edges_array, int * N_edges_deleted) {
    int sol[N];
    disp_rip(sol, 0, N, G, dag_edges_array, N_dag_edges_array, DIM_MAX_dag_edges_array, N_edges_deleted);
}

void GRAPHReturnPossibleDag(Graph G, Edge  *** edges_array_to_return, int *N_dag_edges_array_to_return, int * N_edges_deleted) {
    int N_dag_edges_array = 0;
    int DIM_MAX_dag_edges_array = 2;
    int ** dag_edges_array = malloc(sizeof(int *)*DIM_MAX_dag_edges_array);
    disp_rip_wrapper(G->E, G, &dag_edges_array, &N_dag_edges_array, &DIM_MAX_dag_edges_array, N_edges_deleted);
    if(*N_edges_deleted != 0) {
        *edges_array_to_return = malloc(sizeof(Edge *) * N_dag_edges_array);
        for(int i = 0; i < N_dag_edges_array; i++) {
            printf("%d possibilità, archi rimossi:\n", i+1);
            (*edges_array_to_return)[i] = malloc(sizeof(Edge) * (*N_edges_deleted));
            int cont = 0;
            for(int j = 0; j < G->E; j++) {
                if(dag_edges_array[i][j] == 1) {
                    printf("\t- Arco %s -> %s. Peso: %d\n", STsearchByIndex(G->tab, G->edge_array[j].v), STsearchByIndex(G->tab, G->edge_array[j].w), G->edge_array[j].wt);
                    (*edges_array_to_return)[i][cont] = G->edge_array[j];
                    cont++;
                }
                //printf("%d ", dag_edges_array[i][j]);
            }
            printf("\n");
        }
        *N_dag_edges_array_to_return = N_dag_edges_array;
    }
    else {
        *edges_array_to_return = NULL;
    }
    for(int i = 0; i < N_dag_edges_array; i++) {
        free(dag_edges_array[i]);
    }
    free(dag_edges_array);
    
}

void GRAPHFreeEdgesArray(Edge ** edges_array, int N) {
    for(int i = 0; i < N; i++) {
        free(edges_array[i]);
    }
    free(edges_array);
}

int GRAPHPrintDagThatDontHaveMaxWeight(Graph G, Edge ** edges_array, int N, int N_edges_deleted) {
    int weights[N];
    int max_weight = -100000;
    for(int i = 0; i < N; i++) {
        int tmp_weight = 0;
        for(int j = 0; j < N_edges_deleted; j++) {
            tmp_weight+=edges_array[i][j].wt;
        }
        weights[i] = tmp_weight;
        if(tmp_weight > max_weight)
            max_weight = tmp_weight;
    }
    for(int i = 0; i < N; i++) {
        if(weights[i] == max_weight) {
            printf("Dag con peso massimo ha archi %d:\n", max_weight);
            for(int j = 0; j < N_edges_deleted; j++) {
                printf("\t- Arco %s -> %s. Peso: %d\n", STsearchByIndex(G->tab, edges_array[i][j].v), STsearchByIndex(G->tab, edges_array[i][j].w), edges_array[i][j].wt);
            }
            return i;
        }
    }
}

void GRAPHspBF(Graph G_to_copy, Edge * edge_array, int N_edges_deleted)
{
    int filter[G_to_copy->E];
    int cont = 0;
    for(int i = 0; i < G_to_copy->E; i++) {
        if(G_to_copy->edge_array[i].v == edge_array[cont].v && G_to_copy->edge_array[i].w == edge_array[cont].w) {
            filter[i] = 1;
            cont++;
        }
        else {
            filter[i] = 0;
        }
    }
    Graph G = GRAPHCopyWithFilterEdges(G_to_copy, filter);
    for(int id = 0; id < G_to_copy->V; id++) {
        int maxWT = -100000;
        int v, i, negcycfound;
        link t;
        int *st, *d;
        st = malloc(G->V * sizeof(int));
        d = malloc(G->V * sizeof(int));
        for (v = 0; v < G->V; v++)
        {
            st[v] = -1;
            d[v] = maxWT;
        }
        d[id] = 0;
        st[id] = id;
        for (i = 0; i < G->V - 1; i++)
            for (v = 0; v < G->V; v++)
                if (d[v] > maxWT)
                    for (t = G->ladj[v]; t != G->z; t = t->next)
                        if (d[t->v] < d[v] + t->wt)
                        {
                            d[t->v] = d[v] + t->wt;
                            st[t->v] = v;
                        }
        negcycfound = 0;
        for (v = 0; v < G->V; v++)
            if (d[v] > maxWT)
                for (t = G->ladj[v]; t != G->z; t = t->next)
                    if (d[t->v] < d[v] + t->wt)
                        negcycfound = 1;
        if (negcycfound == 0)
        {
            printf("\n Max.dist. from %s\n", STsearchByIndex(G->tab, id));
            for (v = 0; v < G->V; v++)
                printf("%s: %d\n", STsearchByIndex(G->tab, v), d[v]);
        }
        else
            printf("\n Negative cycle found!\n");
    }
   GRAPHfree(G);
}