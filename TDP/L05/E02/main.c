#include <stdio.h>
#include <string.h>
#include<stdlib.h>

typedef struct
{
    char originale[200+1];
    char ricodifica[200+1];
    int lenParola;
} parola;

char* aggiungiCodifica(char riga[], parola parola, int inizioParola);
int leggiRiga(char riga[], FILE *fp);

int main(void)
{
    FILE *fDizionario;
    fDizionario = fopen("dizionario.txt", "r");
    int aus;
    const int nParole = fscanf(fDizionario, " %d", &aus) * aus;
    parola parole[nParole];
    for (int i = 0; i < nParole; i++)
    {
        fscanf(fDizionario, "%s %s", parole[i].ricodifica, parole[i].originale);
        parole[i].lenParola = strlen(parole[i].originale);
        // printf("%s %s", parole[i].ricodifica, parole[i].originale);
    }

    FILE *fSorgente, *fRicodificato;

    if((fSorgente = fopen("sorgente.txt", "r")) == NULL) {
        printf("Errore nell'aprire il file sorgente.txt\n");
        return 1;
    }
    if((fRicodificato = fopen("ricodificato.txt", "wb")) == NULL) {
        printf("Errore nell'aprire il file ricodificato.txt\n");
        return 1;
    }
    
    char car;
    char* riga;
    riga=(char*)malloc((200+1)*1);
    for(int i = 0; i< 201; i++) {
        riga[i] = '\0';
    }

    int cont = 0;
    int parolaTrovata = 0;
    int eof;
    do
    {
        eof = leggiRiga(riga, fSorgente);      
        for(int i = 0; i < nParole; i++) {
            // Cerco ogni parola nella riga e se la trovo sostituisco la parola con la sua codifica
            for(int j = 0; j < strlen(riga) - parole[i].lenParola + 1; j++) {
                int k = 0;
                while(riga[j+k] == parole[i].originale[k] && k < parole[i].lenParola) {
                    k++;
                }
                if(k == parole[i].lenParola) {
                    riga = aggiungiCodifica(riga, parole[i], j);
                }
            }
            
        }
        fprintf(fRicodificato, "%s\n", riga);
    }while(eof != -1);
    fclose(fDizionario);
    fclose(fRicodificato);
    return 0;
}

char* aggiungiCodifica(char* riga, parola parola, int inizioParola)
{

    int len_parola = parola.lenParola;
    int len_ricodifica = strlen(parola.ricodifica);
    char* nuovaRiga;
    nuovaRiga=(char*)malloc((200+1)*1);
    
    int i;
    for(i = 0; i < inizioParola; i++) {
        nuovaRiga[i] = riga[i];
    }
    int j;
    for(j = 0; j < len_ricodifica; j++) {
        nuovaRiga[i+j] = parola.ricodifica[j];
    }
    for(int k = i+len_parola; riga[k] != '\0'; k++) {
        nuovaRiga[i+j] = riga[k];
        j++;
    }
    nuovaRiga[i+j] = '\0';
    return nuovaRiga;
    
}

int leggiRiga(char riga[], FILE *fp) {
    char car;
    int i = 0;
    int ris;
    while ((ris = fscanf(fp, "%c", &car)) != -1 && car !='\n') {// && car !='\n'
        riga[i] = car;
        i++;
    }
    riga[i] = '\0';
    return ris;
}