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

// diag_1_opt = 2 ---> front transiton back
// diag_1_opt = 1 ---> back transiton front
//int diag_1_opt;
// if there is not a transition front back or back front I save that in this variable
// 2 stands for not ok front
// 1 stands for not ok back
// 0 stands for ok both
// If, for example there is not a transition front back, I suppose there is at least one transition back front
//int check_diag_1_opt = 0;
int diag_1_cond_completed = 0;
int both_acr_type = 0;
int acr_type_added = -1;

int loadElems(Elem ** elems);
void loadDiag(Diag * diag, int LIM_DIM_DIAGS, int dd, int dp, Elem * elems_app, Elem * elems_diff, int N_elems, int diff_diag_before, int n_diag);
void bubblesort_desc_appetability(Elem * v, int n);
void bubblesort_asc_diff(Elem * v, int n);
void buildSolution(Elem * elems_app, Elem * elems_diff, int N_elems);
int checkAcceptabilityNewElem(Diag * diag_test, int idx_last_elem, int diff_diag_before, Elem * new_elem, int dd, int dp, int n_diag, int add_trans_in_first);
int checkNewDifficulty(Diag * diag_test, Elem * new_elem, int dd, int dp, int diff_before_diag, int n_diag);
void printElem(Elem * elem);
void printSequence(Sequence * sequence, int format);
void checkSequence(Sequence * sequence);
void calculateScore(Sequence * sequence);
void printDiag(Diag * diag);

int main() {
    Elem * elems_app;
    int N_elems = loadElems(&elems_app);
    Elem * elems_diff = malloc(sizeof(Elem) * N_elems);
    for(int i = 0; i < N_elems; i++) {
        elems_diff[i] = elems_app[i];
    }
    bubblesort_asc_diff(elems_diff, N_elems);
    buildSolution(elems_app, elems_diff, N_elems);
    free(elems_diff);
    free(elems_app);
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
    bubblesort_desc_appetability(*elems, N_elems);
    return N_elems;
}

void bubblesort_asc_diff(Elem * v, int n) {
    int i,k;
    Elem temp;
    for (i = 0; i < n - 1; i++)
    {
        for (k = 0; k < n - 1 - i; k++)
        {
            if (v[k].difficulty > v[k + 1].difficulty)
            {
                temp = v[k];
                v[k] = v[k + 1];
                v[k + 1] = temp;
            }
        }
    }
}

void bubblesort_desc_appetability(Elem * v, int n) {
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

void buildSolution(Elem * elems_app, Elem * elems_diff, int N_elems) {
    FILE * fin;
    if((fin = fopen("testset.txt", "r")) == NULL) exit(-1);
    int n;
    fscanf(fin, "%d", &n);
    for(int i = 0; i < n; i++) {
        int dd, dp;
        fscanf(fin, "%d %d", &dd, &dp);
        Sequence sequence_max;
        sequence_max.difficulty_tot = 0;
        sequence_max.score_tot = 0;
        diag_1_cond_completed = 0;
        both_acr_type = 0;
        acr_type_added = -1;
        for(int j = 0; j < 3; j++) {
            Diag * diag_to_add = malloc(sizeof(Diag));
            loadDiag(diag_to_add, 5, dd, dp, elems_app, elems_diff, N_elems, sequence_max.difficulty_tot, j);
            sequence_max.diags[j] = *diag_to_add;
            sequence_max.difficulty_tot+=(*diag_to_add).difficulty;
            sequence_max.score_tot += (*diag_to_add).score;
            free(diag_to_add);
        }
        calculateScore(&sequence_max);
        printSequence(&sequence_max, 1);
    }
}

void loadDiag(Diag * diag, int LIM_DIM_DIAGS, int dd, int dp, Elem * elems_app, Elem * elems_diff, int N_elems, int diff_diag_before, int n_diag) {
    diag->nElem = 0;
    diag->difficulty = 0;
    int cont_elems = 0;
    int add_trans = 0;
    Elem * elem_to_test;
    int limit_for_elems_diff;
    if(n_diag == 0) {
        limit_for_elems_diff = 2;
    }
    else {
        limit_for_elems_diff = 1;
    }
    for(int i = 0; i < N_elems && cont_elems != LIM_DIM_DIAGS; i++) {
        if((n_diag == 0 && cont_elems < limit_for_elems_diff) || (n_diag == 1 && cont_elems < limit_for_elems_diff)) {
            elem_to_test = &(elems_diff[i]);
        }
        else {
            elem_to_test = &(elems_app[i]);
        }
        if(checkAcceptabilityNewElem(diag, cont_elems-1, diff_diag_before, elem_to_test, dd, dp, n_diag, add_trans) == 1) {
            if(add_trans == 1)
                add_trans = 0;
            diag->elems[cont_elems] = elem_to_test;
            diag->nElem++;
            if(elem_to_test->final == 1) {
                i = N_elems;
            } else {
                i = -1;
            }
            cont_elems++;
        }
        else {
            if(i == N_elems-1 && add_trans == 0) {
                i = -1;
                limit_for_elems_diff++;
                add_trans = 1;
            }
        }
    }
}

int checkAcceptabilityNewElem(Diag * diag_test, int idx_last_elem, int diff_diag_before, Elem * new_elem, int dd, int dp, int n_diag, int add_trans_in_first) {
    // Returns 1 if is okay, otherwise 0
    // Check if the new elem has the same entry of the last one
    //printElem(new_elem);
    int update_acr_type_added = 0;
    int update_both_acr_type = 0;
    int update_diag_1_cond_completed = 0;
    if(diag_test->nElem != 0) {
        if(diag_test->elems[idx_last_elem]->dir_exit != new_elem->dir_enter)
            return 0;
        // In the first diag I add an element acrobatic front, transition back and acrobatic in the first four positions
        if(n_diag == 0) {
            if(diag_1_cond_completed == 0) {
                if(idx_last_elem == 0 && diag_test->elems[0]->type == 0 && new_elem->type > 0) {
                    // Caso trans e poi acr
                    update_acr_type_added = 1;
                }
                // Try to add next acr
                else if(new_elem->type > 0) {
                    update_diag_1_cond_completed = 1;
                    if(new_elem->type != diag_test->elems[idx_last_elem]->type)
                        update_both_acr_type = 1;
                }
                else {
                    return 0;
                }
            }
            else {
                if(new_elem->type > 0 && new_elem->type != acr_type_added)
                    update_both_acr_type = 1;
            }
        }
        else {
            if(idx_last_elem == 0 && diag_test->elems[0]->type == 0 && new_elem->type == 0) {
                return 0;
            }
            else {
                if(idx_last_elem == 0 && diag_test->elems[0]->type == 0 && new_elem->type > 0) {
                    if(both_acr_type != 1) {
                        if(new_elem->type == acr_type_added) {
                            return 0;
                        }
                        update_both_acr_type = 1;
                    } 
                }
            }
        }
    }
    else {
        // Prec must be 0 and dir enter 1
        if(new_elem->prec == 1 || new_elem->dir_enter == 0) 
            return 0;
        /*if(new_elem->dir_exit == 0 && check_diag_1_opt == 1)
            return 0;
        if(new_elem->dir_exit == 1 && check_diag_1_opt == 2)
            return 0;*/
        if(n_diag == 0) {
            update_acr_type_added = 1;
            if(add_trans_in_first == 0 && new_elem->type == 0)
                return 0;
        }
        else {
            if(add_trans_in_first == 0 && new_elem->type == 0)
                return 0;
            if(both_acr_type != 1) {
                if(new_elem->type == acr_type_added) {
                    return 0;
                }
            }
            if(new_elem->type == 0 && acr_type_added == 2) {
                // Add a front back transition
                if(new_elem->dir_exit != 0)
                    return 0;
            }
            
        }
        
    }
    if(checkNewDifficulty(diag_test, new_elem, dd, dp, diff_diag_before, n_diag) == 1) {
        if(update_acr_type_added == 1) {
            acr_type_added = new_elem->type;
        }
        if(update_both_acr_type == 1) {
            both_acr_type = 1;
        }
        if(update_diag_1_cond_completed == 1) {
            diag_1_cond_completed = 1;
        }
        return 1;
    }
        
    return 0;
}



int checkNewDifficulty(Diag * diag_test, Elem * new_elem, int dd, int dp, int diff_before_diag, int n_diag) {
    // Calculate the new difficulty and, if it is acceptable, the function updates it
    int new_difficulty_for_last_diag = diag_test->difficulty + new_elem->difficulty;

    if(new_difficulty_for_last_diag <= dd) {
        //printf("%d\n", diag_test->difficulty);
        if(n_diag != 2) {
            if(new_difficulty_for_last_diag + diff_before_diag < dp) {
                diag_test->difficulty = new_difficulty_for_last_diag;
                return 1;
            }   
                
        }
        else {
            if(new_difficulty_for_last_diag + diff_before_diag <= dp) {
                diag_test->difficulty = new_difficulty_for_last_diag;
                return 1;
            }
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

void calculateScore(Sequence * sequence) {
    float score = 0;
    for(int i = 0; i < 3; i++) {
        float score_to_add = 0;
        for(int j=0; j < (*sequence).diags[i].nElem; j++) {
            score_to_add+=(*sequence).diags[i].elems[j]->score;
        }
        if((*sequence).diags[i].elems[(*sequence).diags[i].nElem - 1]->final == 1 && (*sequence).diags[i].elems[(*sequence).diags[i].nElem - 1]->difficulty >= 8) {
            score_to_add*=1.5;
        }
        score +=score_to_add;
    }
    (*sequence).score_tot = score;
}

