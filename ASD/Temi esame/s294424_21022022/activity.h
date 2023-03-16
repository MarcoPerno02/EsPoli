#ifndef ACTIVITY_H_DEFINED
#define ACTIVITY_H_DEFINED
#include <stdio.h>
#include <stdlib.h>

typedef struct activity_wrapper_s * Activity_Wrapper;
typedef struct {
    int id; //corrispondenza id pos per sicurezza
    int diff; // conteiene esperienza necessaria per incarico
} Activity;
struct activity_wrapper_s {
    int N;
    Activity * vett;
};

Activity_Wrapper ACTIVITYLoad(FILE * fin);
void ACTIVITYFree(Activity_Wrapper a_wrapper);

#endif