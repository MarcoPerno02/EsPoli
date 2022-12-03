#include <stdio.h>
#include <stdlib.h>
#include "inv.h"

/* funzioni di input/output delle statistiche */
void stat_read(FILE *fp, stat_t *statp) {
    fscanf(fp, "%d %d %d %d %d %d", &(statp->hp), &(statp->mp), &(statp->atk), &(statp->def), &(statp->mag), &(statp->spr));
}
void stat_print(FILE *fp, stat_t *statp, int soglia) {
    if(statp->atk < soglia) {
        statp->atk = 0;
    }
    if(statp->def < soglia) {
        statp->def = 0;
    }
    if(statp->hp < soglia) {
        statp->hp = 0;
    }
    if(statp->mag < soglia) {
        statp->mag = 0;
    }
    if(statp->mp < soglia) {
        statp->mp = 0;
    }
    if(statp->spr < soglia) {
        statp->spr = 0;
    }
    fprintf(fp, "Stat:\natk: %d def: %d hp: %d mag: %d mp: %d spr: %d\n", statp->atk, statp->def, statp->hp, statp->mag, statp->mp, statp->spr);
}

/* funzioni di input/output di un oggetto dell'inventario */
void inv_read(FILE *fp, inv_t *invp) {
    fscanf(fp, "%s %s %d %d %d %d %d %d", invp->nome, invp->tipo, &(invp->stat.atk), &(invp->stat.def), &(invp->stat.hp), &(invp->stat.mag), &(invp->stat.mp), &(invp->stat.spr));
}
void inv_print(FILE *fp, inv_t *invp) {
    fprintf(fp, "%s %s %d %d %d %d %d %d\n", invp->nome, invp->tipo, invp->stat.atk, invp->stat.def, invp->stat.hp, invp->stat.mag, invp->stat.mp, invp->stat.spr);
}

/* ritorna il campo stat di un oggetto dell'inventario */
stat_t inv_getStat(inv_t *invp) {
    return invp->stat;
}
