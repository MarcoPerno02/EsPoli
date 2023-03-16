#include <stdio.h>
#include <stdlib.h>
#include "skilift/skilift.h"
#include "bst/bst.h"

int main () {
    FILE * fin;
    fin = fopen("input2.txt", "r");
    SKiliftArray * S = SKILIFTLoad(fin);
    fclose(fin);
    fin = fopen("input1.txt", "r");
    BST bst = BSTLoad(fin, S);
    fclose(fin);
    WrapperLog wrapperLogs = BSTLogInit();
    char skiliftId[11];
    int cardId;
    int time;
    while(1 == 1) {
        printf("Inserisci skiliftId cardId time: ");
        fscanf(stdin, "%s %d %d", skiliftId, &cardId, &time);
        authorize(bst, S, wrapperLogs, cardId, skiliftId, time);
    }
    SKILIFTFree(S);
    BSTfree(bst);
}