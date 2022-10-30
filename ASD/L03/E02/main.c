#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[256];
} Song;

typedef struct {
    int songsNum;
    Song * songs;
} Friend;

void loadSongs(FILE *fin, Friend ** friends, int * friendsNum);
void printCombinations(Friend ** friends, Song * combination, int friendIndex, int songIndex, int friendsNum, int *combinationsNum);

void test(Song combination[]) {
    strcpy(combination[0].name, "ss");
    printf("%s", combination[0].name);
}

int main() {
    FILE *fin;
    Friend * friends;
    int friendsNum;
    loadSongs(fin, &friends, &friendsNum);

    int combinationsNum = 0;
    Song * combination;
    combination = (Song *) malloc(friendsNum * sizeof(Song));
    if(combination == NULL) exit(1);
    printCombinations(&friends, combination, 0, 0, friendsNum, &combinationsNum);
    for(int i = 0; i < friendsNum; i++) {
        free(friends[i].songs);
    }
    free(friends);
    free(combination);
}

void loadSongs(FILE *fin, Friend ** friends, int * friendsNum) {
    if((fin = fopen("brani.txt", "r")) == NULL) {
        printf("Errore nell'aprire il file brani.txt\n");
        exit(1);
    }
    fscanf(fin, "%d", friendsNum);
    *friends = (Friend *) malloc(*friendsNum * sizeof(Friend));
    if(*friends == NULL) exit(1);
    for(int i = 0; i < *friendsNum; i++) {
        int songsNum;
        fscanf(fin, "%d", &songsNum);
        (*friends)[i].songsNum = songsNum;
        (*friends)[i].songs = (Song *) malloc(songsNum * sizeof(Song));
        if((*friends)[i].songs == NULL) exit(1);
        for(int j = 0; j < songsNum; j++) {
            fscanf(fin, "%s", &(*friends)[i].songs[j].name);
        }
    }
    fclose(fin);
}

void printCombinations(Friend ** friends, Song * combination, int friendIndex, int songIndex, int friendsNum, int *combinationsNum) {
    if(friendIndex != friendsNum-1) {
        strcpy(combination[friendIndex].name, (*friends)[friendIndex].songs[songIndex].name);
        while(songIndex < (*friends)[friendIndex].songsNum) {
            printCombinations(friends, combination, friendIndex+1, 0, friendsNum, combinationsNum);
            songIndex++;
            strcpy(combination[friendIndex].name, (*friends)[friendIndex].songs[songIndex].name);
        }
    }
    else {
        for(int i = 0; i < (*friends)[friendIndex].songsNum; i++) {
            *combinationsNum+=1;
            printf("Combinazione numero %d:", *combinationsNum);
            for(int j = 0; j < friendsNum-1; j++) {
                printf("\t- %s", combination[j].name);
            }
            printf("\t- %s", (*friends)[friendIndex].songs[i].name);
            printf("\n");
        }
    }
}

