#include <stdio.h>
#include <stdlib.h>
#include "inv.h"

/* funzioni di input/output delle statistiche */
void stat_read(FILE *fp, stat_t *statp) {}
void stat_print(FILE *fp, stat_t *statp, int soglia) {}

/* funzioni di input/output di un oggetto dell'inventario */
void inv_read(FILE *fp, inv_t *invp) {}
void inv_print(FILE *fp, inv_t *invp) {}

/* ritorna il campo stat di un oggetto dell'inventario */
stat_t inv_getStat(inv_t *invp) {}
