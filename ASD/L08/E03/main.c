#include <stdio.h>
#include <stdlib.h>
#include "stockList/stockList.h"
#include "stock/stock.h"
#include "date/date.h"
#include "quote/quote.h"

int main() {
    StockList stockList = StockListinit();

    FILE * f = fopen("F1.txt", "r");
    if(f == NULL) exit(-1);
    StockListLoad(f, stockList);
    fclose(f);

    f = fopen("F2.txt", "r");
    if(f == NULL) exit(-1);
    StockListLoad(f, stockList);
    fclose(f);

    f = fopen("F3.txt", "r");
    if(f == NULL) exit(-1);
    StockListLoad(f, stockList);
    fclose(f);
    
    int choice;
    do {
        printf("Scelta: ");
        scanf("%d", &choice);
        if(choice == 1) {
            char cod [50+1];
            printf("Inserire codice: ");
            scanf("%s", cod);
            Stock stock = StockListSearchByCodStockVersion(stockList, cod);
            if(stock != NULL)
                printf("Trovato\n");
            else 
                printf("Non trovato\n");
        }
        else if(choice == 2) {
            char cod [50+1];
            printf("Inserire codice: ");
            scanf("%s", cod);
            Stock stock = StockListSearchByCodStockVersion(stockList, cod);
            if(stock != NULL) {
                printf("Inserisci data (YY/MM/DD hh:mi): ");
                int year, month, day, minute, hour;
                fscanf(stdin, "%d/%d/%d %d:%d", &year, &month, &day, &hour, &minute);
                struct date_s date_to_search = DATEInit(year, month, day, hour, minute);
                Quote quote = StockSearchForDate(stock, date_to_search);
                if(quote != NULL)
                    printf("Trovato\n");
                else
                    printf("Non trovato\n");
            }
            else 
                printf("Non trovato\n");
        }
        else if(choice == 3 || choice == 4) {
            char cod [50+1];
            printf("Inserire codice: ");
            scanf("%s", cod);
            Stock stock = StockListSearchByCodStockVersion(stockList, cod);
            if(stock != NULL) {
                StockSearchQuoteMaxAndMinInRange(stock, choice-3);
            }
            else {
                printf("Non trovato");
            }
        }
        else if(choice == 5) {
            char cod [50+1];
            printf("Inserire codice: ");
            scanf("%s", cod);
            Stock stock = StockListSearchByCodStockVersion(stockList, cod);
            if(stock != NULL) {
                StockBalanceBSTQuote(stock);
            }
            else {
                printf("Non trovato");
            }
        }
    } while(choice != 0);
    StockListFree(stockList);
}