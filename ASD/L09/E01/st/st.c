#include <stdio.h>
#include <stdlib.h>
#include "../st/st.h"

ST STLoad(FILE *fin) {
    ST st = malloc(sizeof(struct st_s));
    fscanf(fin, "%d", &(st->N));
    st->name = malloc(sizeof(st->N * sizeof(char *)));
    for(int i = 0; i < st->N; i++) {
        st->name[i] = malloc(sizeof(char) * 31);
        fscanf(fin, "%s", st->name[i]);
    }
    return st;
}

void STFree(ST st) {
    for(int i = 0; i < st->N; i++) {
        free(st->name[i]);
    }
    free(st->name);
    free(st);
}