#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int zaffiri;
    int rubini;
    int topazi;
    int smeraldi;
    int tot;
} Collection;

typedef struct 
{
    int type; // 0 zaffiro, 1 rubino, 2 topazio, 3 smeraldo
} Stone;

int checkZaffiro(Collection collection, int last_stone);
int checkRubino(Collection collection, int last_stone);
int checkTopazio(Collection collection, int last_stone);
int checkSmeraldo(Collection collection, int last_stone);
void bestCombination(Collection collection);
void addStone(Stone * combination, int pos, int len, Collection * collection, Stone * best_combination, int * len_best_combination);
int loadCollection(Collection ** collections);
void initializeCombination(Stone * combination, int len);
void printCombination(Stone * combination, int len);
void decreaseCollection(Collection * collection, int stone_type);
void increaseCollection(Collection * collection, int stone_type);
void handleFinalCase(Stone * combination, int pos, Stone * best_combination, int * len_best_combination);

int main() {
    Collection * collections;
    int n_set = loadCollection(&collections);
    for(int i = 0; i < n_set; i++) {
        printf("Test%d:\n", i+1);
        bestCombination(collections[i]);
    }
}

int loadCollection(Collection ** collections) {
    FILE * fin;
    if((fin = fopen("easy_test_set.txt", "r")) == NULL) {
        printf("Errore apertura file");
        exit(-1);
    }
    int n_set;
    fscanf(fin, "%d", &n_set);
    *collections = (Collection *) malloc(sizeof(Collection) * n_set);
    for(int i = 0; i < n_set; i++) {
        fscanf(fin, "%d %d %d %d", &((*collections)[i].zaffiri), &((*collections)[i].rubini), &((*collections)[i].topazi), &((*collections)[i].smeraldi));
        (*collections)[i].tot = (*collections)[i].zaffiri + (*collections)[i].rubini + (*collections)[i].topazi + (*collections)[i].smeraldi;
        //printf("%d %d %d %d\n", (*collections)[i].zaffiri, (*collections)[i].rubini, (*collections)[i].topazi, (*collections)[i].smeraldi);
    }
    fclose(fin);
    return n_set;
}

void initializeCombination(Stone * combination, int len) {
    for(int i = 0; i < len; i++) {
        combination[i].type = -1;
    }
}

void bestCombination(Collection collection) {
    // Start from one of the 4 types of stones
    Stone best_combination[collection.tot];
    initializeCombination(best_combination, collection.tot);
    int len_best_combination = -1;
    for(int i = 0; i < 4; i++) {
        Stone combination[collection.tot];
        initializeCombination(combination, collection.tot);
        combination[0].type = i;
        if(i == 0)
            collection.zaffiri--;
        else if(i==1)
            collection.rubini--;
        else if(i==2)
            collection.topazi--;
        else
            collection.smeraldi--;
        addStone(combination, 1, collection.tot, &collection, best_combination, &len_best_combination);
        if(i == 0)
            collection.zaffiri++;
        else if(i==1)
            collection.rubini++;
        else if(i==2)
            collection.topazi++;
        else
            collection.smeraldi++;
        
    }
    printf("Len best combination: %d\n", len_best_combination);
    printCombination(best_combination, len_best_combination);
}

int checkZaffiro(Collection collection, int last_stone) {
    // Ok for zaffiro and topazio
    if((last_stone == 0 && collection.zaffiri > 0) || (last_stone == 2  && collection.zaffiri > 0))
        return 1;
    return 0;
}

int checkRubino(Collection collection, int last_stone) {
    // Ok for zaffiro and topazio
    if((last_stone == 0 && collection.rubini > 0) || (last_stone == 2  && collection.rubini > 0))
        return 1;
    return 0;
}

int checkTopazio(Collection collection, int last_stone) {
    // Ok for rubino and smeraldo
    if((last_stone == 1 && collection.topazi > 0) || (last_stone == 3 && collection.topazi > 0))
        return 1;
    return 0;
}

int checkSmeraldo(Collection collection, int last_stone) {
    // Ok for rubino and smeraldo
    if((last_stone == 1 && collection.smeraldi > 0) || (last_stone == 3 && collection.smeraldi > 0))
        return 1;
    return 0;
}

void addStone(Stone * combination, int pos, int len, Collection * collection, Stone * best_combination, int * len_best_combination) {
    // 1 stands for ok, 0 for not
    int choices [4] = {0, 0, 0, 0};
    choices[0] = checkZaffiro(*collection, combination[pos-1].type);
    choices[1] = checkRubino(*collection, combination[pos-1].type);
    choices[2] = checkTopazio(*collection, combination[pos-1].type);
    choices[3] = checkSmeraldo(*collection, combination[pos-1].type);
    int paths = 0;
        
    for(int i = 0; i < 4; i++) {
        if(choices[i] == 1 && *len_best_combination != len) {
            // Pruning section
            paths++;
            if(collection->topazi == 0 && i == 3) {
                // Case only smeraldi left and not topazi
                if(pos + collection->smeraldi > *len_best_combination) {
                    int pos_aus;
                    for(pos_aus = pos; collection->smeraldi != 0; collection->smeraldi--, pos_aus++) {
                        combination[pos_aus].type = i;
                    }
                    handleFinalCase(combination, pos_aus, best_combination, len_best_combination);
                    for(; pos != pos_aus + 1 ; pos_aus--) {
                        if(pos != pos_aus)
                            collection->smeraldi++;
                        combination[pos_aus].type = -1;
                    }
                }
            }
            else if(collection->rubini == 0 && i == 0) {
                // Case only zaffiri left and not rubini
                if(pos + collection->zaffiri > *len_best_combination) {
                    int pos_aus;
                    for(pos_aus = pos; collection->zaffiri != 0; collection->zaffiri--, pos_aus++) {
                        combination[pos_aus].type = i;
                    }
                    handleFinalCase(combination, pos_aus, best_combination, len_best_combination);
                    for(; pos != pos_aus + 1 ; pos_aus--) {
                        if(pos != pos_aus)
                            collection->zaffiri++;
                        combination[pos_aus].type = -1;
                    }
                }
            }
            else {
                combination[pos].type = i;
                decreaseCollection(collection, i);
                addStone(combination, pos+1, len, collection, best_combination, len_best_combination);
                increaseCollection(collection, i);
            }
            
        }
    }
    if(paths == 0 ) {
        if(pos > *len_best_combination) {
            // There werent possible choices to take --> Finale case
            handleFinalCase(combination, pos, best_combination, len_best_combination);
            // Release position
            
        }
        else if(1!=1) {
            printf("Scartato:\n");
            printCombination(combination, pos);
        }
        combination[pos-1].type = -1;
        
    }
    
}

void handleFinalCase(Stone * combination, int pos, Stone * best_combination, int * len_best_combination) {
    //printCombination(combination, pos);
    if(pos > *len_best_combination) {
        for(int i = 0; i < pos; i++) {
            best_combination[i] = combination[i];
        }
        *len_best_combination = pos;
    }
}

void printCombination(Stone * combination, int len) {
    for(int i = 0; i < len; i++) {
        if(combination[i].type == 0)
            printf("Zaffiro, ");
        else if(combination[i].type == 1)
            printf("Rubino, ");
        else if(combination[i].type == 2)
            printf("Topazio, ");
        else
            printf("Smeraldo, ");
    }
    printf("\n");
}

void increaseCollection(Collection * collection, int stone_type) {
    if(stone_type == 0)
        collection->zaffiri += 1;
    else if(stone_type == 1)
        collection->rubini += 1;
    else if(stone_type == 2)
        collection->topazi += 1;
    else
        collection->smeraldi += 1;
}

void decreaseCollection(Collection * collection, int stone_type) {
    if(stone_type == 0)
        collection->zaffiri -= 1;
    else if(stone_type == 1)
        collection->rubini -= 1;
    else if(stone_type == 2)
        collection->topazi -= 1;
    else
        collection->smeraldi -= 1;
}
