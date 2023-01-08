#ifndef STOCK_H_DEFINED
#define STOCK_H_DEFINED
#include <stdio.h>
#include <stdlib.h>
#include "../BSTDailyQuote/BSTDailyQuote.h"
#include "../date/date.h"

typedef struct stock_s * Stock;

Stock StockInit();
void StockFree(Stock stock);
void StockLoad(FILE * f, Stock stock, char * cod);
char * StockGetCod(Stock stock);
DailyQuote StockSearchForDate(Stock stock, struct date_s date);
void StockSearchQuoteMaxAndMinInRange(Stock stock, int opt);
void StockBalanceBSTDailyQuote(Stock stock);
#endif