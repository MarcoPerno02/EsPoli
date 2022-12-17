#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int finish;
    int duration_of_activity;
} Activity;

int loadActivities(Activity ** activities);
void attSel(int N, Activity *activities);
void addActivity(Activity *activities, int next_activity, int N_activities, Activity ** longest_combination, int * len_longest_combination, int * duration_longest_combination, Activity ** combination, int pos_combination);
int calculate_duration_combination(Activity ** activities, int N);
void cleanCombination(Activity ** activities, int N);
void printCombination(Activity ** activities, int N);
void terminationCase(Activity ** longest_combination, int * len_longest_combination, int * duration_longest_combination, Activity ** combination, int len_combination);

int main() {
    Activity * activities;
    int N = loadActivities(&activities);
    attSel(N, activities);
    free(activities);
}

int loadActivities(Activity ** activities) {
    FILE *fin;
    if((fin = fopen("att1.txt", "r")) == NULL) {
        printf("Errore apertura file");
        exit(-1);
    }
    int N;
    fscanf(fin, "%d", &N);
    *activities = malloc(N * sizeof(Activity));
    if(*activities == NULL) exit(-1);
    for(int i = 0; i < N; i++) {
        fscanf(fin, "%d %d", &((*activities)[i].start), &((*activities)[i].finish));
        (*activities)[i].duration_of_activity = (*activities)[i].finish - (*activities)[i].start;
    }
    fclose(fin);
    return N;
}

void attSel(int N, Activity *activities) {
    Activity ** longest_combination;
    longest_combination = (Activity **) malloc(N * sizeof(Activity *));
    if(longest_combination == NULL) exit(-1);
    cleanCombination(longest_combination, N);
    int len_longest_combination = -1; // It will contains the length of the longest combination
    int duration_longest_combination = -1; // It will contains the sum of the duration
    Activity ** combination;
    combination = (Activity **) malloc(N * sizeof(Activity *));
    if(combination == NULL) exit(-1);
    for(int i = 0; i < N; i++) {
        cleanCombination(combination, N);
        combination[0] = &(activities[i]);
        addActivity(activities, i+1, N, longest_combination, &len_longest_combination, &duration_longest_combination, combination, 1);
    }
    printf("Duration_longest_combination: %d\n", duration_longest_combination);
    printCombination(longest_combination, len_longest_combination);
    free(combination);
    free(longest_combination);
}

void addActivity(Activity *activities, int next_activity, int N_activities, Activity ** longest_combination, int * len_longest_combination, int * duration_longest_combination, Activity ** combination, int pos_combination) {
    if(next_activity == N_activities) {
        // Terminal case
        terminationCase(longest_combination, len_longest_combination, duration_longest_combination, combination, pos_combination);
    }
    else {
        int possible_paths = 0;
        for(int i = next_activity; i < N_activities; i++) {
            // Condition no intersecation
            if((*combination[pos_combination-1]).start >= activities[i].finish || activities[i].start >= (*combination[pos_combination-1]).finish) {
                possible_paths = 1;
                combination[pos_combination] = &(activities[i]);
                addActivity(activities, i+1, N_activities, longest_combination, len_longest_combination, duration_longest_combination, combination, pos_combination+1);
                combination[pos_combination] = NULL;
            }  
        }
        if(possible_paths == 0) {
            // Terminal case due to no possible activity to add
            terminationCase(longest_combination, len_longest_combination, duration_longest_combination, combination, pos_combination);
        }
    }
}

int calculate_duration_combination(Activity ** activities, int N) {
    int duration = 0;
    for(int i = 0; i < N; i++) {
        duration+=(*activities[i]).duration_of_activity;
    }
    return duration;
}

void cleanCombination(Activity ** activities, int N) {
    for(int i = 0; i < N; i++) {
        activities[i] = NULL;
    }
}

void printCombination(Activity ** activities, int N) {
    for(int i = 0; i < N; i++) {
        printf("(%d, %d) ", (*activities[i]).start, (*activities[i]).finish);
    }
    printf("\n");
}

void terminationCase(Activity ** longest_combination, int * len_longest_combination, int * duration_longest_combination, Activity ** combination, int len_combination) {
    int duration_test = calculate_duration_combination(combination, len_combination);
    printCombination(combination, len_combination);
    if(duration_test > *duration_longest_combination) {
        *duration_longest_combination = duration_test;
        *len_longest_combination = len_combination;
        for(int i = 0; i < len_combination; i++) {
            longest_combination[i] = combination[i];
        }
    }
}