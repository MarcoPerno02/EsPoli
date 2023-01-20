#ifndef BSTDAILYQUOTE_H_DEFINED
#define BSTDAILYQUOTE_H_DEFINED
#include <stdio.h>
#include <stdlib.h>
#include "../date/date.h"

typedef struct BSTDailyQuote_s * BSTDailyQuote;
typedef struct dailyQuote_s * DailyQuote;
struct dailyQuote_s {
    struct date_s date;
    float quote;
    float n;
    int sum;
};

BSTDailyQuote BSTDailyQuoteinit();
void BSTDailyQuoteInsert(FILE * f, BSTDailyQuote bst);
void BSTDailyQuotefree(BSTDailyQuote bst);
DailyQuote BSTDailyQuoteSearchForDate(BSTDailyQuote bst, struct date_s date);
void BSTDailyQuoteSearchMaxAndMin(BSTDailyQuote bst, Date start_date, Date finish_date, float * max, float * min);
void BSTDailyQuotebalance(BSTDailyQuote bst);
#endif