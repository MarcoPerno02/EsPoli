#include <stdio.h>
#include <stdlib.h>
#include "pg.h"

/* lettura e scrittura su file */
int pg_read(FILE *fp, pg_t *pgp) {
    int ris;
    ris = fscanf(fp, "%s %s %s %d %d %d %d %d %d", pgp->cod, pgp->nome, pgp->classe, &(pgp->b_stat.hp), &(pgp->b_stat.mp), &(pgp->b_stat.atk), &(pgp->b_stat.def), &(pgp->b_stat.mag), &(pgp->b_stat.spr));
    if(ris == EOF) return 0;
    return 1;
}
/* non essendo struct dinamica, pulisce chiamando il distruttire di equipArray */
void pg_clean(pg_t *pgp) {}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray) {}
/* modifica personaggio aggiungendo/togliendo un equipaggiamento selezionato da inventario:
di fatto e' sufficiente chiamare l'opportuna funzione dal modulo equipArray */
void pg_updateEquip(pg_t *pgp, invArray_t invArray) {}