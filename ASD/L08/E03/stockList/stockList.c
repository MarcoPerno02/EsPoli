#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stockList.h"
#include "../stock/stock.h"

typedef struct nodeStockList * linkNodeStock;
struct nodeStockList {
    Stock stock;
    linkNodeStock next;
};

struct stockList_s {
    linkNodeStock head;
    linkNodeStock tail;
    int N;
};

StockList StockListinit() {
    StockList list = malloc(sizeof(struct stockList_s));
    list->head = NULL;
    list->tail = NULL;
    list->N = 0;
}

void StockListFree(StockList list) {
    linkNodeStock next;
    for(linkNodeStock x = list->head; x != NULL; x = next) {
        next = x->next;
        Stock stock = x->stock;
        StockFree(stock);
        free(x);
    }
    free(list);
}

linkNodeStock StockListNewNode() {
    linkNodeStock node = malloc(sizeof(struct nodeStockList));
    return node;
}

void StockListInsert(StockList list, linkNodeStock node) {

}


void StockListLoad(FILE * f, StockList list) {
    int num_of_stocks;
    fscanf(f, "%d", &num_of_stocks);
    for(int i = 0; i < num_of_stocks; i++) {
        linkNodeStock node = StockListNewNode();
        node->stock = StockInit();
        StockLoad(f, node->stock);
    }
}