#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int finish;
    int duration;
} Activity;

void loadActivities(Activity ** activities, int *N);
void buildSol(Activity * activities, int N);
void printSol(Activity * activities, int N, int * idx_prec, int pos);

int main() {
    Activity * activities;
    int N;
    loadActivities(&activities, &N);
    buildSol(activities, N);
    free(activities);
}

void loadActivities(Activity ** activities, int *N) {
    FILE *fin;
    if((fin = fopen("att1.txt", "r")) == NULL) {
        printf("Errore apertura file");
        exit(-1);
    }
    fscanf(fin, "%d", N);
    *activities = malloc(sizeof(Activity)* *N);
    if(*activities == NULL) exit(-1);
    for(int i = 0; i < *N; i++) {
        fscanf(fin, "%d %d", &(*activities)[i].start, &(*activities)[i].finish);
        (*activities)[i].duration = (*activities)[i].finish - (*activities)[i].start;
    }
    fclose(fin);
}

void buildSol(Activity * activities, int N) {
    int durations[N];
    int idx_prec[N];
    durations[0] = activities[0].duration;
    idx_prec[0] = -1;
    int idx_sum_max = -1;
    int sum_max = -1;
    for(int i = 1; i < N; i++) {
        int tmp_sum_max = 0;
        int tmp_idx_prec = -1;
        for(int j = 0; j < i; j++) {
            // Condition no intersecation
            if(activities[j].start >= activities[i].finish || activities[i].start >= activities[j].finish) {
                if(durations[j] + activities[i].duration > tmp_sum_max) {
                    tmp_sum_max = durations[j] + activities[i].duration;
                    tmp_idx_prec = j;
                }
            }
        }
        durations[i] = tmp_sum_max;
        idx_prec[i] = tmp_idx_prec;
        if(tmp_sum_max > sum_max) {
            sum_max = tmp_sum_max;
            idx_sum_max = i;
        }
    }
    printSol(activities, N, idx_prec, idx_sum_max);
}

void printSol(Activity * activities, int N, int * idx_prec, int pos) {
    if(pos == -1) {
        printf("Una soluzione possibile è: ");
    }
    else {
        int new_pos;
        new_pos = idx_prec[pos];
        printSol(activities, N, idx_prec, new_pos);
        printf("(%d, %d) ", activities[pos].start, activities[pos].finish);
    }
}