#include <stdio.h>
#include <stdlib.h>

typedef struct symboltable * ST;

ST STinit();
void STfree(ST st);
int STSearch(ST st, char * label);


