#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BSTDailyQuote.h"



typedef struct node* link;
struct node {DailyQuote dailyQuote; link p;link l;link r;int N;};
struct BSTDailyQuote_s { link root; link z; };

static link NEW(DailyQuote quote, link p, link l, link r, int N)
{
    link x = malloc(sizeof *x);
    x->dailyQuote = quote;
    x->p = p;
    x->l = l;
    x->r = r;
    x->N = N;
    return x;
}



static void treeFree(link h, link z)
{
    if (h == z)
        return;
    free(h->dailyQuote);
    treeFree(h->l,z);
    treeFree(h->r, z);
    free(h);
}

void BSTDailyQuotefree(BSTDailyQuote bst)
{
    if (bst == NULL)
        return;
    treeFree(bst->root, bst->z);
    free(bst->z->dailyQuote);
    free(bst->z);
    free(bst);
}

void SearchMaxAndMin(link h, link z, Date start_date, Date finish_date, float * max, float * min) {
    if (h == z)
        return;
    SearchMaxAndMin(h->l, z, start_date, finish_date, max, min);
    if(start_date != NULL && finish_date != NULL) {
        if(h->dailyQuote->date.unix_time > finish_date->unix_time)
            return;
    }
    if(start_date == NULL || h->dailyQuote->date.unix_time >= start_date->unix_time) {
        if(h->dailyQuote->quote > *max)
            *max = h->dailyQuote->quote;
        if(h->dailyQuote->quote < * min) 
            *min = h->dailyQuote->quote;
        }
    SearchMaxAndMin(h->r, z, start_date, finish_date, max, min);

}

void BSTDailyQuoteSearchMaxAndMin(BSTDailyQuote bst, Date start_date, Date finish_date, float * max, float * min) {
    if (bst == NULL) {
        *max = 0;
        *min = 0;
        return;
    }
        
    *max = -9999999;
    *min = 9999999;
    SearchMaxAndMin(bst->root, bst->z, start_date, finish_date, max, min);
}


link insertR(link h, DailyQuote x, link z)
{
    if (h == z)
        return NEW(x, z, z, z, 1);
    if (x->date.unix_time < h->dailyQuote->date.unix_time)
    {
        h->l = insertR(h->l, x, z);
        h->l->p = h;
    }
    else
    {
        h->r = insertR(h->r, x, z);
        h->r->p = h;
    }
    (h->N)++;
    return h;
}

void BSTinsert_leafR(BSTDailyQuote bst, DailyQuote x)
{
    bst->root = insertR(bst->root, x, bst->z);
}

BSTDailyQuote BSTDailyQuoteinit()
{
    BSTDailyQuote bst = malloc(sizeof(struct BSTDailyQuote_s));
    DailyQuote dailyQuote = malloc(sizeof(struct dailyQuote_s));
    bst->root = (bst->z = NEW(dailyQuote, NULL, NULL, NULL, 0));
    return bst;
}

DailyQuote searchForDateR(link h, struct date_s k, link z) {
    if (h == z)
        return NULL;
    if(h->dailyQuote->date.unix_time == k.unix_time) {
        return h->dailyQuote;
    }
    if(k.unix_time < h->dailyQuote->date.unix_time)
        return searchForDateR(h->l, k, z);
    else 
        return searchForDateR(h->r, k, z);
}

link BSTDailyQuoteSearchForDateRPointerVerion(link h, struct date_s k, link z) {
    if (h == z)
        return NULL;
    if(h->dailyQuote->date.unix_time == k.unix_time) {
        return h;
    }
    if(k.unix_time < h->dailyQuote->date.unix_time)
        return BSTDailyQuoteSearchForDateRPointerVerion(h->l, k, z);
    else 
        return BSTDailyQuoteSearchForDateRPointerVerion(h->r, k, z);
}


DailyQuote BSTDailyQuoteSearchForDate(BSTDailyQuote bst, struct date_s date) {
    return searchForDateR(bst->root, date, bst->z);
}

void BSTDailyQuoteInsert(FILE * f, BSTDailyQuote bst) {
    int n_quote;
    fscanf(f, "%d", &n_quote);
    
    for(int i = 0; i < n_quote; i++) {
        // Iterate on each quote and add it the list of that day
        int year, month, day, minute, hour;
        fscanf(f, "%d/%d/%d %d:%d", &year, &month, &day, &hour, &minute);
        struct date_s date = DATEInit(year, month, day, 0, 0);
        float val;
        int qty;
        fscanf(f, "%f %d", &(val), &(qty));
        
        // Search if the dailyQuote for this date already exists
        link h = BSTDailyQuoteSearchForDateRPointerVerion(bst->root, date, bst->z);
        if(h == NULL){
            DailyQuote dailyQuote = malloc(sizeof(struct dailyQuote_s));
            dailyQuote->date = date;
            dailyQuote->n = qty;
            dailyQuote->quote = (float) val;
            dailyQuote->sum = (float) val *qty;
            BSTinsert_leafR(bst, dailyQuote);
        }
        else {
            h->dailyQuote->n += qty;
            h->dailyQuote->sum += (float) (val*qty);
            h->dailyQuote->quote = (float)  h->dailyQuote->sum / h->dailyQuote->n;
        }
        
        
    }
}

link rotL(link h)
{
    link x = h->r;
    h->r = x->l;
    x->l->p = h;
    x->l = h;
    x->p = h->p;
    h->p = x;
    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
    return x;
}

link rotR(link h)
{
    link x = h->l;
    h->l = x->r;
    x->r->p = h;
    x->r = h;
    x->p = h->p;
    h->p = x;
    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
    return x;
}

link partR(link h, int r)
{
    int t = h->l ->N;
    if (t > r)
    {
        h->l = partR(h->l, r);
        h = rotR(h);
    }
    if (t < r)
    {
        h->r = partR(h->r, r -t -1);
        h = rotL(h);
    }
    return h;
}

static link balanceR(link h, link z)
{
    int r;
    if (h == z)
        return z;
    r = (h->N + 1) / 2 - 1;
    h = partR(h, r);
    h->l = balanceR(h->l, z);
    h->r = balanceR(h->r, z);
    return h;
}

void findLongestAndShortestPath(link h, link z, int level, int * longest_path, int * shortest_path) {
    if(h == z)
        return;
    if(h->l != z || h->r != z) {
        findLongestAndShortestPath(h->l, z, level + 1, longest_path, shortest_path);
        findLongestAndShortestPath(h->r, z, level + 1, longest_path, shortest_path);
    }
    else {
        if(*longest_path < level)
            *longest_path = level;
        if(*shortest_path > level)
            *shortest_path = level;
    }
    
}


void BSTDailyQuotebalance(BSTDailyQuote bst)
{
    int longest_path = -1, shortest_path = 999999, level = 1;
    findLongestAndShortestPath(bst->root, bst->z, level, &longest_path, &shortest_path);
    float ris = (float) longest_path/shortest_path;
    if(ris > 1)
        bst->root = balanceR(bst->root, bst->z);
}
