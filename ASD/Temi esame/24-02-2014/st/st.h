#ifndef ST_H_DEFINED
#define ST_H_DEFINED
#include <stdio.h>
#include <stdlib.h>

typedef struct  {
    char name[21];
} Key_st;

typedef struct {
    int id;
    Key_st key;
} Item_st;

typedef struct st_s * ST;

ST STInit(int maxN);
void STFree(ST st);
void STInsert(ST st, Item_st item);
int STcount(ST st);
int STsearch(ST st, Key_st k);
Key_st STsearchByIndex (ST st, int id);

#endif