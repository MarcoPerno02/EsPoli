#include <stdio.h>
#include <stdlib.h>

typedef struct symboltable * ST;

ST STinit();
void STfree(ST st);
void STInsert(ST st, char * label);
int STSearchByLabel(ST st, char * label);
int STVertexCount(ST st);
char * STSearchById(ST st, int id);
