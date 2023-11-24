#ifndef ST_H_DEFINED
#define ST_H_DEFINED
#include <stdio.h>
#include <stdlib.h>

typedef struct st_s* ST;
typedef struct {
    char name[31];
} Item;
struct st_s {
    Item * vet;
    int N;
};

ST STInit(int v);
void STLoad(FILE *fin, ST st);
void STCopy(ST dest, ST source);
int STsearch(ST st, char * name);
char * STsearchByIndex(ST st, int id);
void STFree();
#endif