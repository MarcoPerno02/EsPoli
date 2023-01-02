#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stock.h"
#include "../BSTQuote/BSTQuote.h"

struct stock_s {
    char cod[20+1];
    BSTQuote BSTQuote;
};


Stock StockInit() {
    Stock stock = malloc(sizeof(struct stock_s));
    stock->BSTQuote = NULL;
    return stock;
}

void StockFree(Stock stock) {
    BSTQuotefree(stock->BSTQuote);
    free(stock);
}

char * StockGetCod(Stock stock) {
    return stock->cod;
}

void StockLoad(FILE * f, Stock stock, char * cod) {
    strcpy(stock->cod, cod);
    if(stock->BSTQuote == NULL)
        stock->BSTQuote = BSTQuoteinit();
    BSTQuoteInsert(f, stock->BSTQuote);
}
