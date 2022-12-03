#include <stdio.h>
#include <stdlib.h>

typedef struct
{
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
    int score;
} Diag;

typedef struct
{
    Diag diags[3];
    float score_tot;
    int checkFront;
    int checkBack;
} Sequence;

int loadElems(Elem ** elems);
void findBestSequence(Elem * elems, int N_elems);
int dispRip(Sequence * sequence_test, int n_diag, int pos, Elem * elems, int N_elems, Sequence * sequence_max, float dd, float dp);
int checkAcceptabilityNewElem(Sequence * sequence_test, int n_diag, int idx_last_elem, Elem * new_elem, float dp);
int checkAcceptabilitySolution(Sequence * sequence_test, float dd, float dp);
float checkNewScore(Sequence * sequence_test, int n_diag, Elem * new_elem, int dp);

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
    }
    fclose(fin);
    return N_elems;
}

void findBestSequence(Elem * elems, int N_elems) {
    FILE * fin;
    if((fin = fopen("testset.txt", "r") == NULL)) exit(-1);
    Sequence sequence_max;
    sequence_max.score_tot = -1;
    Sequence sequence_test;
    sequence_test.score_tot = 0;
    int n;
    fscanf(fin, "%d", &n);
    for(int i = 0; i < n; i++) {
        float dd, dp;
        fscanf(fin, "%d %d", &dd, &dp);
        dispRip(&sequence_test, 0, 0, elems, N_elems, &sequence_max, dd, dp);

    }
}

int dispRip(Sequence * sequence_test, int n_diag, int pos, Elem * elems, int N_elems, Sequence * sequence_max, float dd, float dp) {
    if(n_diag == 3) {
        // Final case
        int ris = checkAcceptabilitySolution(sequence_test, dd, dp);
    }
    else {
        int check_new_elem_addded = 0;
        float last_score = sequence_test->diags[n_diag].score; 
        for(int i = 0; i < N_elems; i++) {
            if(pos == 0 && n_diag == 0) {
                sequence_test->checkBack = 0;
                sequence_test->checkFront = 0;
                sequence_test->diags[0].nElem = 0;
                sequence_test->diags[1].nElem = 0;
                sequence_test->diags[2].nElem = 0;
                sequence_test->score_tot = 0;
            }
            int ris = checkAcceptabilityNewElem(sequence_test, n_diag, pos-1, &(elems[i]), dp);
            sequence_test->diags[n_diag].elems[pos] = &elems[i];
            if(ris == 1) {
                check_new_elem_addded = 1;
                sequence_test->diags[n_diag].nElem++;
                sequence_test->diags[n_diag].score = checkNewScore(sequence_test, n_diag, &(elems[i]));
                if(elems[i].dir_enter == 0)
                    sequence_test->checkBack = 1;
                else 
                    sequence_test->checkFront = 1;

                // Check no more space available for the current diag or the a final elem has been inserted
                if(pos == 4 || elems[i].final == 1) {
                    n_diag++;
                    pos = 0;
                }

                dispRip(sequence_test, n_diag, pos, elems, N_elems, sequence_max, dd, dp);
                
                sequence_test->diags[n_diag].nElem--;
                sequence_test->diags[n_diag].score = last_score;
            }
        }
        // If no elem was added to the current diag, pass to the next diag
        if(check_new_elem_addded == 0) {
            n_diag++;
            pos = 0;
        }
    }
}

int checkAcceptabilityNewElem(Sequence * sequence_test, int n_diag, int idx_last_elem, Elem * new_elem, float dp) {
    // Returns the new_score if is okay, otherwise -1
    // Check if the new elem has the same entry of the last one
    if(sequence_test->diags[n_diag].nElem == 0) {
        if(sequence_test->diags[n_diag].elems[idx_last_elem]->dir_exit != new_elem->dir_enter) return -1;
    }
    float possible_score;
    possible_score = checkNewScore(sequence_test, n_diag, new_elem, dp);
    if(possible_score > dp) return -1;
    return possible_score;
}

int checkAcceptabilitySolution(Sequence * sequence_test, float dd, float dp) {
    // Returns 1 if is okay, otherwise 0
    if(sequence_test->checkBack == 1 && sequence_test->checkFront == 1 && sequence_test->score_tot >= dd && sequence_test->score_tot <= dp) {

    }
}

float checkNewScore(Sequence * sequence_test, int n_diag, Elem * new_elem, int dp) {
    // Calculate the new score and, if it is acceptable, the function updates it
    float score = 0;
    for(int i = 0; i < n_diag; i++) {
        score += sequence_test->diags[n_diag].score;
    }
    float new_score_for_last_diag = sequence_test->diags[n_diag].score + new_elem->score;
    if(new_elem->final == 1 && new_elem->score >= 8)
        new_score_for_last_diag *= 1.5;
    if(score + new_score_for_last_diag <= dp) {
        sequence_test->diags[n_diag].score = new_score_for_last_diag;
        sequence_test->score_tot = score + new_score_for_last_diag;
        return 1;
    }
    else {
        return 0;
    }
}