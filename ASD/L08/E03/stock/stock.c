#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stock.h"
#include "../BSTQuote/BSTQuote.h"
#include "../quote/quote.h"

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

Quote StockSearchForDate(Stock stock, struct date_s date) {
    Quote x = BSTQuoteSearchForDate(stock->BSTQuote, date);
    return x;
}


void StockSearchQuoteMaxAndMinInRange(Stock stock, int opt) {
    if(opt == 0) {
        int year, month, day, minute, hour;
        printf("Inserisici data inizio (YY/MM/DD hh:mi): ");
        fscanf(stdin, "%d/%d/%d %d:%d", &year, &month, &day, &hour, &minute);
        struct date_s start_date = DATEInit(year, month, day, hour, minute);
        printf("Inserisici data fine (YY/MM/DD hh:mi): ");
        fscanf(stdin, "%d/%d/%d %d:%d", &year, &month, &day, &hour, &minute);
        struct date_s finish_date = DATEInit(year, month, day, hour, minute);
        int max, min;
        BSTQuoteSearchMaxAndMin(stock->BSTQuote, &start_date, &finish_date, &max, &min);
        printf("Max: %d. Min: %d\n", max, min);
    }
    else {
        int max, min;
        BSTQuoteSearchMaxAndMin(stock->BSTQuote, NULL, NULL, &max, &min);
        printf("Max: %d. Min: %d\n", max, min);
    }
}

void StockBalanceBSTQuote(Stock stock) {
    BSTQuotebalance(stock->BSTQuote);
}