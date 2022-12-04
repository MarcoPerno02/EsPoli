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
    Diag * diags[3];
    int difficulty_tot;
    float score_tot;
} Sequence;

int loadElems(Elem ** elems);
void findBestSequence(Elem * elems, int N_elems);
void loadDiags(Diag ** diags, int * cont, int * LIM_DIM_DIAGS, Diag * diag_test, int pos, int dd, int dp, int lim_powerset, Elem * elems, int N_elems);
void combDiags(Diag * diags, int N_diags, int pos, int start, Sequence * sol, Sequence * solmax, int dd, int dp);
int checkAcceptabilitySolution(Sequence * sequence_test, int dd, int dp, Sequence * sequence_max);
int checkAcceptabilityNewElem(Diag * diag_test, int idx_last_elem, Elem * new_elem, int dd);
int checkAcceptabilityDiag(Diag ** diags, int * cont, int * LIM_DIM_DIAGS, Diag * diag_test, int dd, int lim_powerset);
int checkNewDifficulty(Diag * diag_test, Elem * new_elem, int dd);
void printElem(Elem * elem);
void printSequence(Sequence * sequence, int format);
void checkSequence(Sequence * sequence);
void calculateScore(Diag * diag, int n_diag);
int checkPresenceOfAnAcrobaticElementInTheDiag(Diag * diag);
void printDiag(Diag * diag);

int main() {
    Elem * elems;
    int N_elems = loadElems(&elems);
    findBestSequence(elems, N_elems);
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
        (*elems)[i].id = i;
    }
    fclose(fin);
    return N_elems;
}

void findBestSequence(Elem * elems, int N_elems) {
    FILE * fin;
    if((fin = fopen("testset.txt", "r")) == NULL) exit(-1);
    Sequence sequence_max;
    sequence_max.difficulty_tot = -1;
    sequence_max.score_tot = -1.0;
    Sequence sequence_test;
    sequence_test.difficulty_tot = 0;
    int n;
    fscanf(fin, "%d", &n);
    for(int i = 0; i < n; i++) {
        int dd, dp;
        fscanf(fin, "%d %d", &dd, &dp);
        Diag * diags = malloc(sizeof(Diag) * 10);
        Diag diag_test;
        int LIM_DIM_DIAGS = 10;
        int N_diags = 0;
        for(int lim_powerset = 1; lim_powerset <= 5; lim_powerset++) {
            loadDiags(&diags, &N_diags, &LIM_DIM_DIAGS, &diag_test, 0, dd, dp, lim_powerset, elems, N_elems);
        }
        Sequence solmax;
        solmax.score_tot = -1;
        Sequence sol;
        combDiags(diags, N_diags, 0, 0, &sol, &solmax, dd, dp);
        printf("\n\n\n\n\nSequennceMax:\n");
        printSequence(&solmax, 1);
        free(diags);
    }
    fclose(fin);
}

void loadDiags(Diag ** diags, int * cont, int * LIM_DIM_DIAGS, Diag * diag_test, int pos, int dd, int dp, int lim_powerset, Elem * elems, int N_elems) {
    if(pos == lim_powerset) {
        int ris = checkAcceptabilityDiag(diags, cont, LIM_DIM_DIAGS, diag_test, dd, lim_powerset);
    }
    else {
        int check_new_elem_addded = 0;
        for(int i = 0; i < N_elems; i++) {
            if(pos == 0) {
                diag_test->nElem = 0;
                diag_test->difficulty = 0;
            }
            int last_difficulty = diag_test->difficulty;
            int ris = checkAcceptabilityNewElem(diag_test, pos-1, &(elems[i]), dd);
            //if(diag_test->nElem > 5) {
            //    printf("ss");
            //}
            //if(diag_test->nElem == 1 && diag_test->elems[0]->id == 4 && i == 14) {
            //    printf("AA");
            //}
            if(ris == 1) {
                check_new_elem_addded = 1;
                diag_test->elems[pos] = &elems[i];
                //if(diag_test->nElem > 5) {
                //    printf("ss");
                //}
                diag_test->nElem++;

                // Check no more space available for the current diag or the a final elem has been inserted
                //printSequence(sequence_test);
                if(pos + 1 == lim_powerset ) {
                    if(checkPresenceOfAnAcrobaticElementInTheDiag(diag_test) == 1)
                    {
                        loadDiags(diags, cont, LIM_DIM_DIAGS, diag_test, pos+1, dd, dp, lim_powerset, elems, N_elems);
                    }
                }
                else if(elems[i].final == 1 && pos + 1 != lim_powerset) {

                }
                else {
                    loadDiags(diags, cont, LIM_DIM_DIAGS, diag_test, pos+1, dd, dp, lim_powerset, elems, N_elems);
                }
                diag_test->elems[pos] = NULL;
                diag_test->nElem--;
                diag_test->difficulty = last_difficulty;
            }
        }
        if(check_new_elem_addded == 0) {
            loadDiags(diags, cont, LIM_DIM_DIAGS, diag_test, lim_powerset, dd, dp, lim_powerset, elems, N_elems);
        }
    }
}

void combDiags(Diag * diags, int N_diags, int pos, int start, Sequence * sol, Sequence  *solmax, int dd, int dp) {
    if(pos == 3) {
        int ris = checkAcceptabilitySolution(sol, dd, dp, solmax);
    }
    else {
        for(int i = start; i < N_diags; i++) {
            /*if(pos == 0 && i == 0) {
                printf("");
            }
            if(pos == 1 && i == 17) {
                printf("");
            }
            if(pos == 2 && i == 29) {
                printf("");
            }*/
            sol->diags[pos] = &diags[i];
            int diff_now = 0;
            for(int j = 0; j <= pos; j++) {
                diff_now += sol->diags[j]->difficulty;
            }
            if(diff_now <= dp)
                combDiags(diags, N_diags, pos + 1, start, sol, solmax, dd, dp);
            start++;
        }
    }
}

int checkAcceptabilityNewElem(Diag * diag_test, int idx_last_elem, Elem * new_elem, int dd) {
    // Returns 1 if is okay, otherwise 0
    // Check if the new elem has the same entry of the last one
    //printElem(new_elem);
    if(diag_test->nElem != 0) {
        if(diag_test->elems[idx_last_elem]->dir_exit != new_elem->dir_enter) 
            return 0;
    }
    else {
        // Prec must be 0 and dir enter 1
        if(new_elem->prec == 1 || new_elem->dir_enter == 0) 
            return 0;
    }
    if(checkNewDifficulty(diag_test, new_elem, dd) == 1) 
        return 1;
    return 0;
}

int checkAcceptabilityDiag(Diag ** diags, int * cont, int * LIM_DIM_DIAGS, Diag * diag_test, int dd, int lim_powerset) {
    // Returns 1 if is okay, otherwise 0
    int i = 0;
    if(diag_test->nElem == 0 || diag_test->nElem != lim_powerset) return 0;
    //printDiag(diag_test);
    if(diag_test->difficulty <= dd) {
        if(diag_test->nElem == 2 && diag_test->elems[0]->id == 4 && diag_test->elems[1]->id == 5 )
            printf("");
        if(diag_test->nElem == 3 && diag_test->elems[0]->id == 1 && diag_test->elems[1]->id == 18 && diag_test->elems[2]->id == 4)
            printf("");
        //printDiag(diag_test);
        diag_test->id = *cont;
        (*diags)[*cont] = *diag_test;
        *cont += 1;
        if(*cont == (*LIM_DIM_DIAGS) - 1) {
            *LIM_DIM_DIAGS *= 2;
            (*diags) = realloc(*diags, sizeof(Diag) * *LIM_DIM_DIAGS);
            if((*diags) == NULL)
                printf("sdsds");
        }
            
    }
}

int checkNewDifficulty(Diag * diag_test, Elem * new_elem, int dd) {
    // Calculate the new difficulty and, if it is acceptable, the function updates it
    int new_difficulty_for_last_diag = diag_test->difficulty + new_elem->difficulty;

    if(new_difficulty_for_last_diag <= dd) {
        //printf("%d\n", diag_test->difficulty);
        diag_test->difficulty = new_difficulty_for_last_diag;
        return 1;
    }
    else {
        return 0;
    }
}

void printElem(Elem * elem) {
    printf("Name: %s\nType (1 back, 2 front): %d\nDir_enter (0 back, 1 front): %d\nDir_exit (0 back, 1 front): %d\nPrec: %d\nFinal: %d\nScore: %f\nDifficulty: %d\n-------------\n", elem->name, elem->type, elem->dir_enter, elem->dir_exit, elem->prec, elem->final, elem->score, elem->difficulty);
}

void printSequence(Sequence * sequence, int format) {
    printf("Score_tot: %f\n", sequence->score_tot);
    if(format == 1) {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < sequence->diags[i]->nElem; j++) {
                printf("%s ", sequence->diags[i]->elems[j]->name);
                //printElem(sequence->diags[i]->elems[j]);
            }
            printf(" | ");
        }
        printf("\n");
    }
    else {
        for(int i = 0; i < 3; i++) {
            printf("_");
            for(int j = 0; j < sequence->diags[i]->nElem; j++) {
                printf("___");
            }
            printf("_  ");
        }
        printf("\n");
        for(int i = 0; i < 3; i++) {
            printf("|");
            for(int j = 0; j < sequence->diags[i]->nElem; j++) {
                printf(" %d ", sequence->diags[i]->elems[j]->id);
            }
            printf(" | ");
        }
        printf("\n");
        for(int i = 0; i < 3; i++) {
            printf("|");
            for(int j = 0; j < sequence->diags[i]->nElem; j++) {
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
            for(int j = 0; j < sequence->diags[i]->nElem && ok == 1; j++) {
                if(sequence->diags[i]->elems[j]->id != id_matrix[i][j]) {
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

int checkPresenceOfAnAcrobaticElementInTheDiag(Diag * diag) {
    int ok = 0, i = 0;
    while(ok == 0 && i != diag->nElem && ok == 0) {
        if(diag->elems[i]->type > 0)
            ok = 1;
        i++;
    }
    return ok;
}

int checkAcceptabilitySolution(Sequence * sequence_test, int dd, int dp, Sequence * sequence_max) {
    // Returns 1 if is okay, otherwise 0
    int checkBack = 0, checkFront = 0, finish = 0, n_diag = 0, checkSequenceOfTwoAcrobaticElemnts = 0, i = 0;
    while(i != 3) {
        if(sequence_test->diags[i]->nElem == 0) return 1;
        i++;
    }
    i = 0;
    while((checkBack == 0 || checkFront == 0 || checkSequenceOfTwoAcrobaticElemnts == 0) && finish == 0) {
        if(sequence_test->diags[n_diag]->elems[i]->type == 1)
            checkBack = 1;
        else if(sequence_test->diags[n_diag]->elems[i]->type == 2)
            checkFront = 1;
        if(i > 0) {
            if(sequence_test->diags[n_diag]->elems[i]->type > 0 && sequence_test->diags[n_diag]->elems[i-1]->type > 0)
                checkSequenceOfTwoAcrobaticElemnts = 1;
        }
        if(sequence_test->diags[n_diag]->nElem == i + 1) {
            if(n_diag == 2) {
                finish = 1;
            }   
            else {
                n_diag++;
                i = 0;
            }
        }
        else {
            i++;
        }
        
    }
    //printSequence(sequence_test, 0);
    sequence_test->difficulty_tot = sequence_test->diags[0]->difficulty + sequence_test->diags[1]->difficulty+ sequence_test->diags[2]->difficulty;
    if(checkBack == 1 && checkFront == 1 && checkSequenceOfTwoAcrobaticElemnts == 1 && sequence_test->difficulty_tot <= dp) {
        sequence_test->score_tot = 0;
        int idx_max_final_score = -1;
        float max_final_score = -1;
        for(int k = 0; k < 3; k++) {
            calculateScore(sequence_test->diags[k], k);
            sequence_test->score_tot+=sequence_test->diags[k]->score;
            if(sequence_test->diags[k]->elems[sequence_test->diags[k]->nElem - 1]->difficulty >= 8 && sequence_test->diags[k]->elems[sequence_test->diags[k]->nElem - 1]->score > max_final_score) {
                idx_max_final_score = k;
                max_final_score = sequence_test->diags[k]->elems[sequence_test->diags[k]->nElem - 1]->score;
            }
        }
        if(max_final_score != -1) {
            sequence_test->score_tot += sequence_test->diags[idx_max_final_score]->score * 0.5; // Bonus 1.5 for the best diag
        }
        //if(j + 1 == diag->nElem && diag->elems[j]->difficulty >= 8 && n_diag == 2) {
        //    score_to_add *= 1.5;
        //}
        if(sequence_test->score_tot > sequence_max->score_tot) {
        //printSequence(sequence_test, 0);
            *sequence_max = *sequence_test;
            //printSequence(sequence_max, 0);
        }   
    }
}