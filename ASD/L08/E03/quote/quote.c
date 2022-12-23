#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quote.h"


Quote QuoteInit() {
    Quote quote = malloc(sizeof(struct quote_s));
    return quote;
}

Quote QuoteSetNull() {
    Quote quote = malloc(sizeof(struct quote_s));
    return quote;
}

void QuoteFree(Quote quote) {
    DATEFree(quote->date);
    free(quote);
}