#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../st/st.h"

struct st_s {
    Item_st * vet;
    int N;
    int maxN;
};



ST STInit(int maxN) {
    ST st = malloc(sizeof(struct st_s));
    st->maxN = maxN;
    st->N = 0;
    st->vet = malloc(sizeof(Item_st)*maxN);
}

void STFree(ST st) {
    free(st->vet);
    free(st);
}

int STsearch(ST st, Key_st k) {
    for(int i = 0; i < st->N; i++) {
        if(strcmp(st->vet[i].key.name, k.name) == 0) {
            return i;
        }
    }
    return -1;
}

Key_st STsearchByIndex (ST st, int id) {
    for(int i = 0; i < st->N; i++) {
        if(st->vet[i].id == id) {
            return st->vet[i].key;
        }
    }
}

int STcount(ST st) {
    return st->N;
}

void STInsert(ST st, Item_st item) {
    int ris = STsearch(st, item.key);
    if(ris == -1) {
        if(st->N == st->maxN) {
            st->maxN *= 2;
            st->vet = realloc(st->vet, sizeof(Item_st)*st->maxN);
        }
        Item_st item_to_add;
        item_to_add.id = st->N;
        strcpy(item_to_add.key.name, item.key.name);
        st->vet[st->N] = item_to_add;
        st->N+=1;
    }
}

