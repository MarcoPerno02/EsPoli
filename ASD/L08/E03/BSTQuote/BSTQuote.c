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


link insertR(link h, Quote x, link z)
{
    if (h == z)
        return NEW(x, z, z, z, 1);
    if (x->date.unix_time < h->quote->date.unix_time)
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

BSTQuote BSTQuoteinit()
{
    BSTQuote bst = malloc(sizeof(struct BSTQuote_s));
    bst->root = (bst->z = NEW(QuoteSetNull(), NULL, NULL, NULL, 0));
    return bst;
}


void BSTQuoteInsert(FILE * f, BSTQuote bst) {
    int n_quote;
    fscanf(f, "%d", &n_quote);
    
    for(int i = 0; i < n_quote; i++) {
        // Iterate on each quote and add it the list of that day
        int year, month, day, minute, hour;
        fscanf(f, "%d/%d/%d %d:%d", &year, &month, &day, &hour, &minute);
        Quote quote = QuoteInit();
        quote->date = DATEInit(year, month, day, hour, minute);
        fscanf(f, "%f %d", &(quote->val), &(quote->qty));
        BSTinsert_leafR(bst, quote);
    }
}