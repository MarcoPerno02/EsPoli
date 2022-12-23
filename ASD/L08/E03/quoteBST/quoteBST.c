#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quoteBST.h"
#include "../quote/quote.h"



typedef struct node* link;
struct node {Quote quote;link p;link l;link r;int N;};
struct quoteBST_s { link root; link z; };

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

QuoteBSTListContainer BSTQuoteBSTListContainerInit() {
    QuoteBSTListContainer list = malloc(sizeof(struct quoteBSTListContainer_s));
    list->head = NULL;
    list->tail = NULL;
    list->N = 0;
    return list;
}

void BSTQuoteBSTListContainerFree(QuoteBSTListContainer list) {
    linkQuoteBSTContainer next;
    for(linkQuoteBSTContainer x = list->head; x != NULL; x = next) {
        next = x->next;
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

void BSTinsert_leafR(QuoteBST bst, Quote x)
{
    bst->root = insertR(bst->root, x, bst->z);
}

QuoteBST BSTinit()
{
    QuoteBST bst = malloc(sizeof(struct quoteBST_s));
    bst->root = (bst->z = NEW(QuoteSetNull(), NULL, NULL, NULL, 0));
    return bst;
}


void BSTQuoteBSTListContainerInsert(FILE * f, QuoteBSTListContainer list) {
    // Create node for that day
    linkQuoteBSTContainer new_node = malloc(sizeof(struct quoteBSTNodeContainer_s));
    new_node->next = NULL;
    new_node->quoteBST = BSTinit();
    if(list->N != 0) {
        linkQuoteBSTContainer tail = list->tail;
        tail->next = new_node;
        list->tail = new_node;
    }
    else {
        
        list->head = new_node;
        list->tail = new_node;
    }
    list->N += 1;

    int n_quote;
    fscanf(f, "%d", &n_quote);
    
    for(int i = 0; i < n_quote; i++) {
        // Iterate on each quote and add it the list of that day
        int year, month, day, minute, hour;
        fscanf(f, "%d/%d/%d %d:%d", &year, &month, &day, &hour, &minute);
        if(i == 0) {
            new_node->date = DATEInit(year, month, day, 0, 0);
        }
        Quote quote = QuoteInit();
        quote->date = DATEInit(year, month, day, hour, minute);
        fscanf(f, "%f %d", &(quote->val), &(quote->qty));
        BSTinsert_leafR(new_node->quoteBST, quote);
        
    }
}

void BSTFree() {
    // Ricordarsi da scaricare date
}
