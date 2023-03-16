#include <stdio.h>
#include <stdlib.h>
#include "../bst/bst.h"
#include "../skilift/skilift.h"
#include <string.h>

typedef struct {
    Skilift ** skilift;
    int * time;
    int * cont;
} WrapperSkilift;

typedef struct {
    int id;
} Key;

typedef struct {
    Key key;
    WrapperSkilift sklifts_enabled;
    int N_sklifts_enabled;
} Item;

typedef struct node_s * link;
struct node_s {
    Item item;
    link l;
    link p;
    link r;
    int N;
};

struct bst_st
{
    link z;
    link root;
};

typedef struct {
    Key cardiId;
    Skilift * skilift;
    int time;
} Log;

struct wrapperLog_s{
    Log * array;
    int N;
    int Max_N;
};

static link NEW(Item item, link p, link l, link r, int N){
    link x = malloc(sizeof *x);
    x->item = item;
    x->p = p; x->l = l; x->r = r; x->N = N;
    return x;
}

int KEYcmp(Key key1, Key key2) {
    if(key1.id > key2.id) 
        return 1;
    else if(key1.id == key2.id)
        return 0;
    else 
        return -1;
} 

Key KEYget(Item item) {
    return item.key;
}

Item ITEMsetNull() {
    Item x;
    x.key.id = -1;
    return x;
}

BST BSTinit( ) {
    BST bst = malloc(sizeof *bst) ;
    bst->root=(bst->z=NEW(ITEMsetNull(), NULL, NULL, NULL, 0));
    return bst;
}


static int countR(link h, link z)
{
    if (h == z)
        return 0;
    return countR(h->l, z) + countR(h->r, z) + 1;
}

int BSTcount(BST bst)
{
    return countR(bst->root, bst->z);
}

link rotR(link h) {
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


link rotL(link h) {
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


link partR(link h, int r)
{
    int t = h->l->N;
    if (t > r)
    {
        h->l = partR(h->l, r);
        h = rotR(h);
    }
    if (t < r)
    {
        h->r = partR(h->r,r - t - 1);
        h = rotL(h);
    }
    return h;
}

link insertT(link h, Item x, link z)
{
    if (h == z)
        return NEW(x, z, z, z, 1);
    if (KEYcmp(KEYget(x), KEYget(h->item)) == -1)
    {
        h->l = insertT(h->l, x, z);
        h = rotR(h);
        h->N++;
    }
    else
    {
        h->r = insertT(h->r, x, z);
        h = rotL(h);
        h->N++;
    }
    return h;
}

void BSTinsert_root(BST bst, Item x) {
    bst->root = insertT(bst->root, x, bst->z);
}

static void treeFree(link h, link z)
{
    if (h == z)
        return;
    treeFree(h->l,z);
    treeFree(h->r,z);
    free(h);
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
void BSTbalance(BST bst)
{
    bst->root = balanceR(bst->root, bst->z);
}

Item searchR(link h, Key k, link z)
{
    int cmp;
    if (h == z)
        return ITEMsetNull();
    cmp = KEYcmp(k, KEYget(h->item));
    if (cmp == 0)
        return h->item;
    if (cmp == -1)
        return searchR(h->l, k, z);
    return searchR(h->r, k, z);
}
Item BSTsearch(BST bst, Key k)
{
    return searchR(bst->root, k, bst->z);
}

WrapperLog BSTLogInit() {
    WrapperLog wrapper = malloc(sizeof(struct wrapperLog_s));
    wrapper->N = 0;
    wrapper->Max_N = 1;
    wrapper->array = malloc(sizeof(Log )*wrapper->Max_N);
    return wrapper;
}

BST BSTLoad(FILE * fin, SKiliftArray * S) {
    BST bst = BSTinit();
    int cont = 0;
    int n;
    while(fscanf(fin, "%d", &n) != EOF) {
        Item item;
        Key key;
        key.id = cont;
        item.N_sklifts_enabled = n;
        item.key = key;
        item.sklifts_enabled.time = malloc(sizeof(int) * n);
        item.sklifts_enabled.skilift = malloc(sizeof(Skilift *) * n);
        item.sklifts_enabled.cont = malloc(sizeof(Skilift *) * n);
        for(int i = 0; i < n; i++) {
            char id[11];
            fscanf(fin, "%s", id);
            item.sklifts_enabled.time[i] = 0;
            item.sklifts_enabled.cont[i] = 0;
            item.sklifts_enabled.skilift[i] = SKILIFTSearchById(S, id);
        }
        cont++;
        BSTinsert_root(bst, item);
    }
    BSTbalance(bst);
    return bst;
}

int authorize (BST bst, SKiliftArray * S, WrapperLog wrapperLog, int cardId, char *skiliftId, int time) {
    Key k;
    k.id = cardId;
    Item x = BSTsearch(bst, k);
    int i = 0;
    int exit = 0;
    while(i < x.N_sklifts_enabled && exit == 0) {
        if(strcmp(skiliftId, x.sklifts_enabled.skilift[i]->id) == 0) {
            if(time - x.sklifts_enabled.time[i] >=  x.sklifts_enabled.skilift[i]->interval) {
                x.sklifts_enabled.time[i] = time;
                x.sklifts_enabled.cont[i]++;
                printf("Abilitato\n");
                if(wrapperLog->N == wrapperLog->Max_N) {
                    wrapperLog->Max_N *= 2;
                    wrapperLog->array = realloc(wrapperLog->array, sizeof(Log )*wrapperLog->Max_N);
                }
                Log tmp;
                tmp.cardiId.id = cardId;
                tmp.skilift = x.sklifts_enabled.skilift[i];
                tmp.time = time;
                wrapperLog->array[wrapperLog->N] = tmp;
                wrapperLog->N += 1;
                exit = 2;
            }
            else {
                printf("Riprovare più tardi\n");
                exit = 1;
            }
            
        }
        i++;
    }
    if(exit == 0) {
        printf("Pista non abilitata\n");
        return -1;
    }
}

void BSTfree(BST bst)
{
    if (bst == NULL)
        return;
    treeFree(bst -> root,
             bst->z);
    free(bst->z);
    free(bst);
}
