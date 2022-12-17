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
    if(pgList == NULL) exit(-1);
    pgList->nPg = 0;
    return pgList;
}

void pgList_free(pgList_t pgList) {
    for(nodoPg_t node = pgList->headPg; node->next != NULL; node = node->next) {
        pg_clean(&(node->pg));
    }
    free(pgList);
}

void pgList_read(FILE *fp, pgList_t pgList) {
    pg_t pg;
    while(pg_read(fp, &pg) == 1) {
        pgList_insert(pgList, pg);
    }
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray) {
    for(nodoPg_t node = pgList->headPg; node != NULL; node = node->next) {
        pg_print(fp, &(node->pg), invArray);
    }
}

/* inserimento di un nuovo personaggio */
void pgList_insert(pgList_t pgList, pg_t pg) {
    if(pgList_searchByCode(pgList, pg.cod) == NULL) {
        nodoPg_t node = malloc(sizeof(struct nodoPg_s));
        if(node == NULL) exit(-1);
        node->pg = pg;
        node->next = NULL;
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
    else {
        printf("Id già presente\n");
    }
}

/* cancellazione con rimozione */
void pgList_remove(pgList_t pgList, char* cod) {
    nodoPg_t node = pgList->headPg;
    nodoPg_t prec = NULL;
    int found = 0;
    while(node != NULL && found == 0){
        if(strcmp(node->pg.cod, cod) == 0) {
            if(prec != NULL) {
                prec->next = node->next;
            } 
            else {
                pgList->headPg = node->next;
            }
            free(node);
            pgList->nPg -= 1;
            found = 1;
        }
        else {
            prec = node;
            node = node->next;
        }
    }
}

/* ricerca per codice, ritornando il puntatore */
pg_t *pgList_searchByCode(pgList_t pgList, char* cod) {
    nodoPg_t node = pgList->headPg;
    int found = 0;
    while(pgList->nPg != 0 && node != NULL && found == 0){
        if(strcmp(node->pg.cod, cod) == 0) {
            found = 1;
        }
        else {
            node = node->next;
        }
    }
    if(found == 1)
        return &(node->pg);
    else
        return NULL;
}
