#include <stdio.h>
#include <stdlib.h>
#include "invArray.h"

struct invArray_s{
    int nInv;
    int maxInv;
    inv_t * vettInv;
};

/* creatore e disruttore */
invArray_t invArray_init() {
    invArray_t list = malloc(sizeof(struct invArray_s));
    list->nInv = 0;
    
}
void invArray_free(invArray_t invArray) {
    free(invArray);
}

/* lettura e scrittura su file */
void invArray_read(FILE *fp, invArray_t invArray) {
    fscanf(fp, "%d", &invArray->maxInv);
    invArray->nInv = invArray->maxInv;
    //invArray->vettInv = malloc(sizeof(inv_t *) * invArray->maxInv);
    invArray->vettInv = malloc(sizeof(invArray->maxInv));
    for(int i = 0; i < invArray->maxInv; i++) {
        inv_read(fp, &(invArray->vettInv[i]));
    }
}
void invArray_print(FILE *fp, invArray_t invArray) {
    for(int i = 0; i < invArray->nInv; i++) {
        fprintf(fp, "%s %s %d %d %d %d %d %d\n", invArray->vettInv[i].nome, invArray->vettInv[i].tipo, invArray->vettInv[i].stat.atk, invArray->vettInv[i].stat.def, invArray->vettInv[i].stat.hp, invArray->vettInv[i].stat.mag, invArray->vettInv[i].stat.mp, invArray->vettInv[i].stat.spr);
    }
}
/* stampa un unico oggetto selezionato da indice (nel vettore) */
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index) {}
/* ritorna puntatore a oggetto selezionato da indice (nel vettore) */
inv_t *invArray_getByIndex(invArray_t invArray, int index) {}
/* ritorna indice (nel vettore) a oggetto selezionato da nome */
int invArray_searchByName(invArray_t invArray, char *name) {}