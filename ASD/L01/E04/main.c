#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


typedef enum {
    r_stampa, r_ordinamento_data, r_ordinamento_codice_tratta,
    r_ordinamento_stazione_partenza, r_ordinamento_stazione_arrivo, r_ricerca_dicotomica, r_ricerca_lineare
} t_comandi;

typedef struct
{
    char codiceTratta[30+1];
    char partenza[30+1];
    char capolinea[30+1];
    char date[10+1];
    char oraPartenza[9+1];
    char oraArrivo[9+1];
    int ritardo;

} Tratta;

void pulisciBufferTastiera(void);
t_comandi leggiComando (void);
void caricaTratte(Tratta tratte[], FILE *fLog, int nTratte);
void toLower(char str[]);
void stampaTratta(Tratta tratta);
void caricaVetPuntatori(Tratta * trattePunt[], Tratta tratte[], int N);
void InsertionSortDate(Tratta tratte[], int N, Tratta * tratteInsertionSortDate[]);
void InsertionSortCodiceTratta(Tratta tratte[], int N, Tratta * tratteInsertionSortCodiceTratta[]);
void InsertionSortPartenza(Tratta tratte[], int N, Tratta * tratteInsertionSortPartenza[]);
void InsertionSortCapolinea(Tratta tratte[], int N, Tratta* tratteInsertionSortStazioneArrivo[]);
char * ricercaTrattaDicotomica(Tratta * tratte[], int l, int r, char k[]);
void ricercaLineare(Tratta tratte[], int N, char * k);

int main()
{
    FILE *fLog;
    t_comandi comando;

    if((fLog = fopen("corse.txt", "r")) == NULL) {
        printf("Errore nell'aprire il file corse.txt\n");
        return 1;
    }
    int aus;
    const int nTratte = fscanf(fLog, "%d ", &aus) * aus;
    Tratta tratte[nTratte];
    Tratta * tratteInsertionSorts[4][nTratte];
    for(int i = 0; i < 4; i++) {
        tratteInsertionSorts[i][0] = NULL;
    }
    caricaTratte(tratte, fLog, nTratte);

    do {
        comando = leggiComando();
        switch(comando) {
            case r_stampa:
                for(int i = 0; i < nTratte; i++) {
                    stampaTratta(tratte[i]);
                }
                break;
            case r_ordinamento_data:
                if(tratteInsertionSorts[0][0] == NULL) 
                    InsertionSortDate(tratte, nTratte, tratteInsertionSorts[0]);
                for(int i = 0; i < nTratte; i++) {
                    stampaTratta(*(tratteInsertionSorts[0])[i]);
                }
                break;
            case r_ordinamento_codice_tratta:
                if(tratteInsertionSorts[1][0] == NULL) 
                    InsertionSortCodiceTratta(tratte, nTratte, tratteInsertionSorts[1]);
                for(int i = 0; i < nTratte; i++) {
                    stampaTratta(*(tratteInsertionSorts[1])[i]);
                }
                break;
            case r_ordinamento_stazione_partenza:
                if(tratteInsertionSorts[2][0] == NULL) 
                    InsertionSortPartenza(tratte, nTratte, tratteInsertionSorts[2]);
                for(int i = 0; i < nTratte; i++) {
                    stampaTratta(*(tratteInsertionSorts[2])[i]);
                }
                break;
            case r_ordinamento_stazione_arrivo:
                if(tratteInsertionSorts[3][0] == NULL) 
                    InsertionSortCapolinea(tratte, nTratte, tratteInsertionSorts[3]);
                for(int i = 0; i < nTratte; i++) {
                    stampaTratta(*(tratteInsertionSorts[3])[i]);
                }
                break;
            case r_ricerca_dicotomica:
                char filter[30+1];
                scanf("%s", filter);
                if(tratteInsertionSorts[2][0] == NULL) 
                    InsertionSortPartenza(tratte, nTratte, tratteInsertionSorts[2]);
                printf("%s\n", ricercaTrattaDicotomica(tratteInsertionSorts[2], 0, nTratte-1, filter));
                break;
            case r_ricerca_lineare:
                char filter2[30+1];
                scanf("%s", filter2);
                ricercaLineare(tratte, nTratte, filter2);
                break;
            default:
                break;
        }
        pulisciBufferTastiera();
        //scanf("%*[^\n]%*1[\n]");
    }while(comando != 7);

    fclose(fLog);
    return 0;
}

void pulisciBufferTastiera(void)
{
    /* Pulisco il buffer della tastiera in modo da evitare che nel buffer STDIN rimanga qualche carattere non letto*/
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

t_comandi leggiComando (void) {
    t_comandi c;
    c = 0;
    char cmd[50];
    char tabella[50][30] = {"stampa", "ordinamento_data", "ordinamento_codice_tratta", "ordinamento_stazione_partenza", "ordinamento_stazione_arrivo", "ricerca_dicotomica", "ricerca_lineare", "fine"};
    do {
        c = 0;
        printf("Digitare uno dei seguenti comandi:\n\t- stampa\n\t- ordinamento_data\n\t- ordinamento_codice_tratta \n\t- ordinamento_stazione_partenza \n\t- ordinamento_stazione_arrivo \n\t- ricerca_dicotomica <ricerca>\n\t- ricerca_lineare <ricerca>\n\t- fine\nScelta: ");
        scanf("%s",cmd);
        for(int i = 0; cmd[i]; i++){
            cmd[i] = tolower(cmd[i]);
        }
        while(c<8 && strcmp(cmd,tabella[c])!=0)
            c++;
        if(c == 8) {
            printf("Comando errato.\n");
            pulisciBufferTastiera();
        }
    }while(c==8);
    return (c);
}

void caricaTratte(Tratta tratte[], FILE *fLog, int nTratte) {
    char data[30];
    int ritardo;
    for(int i = 0; i < nTratte; i++) {
        fscanf(fLog, "%s %s %s %s %s %s %d ", tratte[i].codiceTratta, tratte[i].partenza, tratte[i].capolinea, tratte[i].date, tratte[i].oraPartenza, tratte[i].oraArrivo, &tratte[i].ritardo);
    }
}

void toLower(char str[]) {
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

void stampaTratta(Tratta tratta) {
    printf("\t%s, %s %s %s %s %s %d\n", tratta.codiceTratta, tratta.partenza, tratta.capolinea, tratta.date, tratta.oraPartenza, tratta.oraArrivo, tratta.ritardo);
}

void caricaVetPuntatori(Tratta * trattePunt[], Tratta tratte[], int N) 
{
    for(int i = 0; i < N; i++) {
        trattePunt[i] = &tratte[i];
    }
}

void InsertionSortDate(Tratta tratte[], int N, Tratta * tratteInsertionSortDate[])
{
    Tratta x;
    int i, j, l = 0, r = N - 1;
    for (i = l + 1; i <= r; i++)
    {
        x = tratte[i];
        j = i - 1;
        while (j >= l && (strcmp(x.date, tratte[j].date) < 0 || (strcmp(x.date, tratte[j].date) == 0 && strcmp(x.oraPartenza, tratte[j].oraPartenza) < 0)))
        {
            tratte[j + 1] = tratte[j];
            j--;  
        }
        tratte[j + 1] = x;
    }
    caricaVetPuntatori(tratteInsertionSortDate, tratte, N);
}

void InsertionSortCodiceTratta(Tratta tratte[], int N, Tratta * tratteInsertionSortCodiceTratta[])
{
    Tratta x;
    int i, j, l = 0, r = N - 1;
    for (i = l + 1; i <= r; i++)
    {
        x = tratte[i];
        j = i - 1;
        while (j >= l && (strcmp(x.codiceTratta, tratte[j].codiceTratta) < 0 ))
        {
            tratte[j + 1] = tratte[j];
            j--;  
        }
        tratte[j + 1] = x;
    }
    caricaVetPuntatori(tratteInsertionSortCodiceTratta, tratte, N);
}

void InsertionSortPartenza(Tratta tratte[], int N, Tratta * tratteInsertionSortPartenza[])
{
    Tratta x;
    int i, j, l = 0, r = N - 1;
    for (i = l + 1; i <= r; i++)
    {
        x = tratte[i];
        j = i - 1;
        while (j >= l && (strcmp(x.partenza, tratte[j].partenza) < 0 ))
        {
            tratte[j + 1] = tratte[j];
            j--;  
        }
        tratte[j + 1] = x;
    }
    caricaVetPuntatori(tratteInsertionSortPartenza, tratte, N);
}

void InsertionSortCapolinea(Tratta tratte[], int N, Tratta* tratteInsertionSortStazioneArrivo[])
{
    Tratta x;
    int i, j, l = 0, r = N - 1;
    for (i = l + 1; i <= r; i++)
    {
        x = tratte[i];
        j = i - 1;
        while (j >= l && (strcmp(x.capolinea, tratte[j].capolinea) < 0 ))
        {
            tratte[j + 1] = tratte[j];
            j--;  
        }
        tratte[j + 1] = x;
    }
    caricaVetPuntatori(tratteInsertionSortStazioneArrivo, tratte, N);
}

char * ricercaTrattaDicotomica(Tratta * tratte[], int l, int r, char k[]) {
    int m;
    if (l > r)
        return NULL;
    m = (l + r) / 2;
    char * pointer = strstr(tratte[m]->partenza, k);
    if(pointer == tratte[m]->partenza) {
        stampaTratta(*tratte[m]);
        // Find other occurences left side
        int cont = 1, found = 1;
        while(m-cont >= l && found == 1) {
            char * pointer2 = strstr(tratte[m-cont]->partenza, k);
            if(pointer2 == tratte[m-cont]->partenza) {
                stampaTratta(*tratte[m-cont]);
                cont++;
            }
            else {
                found = 0;
            }
        }
        // Find other occurences right side
        cont = 1, found = 1;
        while(m+cont <= r && found == 1) {
            char * pointer2 = strstr(tratte[m+cont]->partenza, k);
            if(pointer2 == tratte[m+cont]->partenza) {
                stampaTratta(*tratte[m+cont]);
                cont++;
            }
            else {
                found = 0;
            }
        }
        return("OK");
    }
    int ris = strcmp(k, tratte[m]->partenza);
    if (ris < 0)
        return ricercaTrattaDicotomica(tratte, l, m - 1, k);
    return ricercaTrattaDicotomica(tratte, m + 1, r, k);
}

void ricercaLineare(Tratta tratte[], int N, char * k) {
    for(int i = 0; i < N; i++) {
        char * pointer = strstr(tratte[i].partenza, k);
        if(pointer == tratte[i].partenza) {
            stampaTratta(tratte[i]);
        }
    }
}
