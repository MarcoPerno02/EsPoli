#include <stdio.h>
#include <stdlib.h>

typedef struct stock_s * Stock;

Stock StockInit();
void StockFree(Stock stock);
void StockLoad(FILE * f, Stock stock);