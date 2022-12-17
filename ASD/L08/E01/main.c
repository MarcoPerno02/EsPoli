#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    int id;
    char name[100+1];
    int type;
    int dir_enter;
    int dir_exit;
    int prec;
    int final;
    float score;
    int difficulty;
    float appetability;
} Elem;

typedef struct {
    Elem * elems[5];
    int nElem;
    int difficulty;
    float score;
    int id;
} Diag;

typedef struct
{
    Diag diags[3];
    int difficulty_tot;
    float score_tot;
} Sequence;

int loadElems(Elem ** elems);
void loadDiag(Diag * diag, int LIM_DIM_DIAGS, int dd, int dp, Elem * elems, int N_elems, int diff_diag_before, int n_diag);
void bubblesort(Elem * v, int n);
void buildSolution(Elem * elems, int N_elems);
int checkAcceptabilityNewElem(Diag * diag_test, int idx_last_elem, int diff_diag_before, Elem * new_elem, int dd, int dp, int n_diag);
int checkNewDifficulty(Diag * diag_test, Elem * new_elem, int dd, int dp, int diff_before_diag, int n_diag);
void printElem(Elem * elem);
void printSequence(Sequence * sequence, int format);
void checkSequence(Sequence * sequence);
void calculateScore(Diag * diag, int n_diag);
void printDiag(Diag * diag);

int main() {
    Elem * elems;
    int N_elems = loadElems(&elems);
    buildSolution(elems, N_elems);
    free(elems);
}

int loadElems(Elem ** elems) {
    FILE * fin;
    if((fin = fopen("elementi.txt", "r")) == NULL) exit(-1);
    int N_elems;
    fscanf(fin, "%d", &N_elems);
    *elems = malloc(N_elems * sizeof(Elem));
    for(int i = 0; i < N_elems; i++) {
        fscanf(fin, "%s %d %d %d %d %d %f %d", (*elems)[i].name, &((*elems)[i].type), &((*elems)[i].dir_enter), &((*elems)[i].dir_exit), &((*elems)[i].prec), &((*elems)[i].final), &((*elems)[i].score), &((*elems)[i].difficulty));
        (*elems)[i].appetability = ((*elems)[i].score + 1)/ ((*elems)[i].difficulty + 1);
        (*elems)[i].id = i;
    }
    fclose(fin);
    bubblesort(*elems, N_elems);
    return N_elems;
}

void bubblesort(Elem * v, int n) {
    int i, k;
    Elem temp;
    for (i = 0; i < n - 1; i++)
    {
        for (k = 0; k < n - 1 - i; k++)
        {
            if (v[k].appetability < v[k + 1].appetability)
            {
                temp = v[k];
                v[k] = v[k + 1];
                v[k + 1] = temp;
            }
        }
    }
}

void buildSolution(Elem * elems, int N_elems) {
    FILE * fin;
    if((fin = fopen("testset.txt", "r")) == NULL) exit(-1);
    int n;
    fscanf(fin, "%d", &n);
    for(int i = 0; i < n; i++) {
        int dd, dp;
        fscanf(fin, "%d %d", &dd, &dp);
        Sequence sequence_max;
        sequence_max.difficulty_tot = 0;
        Diag diag_to_add;
        loadDiag(&diag_to_add, 5, dd, dp, elems, N_elems, sequence_max.difficulty_tot, i);
        sequence_max.diags[i] = diag_to_add;
        sequence_max.difficulty_tot+=diag_to_add.difficulty;
        
    }
}

void loadDiag(Diag * diag, int LIM_DIM_DIAGS, int dd, int dp, Elem * elems, int N_elems, int diff_diag_before, int n_diag) {
    diag->nElem = 0;
    diag->difficulty = 0;
    int cont_elems = 0;
    for(int i = 0; i < LIM_DIM_DIAGS && cont_elems != N_elems; i++) {
        if(checkAcceptabilityNewElem(diag, i-1, diff_diag_before, &(elems[cont_elems]), dd, dp, n_diag) == 1) {
            diag->elems[i] = &elems[cont_elems];
            diag->nElem++;
            cont_elems = 0;
        }
        else {
            cont_elems++;
        }
    }
}

int checkAcceptabilityNewElem(Diag * diag_test, int idx_last_elem, int diff_diag_before, Elem * new_elem, int dd, int dp, int n_diag) {
    // Returns 1 if is okay, otherwise 0
    // Check if the new elem has the same entry of the last one
    //printElem(new_elem);
    if(diag_test->nElem != 0) {
        if(diag_test->elems[idx_last_elem]->dir_exit != new_elem->dir_enter)
            return 0;
        // In the first diag I add an element acrobatic front, transition back and acrobatic in the first four positions
        if(n_diag == 0 && idx_last_elem == 0) {
            if(new_elem->type != 0)
                return 0;
        }
        else if(n_diag == 0 && idx_last_elem == 1) {
            if(new_elem->type != 1)
                return 0;
        }
        else if(n_diag == 0 && idx_last_elem == 2) {
            if(new_elem->type == 0)
                return 0;
        }

    }
    else {
        // Prec must be 0 and dir enter 1 and must be acrobatci
        if(new_elem->prec == 1 || new_elem->dir_enter == 0 || new_elem->type !=2) 
            return 0;
    }
    if(checkNewDifficulty(diag_test, new_elem, dd, dp, diff_diag_before, n_diag) == 1) 
        return 1;
    return 0;
}



int checkNewDifficulty(Diag * diag_test, Elem * new_elem, int dd, int dp, int diff_before_diag, int n_diag) {
    // Calculate the new difficulty and, if it is acceptable, the function updates it
    int new_difficulty_for_last_diag = diag_test->difficulty + new_elem->difficulty;

    if(new_difficulty_for_last_diag <= dd) {
        //printf("%d\n", diag_test->difficulty);
        if(n_diag != 3) {
            if(new_difficulty_for_last_diag + diff_before_diag < dp)
                diag_test->difficulty = new_difficulty_for_last_diag;
                return 1;
        }
        else {
            if(new_difficulty_for_last_diag + diff_before_diag <= dp)
                diag_test->difficulty = new_difficulty_for_last_diag;
                return 1;
        }
    }
    return 0;
}

void printElem(Elem * elem) {
    printf("Name: %s\nType (1 back, 2 front): %d\nDir_enter (0 back, 1 front): %d\nDir_exit (0 back, 1 front): %d\nPrec: %d\nFinal: %d\nScore: %f\nDifficulty: %d\n-------------\n", elem->name, elem->type, elem->dir_enter, elem->dir_exit, elem->prec, elem->final, elem->score, elem->difficulty);
}

void printSequence(Sequence * sequence, int format) {
    printf("Score_tot: %f\n", sequence->score_tot);
    if(format == 1) {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < sequence->diags[i].nElem; j++) {
                printf("%s ", sequence->diags[i].elems[j]->name);
                //printElem(sequence->diags[i].elems[j]);
            }
            printf(" | ");
        }
        printf("\n");
    }
    else {
        for(int i = 0; i < 3; i++) {
            printf("_");
            for(int j = 0; j < sequence->diags[i].nElem; j++) {
                printf("___");
            }
            printf("_  ");
        }
        printf("\n");
        for(int i = 0; i < 3; i++) {
            printf("|");
            for(int j = 0; j < sequence->diags[i].nElem; j++) {
                printf(" %d ", sequence->diags[i].elems[j]->id);
            }
            printf(" | ");
        }
        printf("\n");
        for(int i = 0; i < 3; i++) {
            printf("|");
            for(int j = 0; j < sequence->diags[i].nElem; j++) {
                printf("___");
            }
            printf(" | ");
        }
        printf("\n");
    }
    
}

void printDiag(Diag * diag) {
    printf("_");
    for(int j = 0; j < diag->nElem; j++) {
        printf("___");
    }
    printf("_  ");
    printf("\n");
    printf("|");
    for(int j = 0; j < diag->nElem; j++) {
        printf(" %d ", diag->elems[j]->id);
    }
    printf(" | ");
    printf("\n");
    printf("|");
    for(int j = 0; j < diag->nElem; j++) {
        printf("___");
    }
    printf(" | ");
    printf("\n");
}

void checkSequence(Sequence * sequence) {
    int ok = 1;
    int diag_to_test[3] = {0, 0, 1};
    int id_matrix[3][5] = {{0,0,0,0,0}, {0,0,0,0,0}, {0,3,3,3,3}};
    for(int i = 0; i < 3 && ok == 1; i++) {
        if(diag_to_test[i] == 1) {
            for(int j = 0; j < sequence->diags[i].nElem && ok == 1; j++) {
                if(sequence->diags[i].elems[j]->id != id_matrix[i][j]) {
                    ok = 0;
                }
            }
            
        }
    }
    if(ok == 1) {
        printf("");
    }

}

void calculateScore(Diag * diag, int n_diag) {
    float score = 0;
    float score_to_add = 0;
    for(int j = 0; j < diag->nElem; j++) {
        score_to_add += diag->elems[j]->score;
    }
    score+=score_to_add;
    diag->score = score;
}

