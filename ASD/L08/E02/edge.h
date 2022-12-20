#include <stdio.h>
#include <stdlib.h>
#include "st.h"

typedef struct edge * Edge;
struct edge {
    int v;
    char v_name[30];
    char v_subnet[30];
    int w;
    char w_name[30];
    char w_subnet[30];
    int weight;
};

typedef struct edgeArray * EdgeArray;
struct edgeArray {
    Edge edges;
    int N;
    int N_vertex;
};


EdgeArray EDGEReadEdges(FILE *fin, ST st);
void EDGEPrintEdges(EdgeArray edgesArray);