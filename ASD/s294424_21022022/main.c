#include <stdio.h>
#include <stdlib.h>
#include "person.h"
#include "activity.h"

int main() {
    FILE * fin;
    fin = fopen("input.txt", "r");
    Activity_Wrapper a_wrapper = ACTIVITYLoad(fin);
    Person_Wrapper p_wrapper = PERSONLoad(fin);
    int ** mat = PERSONBuildMat(fin, p_wrapper);
    fclose(fin);
    printf("Leggere soluzione o generare(0 o 1)? ");
    int choice;
    fscanf(stdin, "%d", &choice);
    if(choice == 0) {
        fin = fopen("proposta.txt", "r");
        ReadFileSol(fin, p_wrapper, a_wrapper, mat);
        fclose(fin);
    }
    else {
        FindBestSol(p_wrapper, a_wrapper, mat);
    }
    PERSONFree(p_wrapper, mat);
    ACTIVITYFree(a_wrapper);
}