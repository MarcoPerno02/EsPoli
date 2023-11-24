#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../st/st.h"


ST STInit(int v) {
    ST st = malloc(sizeof(struct st_s));
    st->N = v;
    st->vet = malloc(st->N * sizeof(Item));
    return st;
}


void STLoad(FILE *fin, ST st) {
    for(int i = 0; i < st->N; i++) {
        fscanf(fin, "%s", st->vet[i].name);
    }
}

void STCopy(ST dest, ST source) {
    for(int i = 0; i < source->N; i++) {
        strcpy(dest->vet[i].name, source->vet[i].name);
    }
}

int STsearch(ST st, char * name) {
    for(int i = 0; i < st->N; i++) {
        if(strcmp(st->vet[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

char * STsearchByIndex(ST st, int id) {
    return st->vet[id].name;
}

void STFree(ST st) {
    free(st->vet);
    free(st);
}