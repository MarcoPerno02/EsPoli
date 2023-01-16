#ifndef ST_H_DEFINED
#define ST_H_DEFINED
#include <stdio.h>
#include <stdlib.h>

typedef struct st_s* ST;
struct st_s {
    char **name;
    int N;
};


ST STLoad(FILE *fin);
void STFree();
#endif