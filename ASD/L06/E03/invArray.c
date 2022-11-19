#include <stdio.h>
#include <stdlib.h>
#include "invArray.h"

typedef struct {
    int aa;
}invArray_s;

/* creatore e disruttore */
invArray_t invArray_init() {}
void invArray_free(invArray_t invArray) {}

/* lettura e scrittura su file */
void invArray_read(FILE *fp, invArray_t invArray) {}
void invArray_print(FILE *fp, invArray_t invArray) {}
/* stampa un unico oggetto selezionato da indice (nel vettore) */
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index) {}
/* ritorna puntatore a oggetto selezionato da indice (nel vettore) */
inv_t *invArray_getByIndex(invArray_t invArray, int index) {}
/* ritorna indice (nel vettore) a oggetto selezionato da nome */
int invArray_searchByName(invArray_t invArray, char *name) {}