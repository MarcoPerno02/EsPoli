#include <stdio.h>
#include <stdlib.h>
#include "equipArray.h"
#include "invArray.h"

struct equipArray_s{
    int inUso;
    int * vettEq;
};

equipArray_t equipArray_init() {
    equipArray_t equipArray;
    equipArray = malloc(sizeof(struct equipArray_s));
    equipArray->inUso = 0;
    equipArray->vettEq = malloc(sizeof(int)*8);
    return equipArray;
}

void equipArray_free(equipArray_t equipArray) {
    free(equipArray->vettEq);
    free(equipArray);
}

/* quanti equipaggiamenti sono in uso */
int equipArray_inUse(equipArray_t equipArray) {
    return equipArray->inUso;
}

/* scrittura su file */
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray) {
    for(int i = 0; i < equipArray->inUso; i++) {
        invArray_printByIndex(fp, invArray, equipArray->vettEq[i]);
    }
}

/* modifica equipaggiamento scegliendo un oggetto da inventario */
void equipArray_update(equipArray_t equipArray, invArray_t invArray) {
    int choice;
    char name[50+1];
    printf("Inserire 0 per aggiungere, 1 per rimuovore: ");
    scanf("%d", &choice);
    printf("Inserire name oggetto inventario: ");
    scanf("%s", name);
    int index = invArray_searchByName(invArray, name);
    if(choice == 0) {
        equipArray->vettEq[equipArray->inUso] = index;
        equipArray->inUso += 1;
    }
    else {
        int i = 0;
        while(i < 8 && equipArray->vettEq[i] != index)
            i++;
        while(i != 7) {
            equipArray->vettEq[i] = equipArray->vettEq[i+1];
            i++;
        }
        equipArray->inUso -= 1;

    }
}
/* torna indice (nel vettore inventario) dell'oggetto in posizione index (0..EQUIP_SLOT-1) di equipArray */
int equipArray_getEquipByIndex(equipArray_t equipArray, int index) {
    return equipArray->vettEq[index];
}