#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stock.h"
#include "../quoteBST/quoteBST.h"

struct stock_s {
    char cod[20+1];
    QuoteBSTListContainer quoteBSTListContainer;
};


Stock StockInit() {
    Stock stock = malloc(sizeof(struct stock_s));
    return stock;
}

void StockFree(Stock stock) {
    free(stock);
}

void StockLoad(FILE * f, Stock stock) {
    fscanf(f, "%s", stock->cod);
    stock->quoteBSTListContainer = BSTQuoteBSTListContainerInit();
    BSTQuoteBSTListContainerInsert(f, stock->quoteBSTListContainer);
}
