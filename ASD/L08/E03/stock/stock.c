#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stock.h"
#include "../BSTQuote/BSTQuote.h"

struct stock_s {
    char cod[20+1];
    BSTQuoteListContainer BSTQuoteListContainer;
};


Stock StockInit() {
    Stock stock = malloc(sizeof(struct stock_s));
    stock->BSTQuoteListContainer = NULL;
    return stock;
}

void StockFree(Stock stock) {
    BSTQuoteListContainerFree(stock->BSTQuoteListContainer);
    free(stock);
}

char * StockGetCod(Stock stock) {
    return stock->cod;
}

void StockLoad(FILE * f, Stock stock, char * cod) {
    strcpy(stock->cod, cod);
    if(stock->BSTQuoteListContainer == NULL)
        stock->BSTQuoteListContainer = BSTQuoteListContainerInit();
    BSTQuoteListContainerInsert(f, stock->BSTQuoteListContainer);
}
