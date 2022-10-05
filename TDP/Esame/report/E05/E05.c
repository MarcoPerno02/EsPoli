#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int pren;
    int clienti;
} giorno;

char *numberToDay(int number) {
    if(number == 0)
        return "Lunedi";
    else if(number == 1)
        return "Martedi";
    else if(number == 2)
        return "Mercoledi";
    else if(number == 3)
        return "Giovedi";
    else if(number == 4)
        return "Venerdi";
    else if(number == 5)
        return "Sabato";
    else if(number == 6)
        return "Domenica";
}

int dayToNumber(char *name){
    if(strcmp(name, "Lunedi") == 0) {
        return 0;
    }
    else if(strcmp(name, "Martedi") == 0) {
        return 1;
    }
    else if(strcmp(name, "Mercoledi") == 0) {
        return 2;
    }
    else if(strcmp(name, "Giovedi") == 0) {
        return 3;
    }
    else if(strcmp(name, "Venerdi") == 0) {
        return 4;
    }
    else if(strcmp(name, "Sabato") == 0) {
        return 5;
    }
    else if(strcmp(name, "Domenica") == 0) {
        return 6;
    }
}

int printReservations(FILE *fp) {
    giorno sett[7];
    for(int i = 0; i < 7; i++) {
        sett[i].pren = 0;
        sett[i].clienti = 0;
    }
    char day[50];
    float clienti = 0; // dichiarato clienti come float invece di int
    while(fscanf(fp, "%s %f", day, &clienti) != EOF) { /*errore &*/
        int num = dayToNumber(day);
        sett[num].pren++;
        sett[num].clienti += clienti;
    }
    int max = -1;
    for(int i = 0; i < 7; i++) {
        float media;
        if(sett[i].pren != 0) /*dimenticato*/
            media = (float) sett[i].clienti/sett[i].pren;
        else 
            media = 0;
        printf("%s: %d prenotazioni, %.2f media clienti\n", numberToDay(i), sett[i].pren, media);/*dimenticato 2f*/
        if(max < sett[i].clienti) 
            max = sett[i].clienti;
    }
    return max;
}

int main() {
    FILE *fp;
    fp = fopen("input.txt", "r");
    printf("%d", printReservations(fp));
}