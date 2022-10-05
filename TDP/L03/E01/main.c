#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define INPUT "input.txt"
#define OUTPUT "output.txt"

void aggiungiCarattereARigaEFile(char *riga, char carattere, int *indice_riga, FILE *foutput, int *cont, int carattere_vero);

int main(void)
{
    FILE *finput, *foutput;
    char riga[25] = "";
    int indice_riga = 0;
    int cont = 0;
    char carattere;

    if((finput = fopen(INPUT , "r")) == NULL) {
        printf("Errore nell'aprire il file %s\n", INPUT);
        return 1;
    }
    if((foutput = fopen(OUTPUT, "wb")) == NULL) {
        printf("Errore nell'aprire il file %s\n", OUTPUT);
        return 1;
    }
    
    while(fscanf(finput, "%c", &carattere) != -1) {
        // Controllo se è un numero grazie al codice ascii
        if(carattere >= 48 && carattere <= 59) {
            aggiungiCarattereARigaEFile(riga, '*', &indice_riga, foutput, &cont, 0);
        }
        else if(carattere == '.' || carattere == ',' || carattere == ';' || carattere == ':' || carattere == '!' || carattere == '?' || carattere == '\'' || carattere == '(' || carattere == ')') {
            aggiungiCarattereARigaEFile(riga, carattere, &indice_riga, foutput, &cont, 0);
            char carattere_aus;
            if(fscanf(finput, "%c", &carattere_aus) != -1) {
                if(carattere == '?' || carattere == '.' || carattere == '!') {
                    if(carattere == '.') {
                        aggiungiCarattereARigaEFile(riga, ' ', &indice_riga, foutput, &cont, 0);
                        for(;indice_riga!=0;) {
                            aggiungiCarattereARigaEFile(riga, ' ', &indice_riga, foutput, &cont, 1);
                        }
                    }
                    else {
                        aggiungiCarattereARigaEFile(riga, ' ', &indice_riga, foutput, &cont, 1);
                    }
                    if(carattere_aus != '\n' && carattere_aus != ' ')
                        aggiungiCarattereARigaEFile(riga, toupper(carattere_aus), &indice_riga, foutput, &cont, 0);
                    else {
                        if(fscanf(finput, "%c", &carattere_aus) != -1)
                            aggiungiCarattereARigaEFile(riga, toupper(carattere_aus), &indice_riga, foutput, &cont, 0);
                    }
                }
                else if(carattere_aus != ' ' && carattere_aus != '\n') {
                    aggiungiCarattereARigaEFile(riga, ' ', &indice_riga, foutput, &cont, 1);
                    aggiungiCarattereARigaEFile(riga, carattere_aus, &indice_riga, foutput, &cont, 0);
                } 
                else {
                    aggiungiCarattereARigaEFile(riga, carattere_aus, &indice_riga, foutput, &cont, 0);
                }
            }
        }
        else if(carattere == '\n') {
            aggiungiCarattereARigaEFile(riga, ' ', &indice_riga, foutput, &cont, 0);
            for(;indice_riga!=0;) {
                aggiungiCarattereARigaEFile(riga, ' ', &indice_riga, foutput, &cont, 1);
            }
        }
        else {
            aggiungiCarattereARigaEFile(riga, carattere, &indice_riga, foutput, &cont, 0);
        }
    }
    if(riga[0] != '\0') {
        aggiungiCarattereARigaEFile(riga, ' ', &indice_riga, foutput, &cont, 0);
        for(;indice_riga!=0;) {
            aggiungiCarattereARigaEFile(riga, ' ', &indice_riga, foutput, &cont, 1);
        }
    }

    fclose(finput);
    fclose(foutput);
    return 0;
}

void aggiungiCarattereARigaEFile(char *riga, char carattere, int *indice_riga, FILE *foutput, int *cont, int carattere_vero) {
    riga[*indice_riga] = carattere;
    *indice_riga += 1;
    if(carattere_vero == 0)
        *cont += 1;
    if(*indice_riga == 25) {
        char result[31+1];
        // Conta num caratteri
        char int_to_str[3];
        sprintf(int_to_str, "%d", *cont);
        strcpy(result, riga);
        strcat(result, "| c:");
        strcat(result, int_to_str);
        strcat(result, "\n");
        fprintf(foutput, "%s", result);
        *indice_riga = 0;
        *cont = 0;
        memset(riga,0,27);
    }
}