#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../calculator/calculator.h"

int addUnqueLetter(char * sol, int * cont, char * str) {
    for(int i = 0; i < strlen(str) && *cont != -1; i++) {
        int j = 0;
        while(j < *cont && sol[j] != str[i]) {
            j++;
        }
        if(j == *cont) {
            if(*cont != 10) {
                sol[*cont] = str[i];
                (*cont)++;
            }
            else {
                *cont = -1;
            }
        }
        
    }
}

char * validateStrings(char * str1, char * str2, char* str3) {
    char * sol = malloc(sizeof(char)*11);
    for(int i = 0; i < 11; i++) {
        sol[i] = '\0';
    }
    int cont = 0;
    addUnqueLetter(sol, &cont, str1);
    if(cont != -1) {
        addUnqueLetter(sol, &cont, str2);
        if(cont != -1)  {
            addUnqueLetter(sol, &cont, str3);
            if(cont != -1) {
                return sol;
            }
        }
    }
    free(sol);
    return NULL;
}

int getCharIndexInString(char test, char * str) {
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] == test)
            return i;
    }

}

int generateNumber(char * str, char * strDist, int * test_sol) {
    int num = 0;
    for(int i = 0; i < strlen(str); i++) {
        int idx = getCharIndexInString(str[i], strDist);
        int num_to_add = test_sol[idx];
        int base = 1;
        for(int j = i; j < strlen(str) - 1; j++) {
            base *= 10;
        }
        num_to_add *= base;
        num += num_to_add;
    }
    return num;
}

void disp_simp(int * test_sol, int * mark, int pos, char * strDist, int * number_sol, char * str1, char * str2, char * str3, int * exit) {
    if(pos == strlen(strDist)){
        // Terminal case
        /*for(int i = 0; i < strlen(strDist); i++) {
                printf("%d ", test_sol[i]);
            }
        printf("\n");*/
        /*test_sol[0] = 9;
        test_sol[1] = 5;
        test_sol[2] = 6;
        test_sol[3] = 7;
        test_sol[4] = 1;
        test_sol[5] = 0;
        test_sol[6] = 8;
        test_sol[7] = 2;*/
        int num1 = generateNumber(str1, strDist, test_sol);
        int num2 = generateNumber(str2, strDist, test_sol);
        int num3 = generateNumber(str3, strDist, test_sol);
        if(num1 + num2 == num3) {
            *exit = 1;
            number_sol = test_sol;
            for(int i = 0; i < strlen(strDist); i++) {
                    printf("%d ", test_sol[i]);
                }
            printf("\n");
        }
        
    }
    else {
        for(int i = 0; i < 10 && *exit != 1; i++) {
            if(mark[i] == 0) {
                if(i != 0 || (i == 0 && pos != 0)) {
                    if( i != 0 || (i == 0 && strDist[pos] != str2[0])) {
                        test_sol[pos] = i;
                        mark[i] = 1;
                        disp_simp(test_sol, mark, pos + 1, strDist, number_sol, str1, str2, str3, exit);
                        mark[i] = 0;
                    }
                }
            }
        }
    }
}

int * generateSol(char * strDist, char * str1, char * str2, char * str3) {
    int * numbers_sol;
    int * test_sol = malloc(strlen(strDist)*sizeof(int));
    int * mark = malloc(10*sizeof(int));
    for(int i = 0; i < 10; i++){
        mark[i] = 0;
    }
    int exit = 0;
    disp_simp(test_sol, mark, 0, strDist, numbers_sol, str1, str2, str3, &exit);
    if(exit == 0) {
        free(test_sol);
        return NULL;
    }
    else {
        return numbers_sol;
    }
}