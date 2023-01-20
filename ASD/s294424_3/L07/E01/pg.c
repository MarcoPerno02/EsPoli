#include <stdio.h>
#include <stdlib.h>
#include "pg.h"

/* lettura e scrittura su file */
int pg_read(FILE *fp, pg_t *pgp) {
    int ris;
    ris = fscanf(fp, "%s %s %s", pgp->cod, pgp->nome, pgp->classe);
    stat_read(fp, &(pgp->b_stat));
    pgp->equip = equipArray_init();
    if(ris == EOF) return 0;
    return 1;
}
/* non essendo struct dinamica, pulisce chiamando il distruttire di equipArray */
void pg_clean(pg_t *pgp) {
    equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray) {
    fprintf(fp, "%s %s %s\n", pgp->cod, pgp->nome, pgp->classe);
    int nEquipInUse = equipArray_inUse(pgp->equip);
    for(int i = 0; i < nEquipInUse; i++) {
        int equip_idx = equipArray_getEquipByIndex(pgp->equip, i);
        inv_t * inv = invArray_getByIndex(invArray, equip_idx);
        stat_t stat = inv_getStat(inv);
        if(i == 0) {
            pgp->eq_stat.atk = pgp->b_stat.atk + stat.atk;
            pgp->eq_stat.def = pgp->b_stat.def + stat.def;
            pgp->eq_stat.hp = pgp->b_stat.hp + stat.hp;
            pgp->eq_stat.mag = pgp->b_stat.mag + stat.mag;
            pgp->eq_stat.mp = pgp->b_stat.mp + stat.mp;
            pgp->eq_stat.spr = pgp->b_stat.spr + stat.spr;
        }
        else {
            pgp->eq_stat.atk+= stat.atk;
            pgp->eq_stat.def+= stat.def;
            pgp->eq_stat.hp+=stat.hp;
            pgp->eq_stat.mag+= stat.mag;
            pgp->eq_stat.mp+=stat.mp;
            pgp->eq_stat.spr+= stat.spr;
        }
    }
    if(nEquipInUse == 0)
        stat_print(fp, &(pgp->b_stat), 1);
    else
        stat_print(fp, &(pgp->eq_stat), 1);
    printf("Equip:\n");
    equipArray_print(fp, pgp->equip, invArray);
}
/* modifica personaggio aggiungendo/togliendo un equipaggiamento selezionato da inventario:
di fatto e' sufficiente chiamare l'opportuna funzione dal modulo equipArray */
void pg_updateEquip(pg_t *pgp, invArray_t invArray) {
    equipArray_update(pgp->equip, invArray);
}