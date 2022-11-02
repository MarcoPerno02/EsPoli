#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u;
    int v;
} Arc;

void loadArcs(int * N, int * E, Arc ** arcs, int ** nodes);
void vertexCover(int N, int E, Arc * arcs, int * nodes);
int comb(int pos, int *nodes, int *sol, int n, int k, int start, int cnt, Arc *arcs, int E);
int checkComb(int * comb, Arc * arcs, int E, int combLen);

int main() {
    int N, E;
    int * nodes;
    Arc * arcs;
    loadArcs(&N, &E, &arcs, &nodes);
    vertexCover(N, E, arcs, nodes);

}

void loadArcs(int * N, int * E, Arc ** arcs, int ** nodes) {
    FILE * fin;
    if((fin = fopen("grafo.txt", "r")) == NULL) {
        printf("Errore nell'apertura del file grafo.txt");
        exit(1);
    }
    fscanf(fin, "%d %d", N, E);
    *arcs = (Arc *) malloc(sizeof(Arc) * (*E));
    *nodes = (int *) malloc(sizeof(int) * (*N));
    for(int i = 0; i < *N; i++) {
        (*nodes)[i] = i;
    }
    for(int i = 0; i < *E; i++) {
        fscanf(fin, "%d %d", &((*arcs)[i].u), &((*arcs)[i].v));
    }
    fclose(fin);
}

void vertexCover(int N, int E, Arc * arcs, int * nodes) {
    for(int k = 2; k <= N; k++) {
        int * sol;
        sol = malloc(sizeof(int) * k);
        for(int i = 0; i < k; i++) {
            sol[i] = -1;
        }
        comb(0, nodes, sol, 4, k, 0, 0, arcs, E);
    }
    
}

int comb(int pos, int *nodes, int *sol, int n, int k, int start, int cnt, Arc * arcs, int E)
{
    int i, j;
    if (pos >= k)
    {   
        int valid = checkComb(sol, arcs, E, k);
        if(valid == 1) {
            for (i = 0; i < k; i++)
                printf("%d ", sol[i]);
            printf("\n");
        }
        return cnt + 1;
    }
    for (i = start; i < n; i++)
    {
        sol[pos] = nodes[i];
        cnt = comb(pos + 1, nodes, sol, n, k, i + 1, cnt, arcs, E);
    }
    return cnt;
}

int checkComb(int * comb, Arc * arcs, int E, int combLen)
{
    // Returns 1 if the combination is valid, otherwhise 0
    int valid = 1;
    int i, j;
    i = 0;
    while(valid == 1 && i < E) {
        j = 0;
        valid = 0;
        while(j < combLen && valid == 0)
        {
            if(arcs[i].u == comb[j] || arcs[i].v == comb[j]) {
                valid = 1;
            }
            else {
                j++;
            }
        }
        i++;
    }
    return valid;
}