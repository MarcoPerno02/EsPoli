#ifndef PERSON_H_DEFINED
#define PERSON_H_DEFINED
#include <stdio.h>
#include <stdlib.h>
#include "activity.h"

typedef struct person_wrapper_s * Person_Wrapper;
Person_Wrapper PERSONLoad(FILE * fin);
int ** PERSONBuildMat(FILE * fin, Person_Wrapper p_wrapper);
void PERSONFree(Person_Wrapper p_wrapper, int ** mat);
void ReadFileSol(FILE *fin, Person_Wrapper p_wrapper, Activity_Wrapper a_wrapper, int **mat);
void FindBestSol(Person_Wrapper p_wrapper,  Activity_Wrapper a_wrapper, int ** mat);
#endif
