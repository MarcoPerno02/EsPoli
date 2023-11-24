#ifndef SKILIFT_H_DEFINED
#define SKILIFT_H_DEFINED
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char id[11];
    int interval;
} Skilift;

typedef struct {
    int N;
    int Max_N;
    Skilift * array;
} SKiliftArray;

SKiliftArray * SKILIFTLoad(FILE * fin);
Skilift * SKILIFTSearchById(SKiliftArray * S, char * id);
void SKILIFTFree(SKiliftArray * S);

#endif