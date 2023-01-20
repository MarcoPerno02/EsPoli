#ifndef STOCKLIST_H_DEFINED
#define STOCKLIST_H_DEFINED
#include <stdio.h>
#include <stdlib.h>
#include "../stock/stock.h"

typedef struct stockList_s * StockList;
typedef struct nodeStockList * linkNodeStock;

StockList StockListinit();
void StockListFree(StockList list);
void StockListLoad(FILE * f, StockList list);
Stock StockListSearchByCodStockVersion(StockList list, char * cod);
#endif
