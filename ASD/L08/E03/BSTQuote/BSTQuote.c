#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BSTQuote.h"
#include "../quote/quote.h"



typedef struct node* link;
struct node {Quote quote;link p;link l;link r;int N;};
struct BSTQuote_s { link root; link z; };

static link NEW(Quote quote, link p, link l, link r, int N)
{
    link x = malloc(sizeof *x);
    x->quote = quote;
    x->p = p;
    x->l = l;
    x->r = r;
    x->N = N;
    return x;
}

BSTQuoteListContainer BSTQuoteListContainerInit() {
    BSTQuoteListContainer list = malloc(sizeof(struct BSTQuoteListContainer_s));
    list->head = NULL;
    list->tail = NULL;
    list->N = 0;
    return list;
}

static void treeFree(link h, link z)
{
    if (h == z)
        return;
    QuoteFree(h->quote);
    treeFree(h->l,z);
    treeFree(h->r, z);
    free(h);
}

void BSTQuotefree(BSTQuote bst)
{
    if (bst == NULL)
        return;
    treeFree(bst->root, bst->z);
    free(bst->z);
    free(bst);
}

void BSTQuoteListContainerFree(BSTQuoteListContainer list) {
    linkBSTQuoteContainer next;
    for(linkBSTQuoteContainer x = list->head; x != NULL; x = next) {
        next = x->next;
        BSTQuotefree(x->BSTQuote);
        DATEFree(x->date);
        free(x);
    }
}

link insertR(link h, Quote x, link z)
{
    if (h == z)
        return NEW(x, z, z, z, 1);
    if (x->date->unix_time < h->quote->date->unix_time)
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

void BSTinsert_leafR(BSTQuote bst, Quote x)
{
    bst->root = insertR(bst->root, x, bst->z);
}

BSTQuote BSTinit()
{
    BSTQuote bst = malloc(sizeof(struct BSTQuote_s));
    bst->root = (bst->z = NEW(QuoteSetNull(), NULL, NULL, NULL, 0));
    return bst;
}

linkBSTQuoteContainer BSTQuoteSearchByDateBST(BSTQuoteListContainer list, Date date_bst) {
    for(linkBSTQuoteContainer x = list->head; x != NULL; x = x->next ) {
        if(x->date->unix_time == date_bst->unix_time) {
            return x;
        }
    }
    return NULL;
}


void BSTQuoteListContainerInsert(FILE * f, BSTQuoteListContainer list) {
    int n_quote;
    fscanf(f, "%d", &n_quote);
    // Read the date
    int year, month, day, minute, hour;
    fscanf(f, "%d/%d/%d %d:%d", &year, &month, &day, &hour, &minute);
    Date date_bst = DATEInit(year, month, day, 0, 0);
    linkBSTQuoteContainer node = BSTQuoteSearchByDateBST(list, date_bst);
    if(node == NULL) {
        // Create node for that day
        node = malloc(sizeof(struct BSTQuoteNodeContainer_s));
        node->next = NULL;
        node->BSTQuote = BSTinit();
        node->date = date_bst;
    }
    if(list->N != 0) {
        linkBSTQuoteContainer tail = list->tail;
        tail->next = node;
        list->tail = node;
    }
    else {
        list->head = node;
        list->tail = node;
    }
    list->N += 1;
    
    for(int i = 0; i < n_quote; i++) {
        // Iterate on each quote and add it the list of that day
        if(i != 0) {
            fscanf(f, "%d/%d/%d %d:%d", &year, &month, &day, &hour, &minute);
        }
        Quote quote = QuoteInit();
        quote->date = DATEInit(year, month, day, hour, minute);
        fscanf(f, "%f %d", &(quote->val), &(quote->qty));
        BSTinsert_leafR(node->BSTQuote, quote);
        
    }
}

void BSTFree() {
    // Ricordarsi da scaricare date
}
