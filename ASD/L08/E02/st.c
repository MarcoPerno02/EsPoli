#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "st.h"


struct symboltable {
    char ** vet;
    int N;
    int M;
};

ST STinit()
{
    ST st = malloc(sizeof(struct symboltable));
    st->M = 1;
    st->vet = malloc(st->M * sizeof(char *));
    st->N = 0;
    return st;
}

void STfree(ST st) {
    for(int i = 0; i < st->N; i++) {
        free(st->vet[i]);
    }
    free(st->vet);
    free(st);
}

void STInsert(ST st, char * label, int pos) {
    if(pos == st->M) {
        st->M *= 2;
        st->vet = realloc(st->vet, (st->M)*sizeof(char *));
    }
    st->vet[pos] = malloc(sizeof(char)*(30+1));
    strcpy(st->vet[pos], label);
    st->N += 1;
}

int STSearch(ST st, char * label) {
    int i = 0; 
    while(i != st->N && strcmp(st->vet[i], label) != 0) {
        i++;
    }
    if(i==st->N) {
        STInsert(st, label, i);
    }
    return i;
}
