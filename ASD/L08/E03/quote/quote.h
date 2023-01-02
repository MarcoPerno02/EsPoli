#ifndef QUOTE_H_DEFINED
#define QUOTE_H_DEFINED
#include <stdio.h>
#include <stdlib.h>
#include "../date/date.h"

typedef struct quote_s * Quote;

struct quote_s {
    struct date_s date;
    float val;
    int qty;
};

Quote QuoteInit();
void QuoteFree(Quote quote);
Quote QuoteSetNull();
#endif