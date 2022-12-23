#include <stdio.h>
#include <stdlib.h>
#include "../date/date.h"

typedef struct quote_s * Quote;

struct quote_s {
    Date date;
    float val;
    int qty;
};

Quote QuoteInit();
void QuoteFree(Quote quote);
Quote QuoteSetNull();