#include <stdio.h>
#include <stdlib.h>

typedef struct stockList_s * StockList;

StockList StockListinit();
void StockListFree(StockList list);
void StockListLoad(FILE * f, StockList list);