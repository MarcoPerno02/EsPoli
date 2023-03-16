#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../skilift/skilift.h"

Skilift * SKILIFTSearchById(SKiliftArray * S, char * id) {
    for(int i = 0; i < S->N; i++) {
        if(strcmp(S->array[i].id, id) == 0) {
            return &(S->array[i]);
        }
    }
    return NULL;
}

SKiliftArray * SKILIFTLoad(FILE * fin) {
    SKiliftArray * skiliftArray = malloc(sizeof(* skiliftArray));
    skiliftArray->N = 0;
    skiliftArray->Max_N = 1;
    skiliftArray->array = malloc(sizeof(Skilift ) * skiliftArray->Max_N);
    char name[11];
    int interval;
    while (fscanf(fin, "%s %d", name, &interval) != EOF)
    {
        Skilift skilift;
        strcpy(skilift.id, name);
        skilift.interval = interval;
        if(skiliftArray->Max_N == skiliftArray->N) {
            skiliftArray->Max_N *= 2;
            skiliftArray->array = realloc(skiliftArray->array, sizeof(Skilift ) * skiliftArray->Max_N);
        }
        skiliftArray->array[skiliftArray->N] = skilift;
        skiliftArray->N += 1;
    }
    return skiliftArray;
}

void SKILIFTFree(SKiliftArray * S) {
    free(S->array);
    free(S);
}