#ifndef BSTQUOTE_H_DEFINED
#define BSTQUOTE_H_DEFINED
#include <stdio.h>
#include <stdlib.h>
#include "../date/date.h"
#include "../quote/quote.h"

typedef struct BSTQuote_s * BSTQuote;
typedef struct dailyQuote_s * DailyQuote;
struct dailyQuote_s {
    struct date_s date;
    float quote;
};

//typedef struct BSTQuoteNodeContainer_s * linkBSTQuoteContainer;
//struct BSTQuoteNodeContainer_s {
//    BSTQuote BSTQuote;
//    Date date;
//    linkBSTQuoteContainer next;
//};

//typedef struct BSTQuoteListContainer_s * BSTQuoteListContainer;
//struct BSTQuoteListContainer_s {
//    linkBSTQuoteContainer head;
//    linkBSTQuoteContainer tail;
//    int N;
//};



//BSTQuoteListContainer BSTQuoteListContainerInit();
//void BSTQuoteListContainerFree(BSTQuoteListContainer list);
//void BSTQuoteListContainerInsert(FILE * f, BSTQuoteListContainer list);
BSTQuote BSTQuoteinit();
void BSTQuoteInsert(FILE * f, BSTQuote bst);
void BSTQuotefree(BSTQuote bst);
Quote BSTQuoteSearchForDate(BSTQuote bst, struct date_s date);
void BSTQuoteSearchMaxAndMin(BSTQuote bst, Date start_date, Date finish_date, int * max, int * min);
void BSTQuotebalance(BSTQuote bst);
#endif