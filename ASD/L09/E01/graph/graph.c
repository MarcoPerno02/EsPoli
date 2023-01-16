
#include <stdio.h>
#include <stdlib.h>
#include "../st/st.h"
#include "../graph/graph.h"

typedef struct node *link;
struct node { int v; int wt; link next; } ;
struct graph{int V; int E; link *ladj; ST tab; link z;} ;

Graph GRAPHLoad(FILE *fin) {
    ST st = STLoad(fin);
    STFree(st);
}