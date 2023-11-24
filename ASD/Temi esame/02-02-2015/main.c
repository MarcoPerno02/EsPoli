#include <stdio.h>
#include <stdlib.h>
#include "graph/graph.h"
#include "st/st.h"

int main() {
    FILE * fin = fopen("file1.txt", "r");
    Graph G = GRAPHLoad(fin);
    fclose(fin);   
    fin = fopen("file2.txt", "r");
    readSolution(G, fin);
    wrapperER(G);
    
    fclose(fin);   
    GRAPHFree(G);
}