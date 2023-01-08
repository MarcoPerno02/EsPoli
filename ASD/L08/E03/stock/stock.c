#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stock.h"
#include "../BSTDailyQuote/BSTDailyQuote.h"

struct stock_s {
    char cod[20+1];
    BSTDailyQuote BSTDailyQuote;
};


Stock StockInit() {
    Stock stock = malloc(sizeof(struct stock_s));
    stock->BSTDailyQuote = NULL;
    return stock;
}

void StockFree(Stock stock) {
    BSTDailyQuotefree(stock->BSTDailyQuote);
    free(stock);
}

char * StockGetCod(Stock stock) {
    return stock->cod;
}

void StockLoad(FILE * f, Stock stock, char * cod) {
    strcpy(stock->cod, cod);
    if(stock->BSTDailyQuote == NULL)
        stock->BSTDailyQuote = BSTDailyQuoteinit();
    BSTDailyQuoteInsert(f, stock->BSTDailyQuote);
}

DailyQuote StockSearchForDate(Stock stock, struct date_s date) {
    DailyQuote x = BSTDailyQuoteSearchForDate(stock->BSTDailyQuote, date);
    return x;
}


void StockSearchQuoteMaxAndMinInRange(Stock stock, int opt) {
    if(opt == 0) {
        int year, month, day, minute, hour;
        printf("Inserisici data inizio (YY/MM/DD): ");
        fscanf(stdin, "%d/%d/%d", &year, &month, &day, &hour, &minute);
        struct date_s start_date = DATEInit(year, month, day, 0, 0);
        printf("Inserisici data fine (YY/MM/DD): ");
        fscanf(stdin, "%d/%d/%d", &year, &month, &day, &hour, &minute);
        struct date_s finish_date = DATEInit(year, month, day, 0, 0);
        float max, min;
        BSTDailyQuoteSearchMaxAndMin(stock->BSTDailyQuote, &start_date, &finish_date, &max, &min);
        printf("Max: %f. Min: %f\n", max, min);
    }
    else {
        float max, min;
        BSTDailyQuoteSearchMaxAndMin(stock->BSTDailyQuote, NULL, NULL, &max, &min);
        printf("Max: %f. Min: %f\n", max, min);
    }
}

void StockBalanceBSTDailyQuote(Stock stock) {
    BSTDailyQuotebalance(stock->BSTDailyQuote);
}