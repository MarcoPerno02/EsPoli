#include <stdio.h>
#include <stdlib.h>
#include "stockList/stockList.h"

int main() {
    FILE * f = fopen("F1.txt", "r");
    if(f == NULL) exit(-1);
    
    StockList stockList = StockListinit();
    StockListLoad(f, stockList);

    fclose(f);
    StockListFree(stockList);
}