#include <stdio.h>
#include <stdlib.h>
#include "pgList.h"
#include "pg.h"

typedef struct nodoPg_s *nodoPg_t;
struct nodoPg_s{
    pg_t pg;
    nodoPg_t next;
};

struct pgList_s{
    nodoPg_t headPg;
    nodoPg_t tailPg;
    int nPg;
};

pgList_t pgList_init() {
    pgList_t pgList = malloc(sizeof(struct pgList_s));
    pgList->nPg = 0;
    return pgList;
}

void pgList_free(pgList_t pgList) {
    free(pgList);
}

void pgList_read(FILE *fp, pgList_t pgList) {
    pg_t pg;
    while(pg_read(fp, &pg) == 1) {
        pgList_insert(pgList, pg);
    }
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray) {
    for(nodoPg_t node = pgList->headPg; node->next != NULL; node = node->next) {

    }
}

/* inserimento di un nuovo personaggio */
void pgList_insert(pgList_t pgList, pg_t pg) {
    nodoPg_t node = malloc(sizeof(struct nodoPg_s));
    node->pg = pg;
    if(pgList->nPg == 0){
        pgList->headPg = node;
        pgList->tailPg = node;
    }
    else {
        nodoPg_t tail = pgList->tailPg;
        tail->next = node;
        pgList->tailPg = node;
    }
    pgList->nPg += 1;
}

/* cancellazione con rimozione */
void pgList_remove(pgList_t pgList, char* cod) {}

/* ricerca per codice, ritornando il puntatore */
pg_t *pgList_searchByCode(pgList_t pgList, char* cod) {}
