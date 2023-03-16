#ifndef BST_H_DEFINED
#define BST_H_DEFINED
#include <stdio.h>
#include <stdlib.h>
#include "../skilift/skilift.h"

typedef struct bst_st * BST;
typedef struct wrapperLog_s * WrapperLog;

BST BSTLoad(FILE * fin, SKiliftArray * S);
void BSTfree(BST bst);
int authorize (BST bst, SKiliftArray * S,  WrapperLog wrapperLog, int cardId, char *skiliftId, int time);
WrapperLog BSTLogInit();

#endif