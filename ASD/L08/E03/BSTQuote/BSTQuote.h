#ifndef BSTQUOTE_H_DEFINED
#define BSTQUOTE_H_DEFINED
#include <stdio.h>
#include <stdlib.h>
#include "../date/date.h"

typedef struct BSTQuote_s * BSTQuote;

typedef struct BSTQuoteNodeContainer_s * linkBSTQuoteContainer;
struct BSTQuoteNodeContainer_s {
    BSTQuote BSTQuote;
    Date date;
    linkBSTQuoteContainer next;
};

typedef struct BSTQuoteListContainer_s * BSTQuoteListContainer;
struct BSTQuoteListContainer_s {
    linkBSTQuoteContainer head;
    linkBSTQuoteContainer tail;
    int N;
};


BSTQuoteListContainer BSTQuoteListContainerInit();
void BSTQuoteListContainerFree(BSTQuoteListContainer list);
void BSTQuoteListContainerInsert(FILE * f, BSTQuoteListContainer list);
#endif