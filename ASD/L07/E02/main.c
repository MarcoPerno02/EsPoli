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
    float difficulty;
} Diag;

typedef struct
{
    Diag diags[3];
    float difficulty_tot;
    float score_tot;
} Sequence;

int loadElems(Elem ** elems);
void findBestSequence(Elem * elems, int N_elems);
void dispRip(Sequence * sequence_test, int n_diag, int pos, Elem * elems, int N_elems, Sequence * sequence_max, int dd, int dp, int lim_powerset);
int checkAcceptabilityNewElem(Sequence * sequence_test, int n_diag, int idx_last_elem, Elem * new_elem, int dd, int dp);
int checkAcceptabilitySolution(Sequence * sequence_test, int dd, int dp, Sequence * sequence_max);
int checkNewDifficulty(Sequence * sequence_test, int n_diag, Elem * new_elem, int dd, int dp);
void printElem(Elem * elem);
void printSequence(Sequence * sequence, int format);
void checkSequence(Sequence * sequence);
void calculateScore(Sequence * sequence);
int checkPresenceOfAnAcrobaticElementInTheDiag(Diag * diag);

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
        for(int lim_powerset = 1; lim_powerset <= 5; lim_powerset++)
            dispRip(&sequence_test, 0, 0, elems, N_elems, &sequence_max, dd, dp, lim_powerset);
        printf("\n\n\n\n\nSequennceMax:\n");
        printSequence(&sequence_max, 0);
    }
    fclose(fin);
}

void dispRip(Sequence * sequence_test, int n_diag, int pos, Elem * elems, int N_elems, Sequence * sequence_max, int dd, int dp, int lim_powerset) {
    //if(n_diag == 1)
    //    printf("ASA");
    if(n_diag == 3) {
        // Final case
        //printSequence(sequence_test);
        int ris = checkAcceptabilitySolution(sequence_test, dd, dp, sequence_max);
    }
    else {
        int check_new_elem_addded = 0;
        float last_difficulty = sequence_test->diags[n_diag].difficulty; 
        for(int i = 0; i < N_elems; i++) {
            if(pos == 0 && n_diag == 0) {
                sequence_test->diags[0].nElem = 0;
                sequence_test->diags[1].nElem = 0;
                sequence_test->diags[2].nElem = 0;
                sequence_test->difficulty_tot = 0;
                sequence_test->score_tot = 0;
            }
            
            //if(n_diag == 1 && sequence_test->diags[1].nElem == 1 && sequence_test->diags[0].elems[0]->id == 4 && sequence_test->diags[1].elems[0]->id == 4 && lim_powerset == 2 && i == 5){
            //    printf("");
            //}
            //if(n_diag == 2 && lim_powerset == 2 && sequence_test->diags[1].nElem == 2 && sequence_test->diags[0].elems[0]->id == 1 && sequence_test->diags[1].elems[0]->id == 1 && sequence_test->diags[1].elems[1]->id == 2) {
            //    printf("");
            //}
                
            int ris = checkAcceptabilityNewElem(sequence_test, n_diag, pos-1, &(elems[i]), dd, dp);
            if(ris == 1) {
                //if(n_diag == 2) {
                //    if(sequence_test->diags[2].nElem < 0 || sequence_test->diags[2].nElem > 5)
                //        printf("");
                //}
                    
                //printf("N_diag: %d Pos: %d idx_el: %d\n", n_diag, pos, i);
                check_new_elem_addded = 1;
                sequence_test->diags[n_diag].elems[pos] = &elems[i];
                sequence_test->diags[n_diag].nElem++;

                // Check no more space available for the current diag or the a final elem has been inserted
                //printSequence(sequence_test);
                if(pos + 1 == lim_powerset || elems[i].final == 1) {
                    if(checkPresenceOfAnAcrobaticElementInTheDiag(&(sequence_test->diags[n_diag])) == 1)
                    {
                        if(n_diag+1 == 3) {
                            // Final case
                            dispRip(sequence_test, n_diag+1, 0, elems, N_elems, sequence_max, dd, dp, lim_powerset);
                        }
                        else {
                            for(int lim_powerset = 1; lim_powerset <= 5; lim_powerset++) {
                                dispRip(sequence_test, n_diag+1, 0, elems, N_elems, sequence_max, dd, dp, lim_powerset);
                            }
                        }
                    }
                }
                else {
                    dispRip(sequence_test, n_diag, pos+1, elems, N_elems, sequence_max, dd, dp, lim_powerset);
                }

                sequence_test->diags[n_diag].elems[pos] = NULL;
                sequence_test->diags[n_diag].nElem--;
                sequence_test->diags[n_diag].difficulty = last_difficulty;
            }
        }
        // If no elem was added to the current diag, pass to the next diag
        if(check_new_elem_addded == 0) {
            for(int lim_powerset = 1; lim_powerset <= 5; lim_powerset++) {
                dispRip(sequence_test, n_diag+1, 0, elems, N_elems, sequence_max, dd, dp, lim_powerset);
            }
        }
        
    }
}

int checkAcceptabilityNewElem(Sequence * sequence_test, int n_diag, int idx_last_elem, Elem * new_elem, int dd, int dp) {
    // Returns 1 if is okay, otherwise 0
    // Check if the new elem has the same entry of the last one
    //printElem(new_elem);
    if(sequence_test->diags[n_diag].nElem != 0) {
        if(sequence_test->diags[n_diag].elems[idx_last_elem]->dir_exit != new_elem->dir_enter) return 0;
    }
    else {
        // Prec must be 0 and dir enter 1
        if(new_elem->prec == 1 || new_elem->dir_enter == 0) return 0;
    }
    if(checkNewDifficulty(sequence_test, n_diag, new_elem, dd, dp) == 1) return 1;
    return 0;
}

int checkAcceptabilitySolution(Sequence * sequence_test, int dd, int dp, Sequence * sequence_max) {
    // Returns 1 if is okay, otherwise 0
    int checkBack = 0, checkFront = 0, finish = 0, n_diag = 0, checkSequenceOfTwoAcrobaticElemnts = 0, i = 0;
    while(i != 3) {
        if(sequence_test->diags[i].nElem == 0) return 1;
        i++;
    }
    i = 0;
    while((checkBack == 0 || checkFront == 0 || checkSequenceOfTwoAcrobaticElemnts == 0) && finish == 0) {
        if(sequence_test->diags[n_diag].elems[i]->type == 1)
            checkBack = 1;
        else if(sequence_test->diags[n_diag].elems[i]->type == 2)
            checkFront = 1;
        if(i > 0) {
            if(sequence_test->diags[n_diag].elems[i]->type > 0 && sequence_test->diags[n_diag].elems[i-1]->type > 0)
                checkSequenceOfTwoAcrobaticElemnts = 1;
        }
        if(sequence_test->diags[n_diag].nElem == i + 1) {
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
    if(checkBack == 1 && checkFront == 1 && checkSequenceOfTwoAcrobaticElemnts == 1 && sequence_test->difficulty_tot <= dp) {
        calculateScore(sequence_test);
        if(sequence_test->score_tot > sequence_max->score_tot) {
            *sequence_max = *sequence_test;
            printSequence(sequence_max, 0);
        }
            
    }
}

int checkNewDifficulty(Sequence * sequence_test, int n_diag, Elem * new_elem, int dd, int dp) {
    // Calculate the new difficulty and, if it is acceptable, the function updates it
    int difficulty = 0;
    for(int i = 0; i < n_diag; i++) {
        difficulty = difficulty + sequence_test->diags[i].difficulty;
    }
    int new_difficulty_for_last_diag = sequence_test->diags[n_diag].difficulty + new_elem->difficulty;

    if(difficulty + new_difficulty_for_last_diag <= dp && new_difficulty_for_last_diag <= dd) {
        sequence_test->diags[n_diag].difficulty = new_difficulty_for_last_diag;
        sequence_test->difficulty_tot = difficulty + new_difficulty_for_last_diag;
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
            for(int j = 0; j < sequence->diags[i].nElem; j++) {
                printElem(sequence->diags[i].elems[j]);
            }
        }
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
        for(int j = 0; j < sequence->diags[i].nElem; j++) {
            score_to_add += sequence->diags[i].elems[j]->score;
            if(j + 1 == sequence->diags[i].nElem && sequence->diags[i].elems[j]->difficulty >= 8 ) {
                score_to_add *= 1.5;
            }
        }
        score+=score_to_add;
    }
    sequence->score_tot = score;
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