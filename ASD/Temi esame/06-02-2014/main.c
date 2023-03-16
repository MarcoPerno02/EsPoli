#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculator/calculator.h"

int main() {
    char str1[9];
    char str2[9];
    char str3[10];
    printf("Inserisci stringa 1: ");
    scanf("%s", str1);
    printf("Inserisci stringa 2: ");
    scanf("%s", str2);
    printf("Inserisci risulato: ");
    scanf("%s", str3);
    char * strDist = validateStrings(str1, str2, str3);
    printf("%s\n", strDist);
    if(strDist == NULL) {
        printf("Input non corretto");
        exit(-1);
    }
    int * sol;
    sol = generateSol(strDist, str1, str2, str3);
    free(sol);
    free(strDist);
}