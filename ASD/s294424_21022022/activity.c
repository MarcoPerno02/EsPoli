#include <stdio.h>
#include <stdlib.h>
#include "activity.h"

//Activity wrapper andava fatto quasi adt per vedere contenuto da person ERRORE

Activity_Wrapper ACTIVITYLoad(FILE * fin) {
    int N;
    fscanf(fin, "%d", &(N));
    Activity_Wrapper a_wrapper = malloc(sizeof(struct activity_wrapper_s));
    a_wrapper->N = N;
    a_wrapper->vett = malloc(sizeof(Activity)* N);
    for(int i = 0; i < N; i++) {
        a_wrapper->vett[i].id = i;
        fscanf(fin, "%d", &(a_wrapper->vett[i].diff));
    }
    return a_wrapper;
}
void ACTIVITYFree(Activity_Wrapper a_wrapper) {
    free(a_wrapper->vett);
    free(a_wrapper);
}

