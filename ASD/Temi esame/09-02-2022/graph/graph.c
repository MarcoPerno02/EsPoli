#include <stdio.h>
#include <stdlib.h>
#include "../graph/graph.h"

typedef struct {
    int r;
    int c;
    int dir;
} Move;

struct graph_s {
    int NR;
    int NC;
    int ceil_avalaible;
    int ceil_left;
    int ** madj;
};

Graph GRAPHInit(int NR, int NC) {
    Graph G = malloc(sizeof(struct graph_s));
    G->ceil_avalaible = 0;
    G->NR = NR;
    G->NC = NC;
    G->madj = malloc(sizeof(int *) * NR);
    for(int i = 0; i < NR; i++) {
        G->madj[i] = malloc(sizeof(int) * NC);
    }
    return G;
}

Graph GRAPHCopy(Graph G) {
    Graph G_to_return = GRAPHInit(G->NR, G->NC);
    for(int i = 0; i < G->NR; i++) {
        for(int j = 0; j < G->NC; j++) {
            G_to_return->madj[i][j] = G->madj[i][j];
        }
    }
    return G_to_return;
}

void GRAPHFree(Graph G) {
    for(int i = 0; i < G->NR; i++) {
        free(G->madj[i]);
    }
    free(G->madj);
    free(G);
}

Graph GRAPHLoad(FILE * fin) {
    int NR, NC;
    fscanf(fin, "%d %d", &NR, &NC);
    Graph G = GRAPHInit(NR, NC);
    int r, c;
    for(int i = 0; i < G->NR; i++) {
        for(int j = 0; j < G->NC; j++) {
            fscanf(fin, "%d", &(G->madj[i][j]));
            if(G->madj[i][j] != 1) {
                G->ceil_avalaible++;
            }
        }
    }
    G->ceil_left = G->ceil_avalaible;
    return G;
}

int CanDir(Graph G, int r, int c, int dir) {
    // dir:
    //  - 0 Up
    //  - 1 Right
    //  - 2 Down
    //  - 3 Left
    if(dir == 0) {
        if(r-1 >= 0 && G->madj[r-1][c] == 0)
            return 1;
    }
    else if(dir == 1) {
        if(c+1 < G->NC && G->madj[r][c+1] == 0)
            return 1;
    }
    else if(dir == 2) {
        if(r+1 < G->NR && G->madj[r+1][c] == 0)
            return 1;
    }
    else if(dir == 3) {
        if(c-1 >= 0 && G->madj[r][c-1] == 0)
            return 1;
    }
    return 0;
}

int IncrementRot(Move * sol, int pos) {
    if(sol[pos-1].dir != 4) {
        if(sol[pos].dir != sol[pos - 1].dir) {
            return 1;
        }
    }
    return 0;
}

void printSol(Move * sol, Graph G) {
    for(int i = 0; i < G->NR; i++) {
        for(int j = 0; j < G->NC; j++) {
            printf("%d ", G->madj[i][j]);
        }
        printf("\n");
    }
}

void funzR(Move * sol, int pos, int rot, int cont, Graph G, Move * best_sol, int * min_rot) {
    int can_up = CanDir(G, sol[pos-1].r, sol[pos-1].c, 0);
    int can_right = CanDir(G, sol[pos-1].r, sol[pos-1].c, 1);
    int can_down = CanDir(G, sol[pos-1].r, sol[pos-1].c, 2);
    int can_left = CanDir(G, sol[pos-1].r, sol[pos-1].c, 3);
    if(can_up == 0 && can_down == 0 && can_left == 0 && can_right == 0 && cont - 2 == G->ceil_avalaible) {
        // Terminal case
        if(rot < *min_rot) {
            *min_rot = rot;
            for(int i = 0; i < G->ceil_avalaible; i++) {
                best_sol[i] = sol[i];
            }
        }
        //printSol(sol, G);
    }
    else {
        if(can_up == 1) {
            sol[pos].r = sol[pos-1].r - 1;
            sol[pos].c = sol[pos-1].c;
            sol[pos].dir = 0;
            //printf("%d %d. dir: %d\n", sol[pos].r, sol[pos].c, sol[pos].dir);
            G->ceil_left -= 1;
            G->madj[sol[pos].r][sol[pos].c] = cont;
            int increment = IncrementRot(sol, pos);
            rot += increment;
            funzR(sol, pos + 1, rot, cont + 1, G, best_sol, min_rot);
            G->ceil_left += 1;
            G->madj[sol[pos].r][sol[pos].c] = 0;
            rot -= increment;
        }
        if(can_right == 1) {
            sol[pos].r = sol[pos-1].r;
            sol[pos].c = sol[pos-1].c + 1;
            sol[pos].dir = 1;
            //printf("%d %d. dir: %d\n", sol[pos].r, sol[pos].c, sol[pos].dir);
            G->ceil_left -= 1;
            G->madj[sol[pos].r][sol[pos].c] = cont;
            int increment = IncrementRot(sol, pos);
            rot += increment;
            funzR(sol, pos + 1, rot, cont + 1, G, best_sol, min_rot);
            G->ceil_left += 1;
            G->madj[sol[pos].r][sol[pos].c] = 0;
            rot -= increment;
        }  
        if(can_down == 1) {
            sol[pos].r = sol[pos-1].r + 1;
            sol[pos].c = sol[pos-1].c;
            sol[pos].dir = 2;
            //printf("%d %d. dir: %d\n", sol[pos].r, sol[pos].c, sol[pos].dir);
            G->ceil_left -= 1;
            G->madj[sol[pos].r][sol[pos].c] = cont;
            int increment = IncrementRot(sol, pos);
            rot += increment;
            funzR(sol, pos + 1, rot, cont + 1, G, best_sol, min_rot);
            G->ceil_left += 1;
            G->madj[sol[pos].r][sol[pos].c] = 0;
            rot -= increment;
        } 
        if(can_left == 1) {
            sol[pos].r = sol[pos-1].r;
            sol[pos].c = sol[pos-1].c - 1;
            sol[pos].dir = 3;
            //printf("%d %d. dir: %d\n", sol[pos].r, sol[pos].c, sol[pos].dir);
            G->ceil_left -= 1;
            G->madj[sol[pos].r][sol[pos].c] = cont;
            int increment = IncrementRot(sol, pos);
            rot += increment;
            funzR(sol, pos + 1, rot, cont + 1, G, best_sol, min_rot);
            G->ceil_left += 1;
            G->madj[sol[pos].r][sol[pos].c] = 0;
            rot -= increment;
        } 
    }
}

void GeneraSol(Graph G) {
    Move sol[G->ceil_avalaible];
    Move best_sol[G->ceil_avalaible];
    int min_rot = 99999;
    sol[0].r = 0;
    sol[0].c = 0;
    sol[0].dir = 4;
    G->madj[0][0] = 2;
    funzR(sol, 1, 0, 3, G, best_sol, &min_rot);
    for(int i = 1; i < G->ceil_avalaible; i++) {
        G->madj[best_sol[i].r][best_sol[i].c] = i+2;
    }
    printSol(best_sol, G);
    for(int i = 3; i < G->ceil_avalaible; i++) {
        G->madj[best_sol[i].r][best_sol[i].c] = 0;
    }
    G->madj[0][0] = 0;
}