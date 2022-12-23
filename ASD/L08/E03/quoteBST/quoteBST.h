#ifndef QUOTEBST_H_DEFINED
#define QUOTEBST_H_DEFINED
#include <stdio.h>
#include <stdlib.h>
#include "../date/date.h"

typedef struct quoteBST_s * QuoteBST;

typedef struct quoteBSTNodeContainer_s * linkQuoteBSTContainer;
struct quoteBSTNodeContainer_s {
    QuoteBST quoteBST;
    Date date;
    linkQuoteBSTContainer next;
};

typedef struct quoteBSTListContainer_s * QuoteBSTListContainer;
struct quoteBSTListContainer_s {
    linkQuoteBSTContainer head;
    linkQuoteBSTContainer tail;
    int N;
};


QuoteBSTListContainer BSTQuoteBSTListContainerInit();
void BSTQuoteBSTListContainerFree(QuoteBSTListContainer list);
void BSTQuoteBSTListContainerInsert(FILE * f, QuoteBSTListContainer list);
#endif