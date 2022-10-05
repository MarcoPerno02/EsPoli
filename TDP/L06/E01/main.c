#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct
{
    int year;
    int month;
    int day;
} Date;

typedef struct
{
    char time[9+1];
} Time;

typedef enum {
    r_date, r_partenza, r_capolinea,
    r_ritardo, r_ritardo_tot, r_fine
} t_comandi;

typedef struct
{
    char codiceTratta[30+1];
    char partenza[30+1];
    char capolinea[30+1];
    Date date;
    Time oraPartenza;
    Time oraArrivo;
    int ritardo;

} Tratta;

void pulisciBufferTastiera(void);
t_comandi leggiComando (void);
void caricaTratte(Tratta tratte[], FILE *fLog, int nTratte);
int splitData(Date* date, char *date_str, char dateFormat[]);
int controlloDataCompresa(Date data, Date data_max, Date data_min);
void toLower(char str[]);
void stampaTratta(Tratta tratta);
void comandoDate(Tratta tratte[], int nTratte);
void comandoPartenza(Tratta tratte[], int nTratte);
void comandoCapolinea(Tratta tratte[], int nTratte);
void comandoRitardo(Tratta tratte[], int nTratte);
void comandoRitardoTot(Tratta tratte[], int nTratte);

int main()
{
    FILE *fLog;
    t_comandi comando;

    if((fLog = fopen("log.txt", "r")) == NULL) {
        printf("Errore nell'aprire il file log.txt\n");
        return 1;
    }
    int aus;
    const int nTratte = fscanf(fLog, "%d ", &aus) * aus;
    Tratta tratte[nTratte];
    caricaTratte(tratte, fLog, nTratte);

    do {
        comando = leggiComando();
        switch(comando) {
            case r_date:
                comandoDate(tratte, nTratte);
                break;
            case r_partenza:
                comandoPartenza(tratte, nTratte);
                break;
            case r_capolinea:
                comandoCapolinea(tratte, nTratte);
                break;
            case r_ritardo:
                comandoRitardo(tratte, nTratte);
                break;
            case r_ritardo_tot:
                comandoRitardoTot(tratte, nTratte);
                break;
            default:
                break;
        }
        pulisciBufferTastiera();
        //scanf("%*[^\n]%*1[\n]");
    }while(comando != 5);

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
    char tabella[50][15] = {
        "date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};
    do {
        printf("Digitare uno dei seguenti comandi:\n\t- date <dataInizio> <dataFine>\n\t- partenza <nomeFermata>\n\t- capolinea <nomeCapolinea>\n\t- ritardo <nomeDestinazione> <dataInizio> <dataFine>\n\t- ritardo_tot <codiceTratta>\n\t- fine\nScelta: ");
        scanf("%s",cmd);
        for(int i = 0; cmd[i]; i++){
            cmd[i] = tolower(cmd[i]);
        }
        while(c<6 && strcmp(cmd,tabella[c])!=0)
            c++;
        if(c == 6) {
            printf("Comando errato.\n");
            pulisciBufferTastiera();
        }
    }while(c==6);
    return (c);
}

void caricaTratte(Tratta tratte[], FILE *fLog, int nTratte) {
    char data[30];
    int ritardo;
    for(int i = 0; i < nTratte; i++) {
        fscanf(fLog, "%s %s %s %s %s %s %d ", tratte[i].codiceTratta, tratte[i].partenza, tratte[i].capolinea, data, tratte[i].oraPartenza.time, tratte[i].oraArrivo.time, &tratte[i].ritardo);
        // Si ignora il valore di ritorno perchè si suppone che il file non abbia errori
        splitData(&tratte[i].date, data, "%d/%d/%d");
    }
}

int splitData(Date* date, char date_str[], char dateFormat[])
{
    int month;
    int year;
    int day;

    if (sscanf(date_str, dateFormat, &year, &month, &day) == 3)
    {
        // check year
        if (year >= 1900 && year <= 9999)
        {
            // check month
            if (month >= 1 && month <= 12)
            {
                // check days
                if (((day >= 1 && day <= 31) && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)) || ((day >= 1 && day <= 30) && (month == 4 || month == 6 || month == 9 || month == 11)) || (day == 29 && month == 2 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))))
                    date->year = year;
                    date->month = month;
                    date->day = day;
                    return 0;
            }
        }
    }
    return -1;
}

int controlloDataCompresa(Date data, Date data_max, Date data_min) {
    // Ritorna 1 se ok, altrimenti 0
    // Controllo che la data_min sia piu piccola della data della tratte
    int ok = 0;
    if(data_min.year < data.year) {
        ok = 1;
    }
    else if(data_min.year == data.year) {
        if(data_min.month < data.month) {
            ok = 1;
        }
        else if(data_min.month == data.month) {
            if(data_min.day <= data.day) {
                ok = 1;
            }
        }
    }

    if(ok == 1) {
        // Controllo che la data_max sia piu grande della data della tratte
        ok = 0;
        if(data_max.year > data.year) {
            ok = 1;
        }
        else if(data_max.year == data.year) {
            if(data_max.month > data.month) {
                ok = 1;
            }
            else if(data_max.month == data.month) {
                if(data_max.day >= data.day) {
                    ok = 1;
                }
            }
        }
    }
    return ok;
}

void toLower(char str[]) {
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

void stampaTratta(Tratta tratta) {
    printf("\t%s, %s %s %d/%d/%d %s %s %d\n", tratta.codiceTratta, tratta.partenza, tratta.capolinea, tratta.date.year, tratta.date.month, tratta.date.day, tratta.oraPartenza.time, tratta.oraArrivo.time, tratta.ritardo);
}

void comandoDate(Tratta tratte[], int nTratte) {
    Date date_min, date_max;
    char date_min_str[50], date_max_str[50];

    if(scanf("%s %s", &date_min_str, &date_max_str) == 2) {
        if(splitData(&date_min, date_min_str, "%d/%d/%d") == 0 && splitData(&date_max, date_max_str, "%d/%d/%d") == 0) {
            printf("Risultati:\n");
            for(int i = 0; i < nTratte; i++) {
                int ok = controlloDataCompresa(tratte[i].date, date_max, date_min);
                if(ok == 1) {
                    stampaTratta(tratte[i]);
                }
            }
            printf("Terminato.\n");
        }
        else {
            printf("Parametri succesivi al comando incorretti\n");
        }
    }
    else 
        printf("Parametri succesivi al comando incorretti\n");
}

void comandoPartenza(Tratta tratte[], int nTratte) {
    char partenza[30+1], partenzaTratta[30+1];
    if(scanf("%s", partenza) == 1) {
        toLower(partenza);
        printf("Risultati:\n");
        for(int i = 0; i < nTratte; i++) {
            strcpy(partenzaTratta, tratte[i].partenza);
            toLower(partenzaTratta);
            if(strcmp(partenzaTratta, partenza) == 0) {
                stampaTratta(tratte[i]);
            }
        }
        printf("Terminato.\n");
    }
    else
        printf("Parametri errati.\n");
}

void comandoCapolinea(Tratta tratte[], int nTratte) {
    char capolinea[30+1], capolineaTratta[30+1];
    if(scanf("%s", capolinea) == 1) {
        toLower(capolinea);
        printf("Risultati:\n");
        for(int i = 0; i < nTratte; i++) {
            strcpy(capolineaTratta, tratte[i].capolinea);
            toLower(capolineaTratta);
            if(strcmp(capolineaTratta, capolinea) == 0) {
                stampaTratta(tratte[i]);
            }
        }
        printf("Terminato.\n");
    }
    else
        printf("Parametri errati.\n");
}

void comandoRitardo(Tratta tratte[], int nTratte) {
    Date date_min, date_max;
    char date_min_str[50], date_max_str[50], capolinea[50], capolineaTratta[50];

    if(scanf("%s %s %s", &capolinea, &date_min_str, &date_max_str) == 3) {
        if(splitData(&date_min, date_min_str, "%d/%d/%d") == 0 && splitData(&date_max, date_max_str, "%d/%d/%d") == 0) {
            printf("Risultati:\n");
            for(int i = 0; i < nTratte; i++) {
                int ok = controlloDataCompresa(tratte[i].date, date_max, date_min);
                if(ok == 1) {
                    toLower(capolinea);
                    char capolineaTratta[30+1];
                    strcpy(capolineaTratta, tratte[i].capolinea);
                    toLower(capolineaTratta);
                    if(strcmp(capolineaTratta, capolinea) == 0 && tratte[i].ritardo != 0)
                        stampaTratta(tratte[i]);
                }
            }
            printf("Terminato.\n");
        }
        else {
            printf("Parametri succesivi al comando incorretti\n");
        }
    }
    else 
        printf("Parametri succesivi al comando incorretti\n");
}

void comandoRitardoTot(Tratta tratte[], int nTratte) {
    char codice[30+1];
    char codiceTratta[30+1];
    if(scanf("%s", &codice) == 1) {
        printf("Risultati:\n");
        int ritardo_tot = 0;
        for(int i = 0; i < nTratte; i++) {
            toLower(codice);
            strcpy(codiceTratta, tratte[i].codiceTratta);
            toLower(codiceTratta);
            if(strcmp(codiceTratta, codice) == 0)
                ritardo_tot += tratte[i].ritardo;
        }
        printf("Ritardo_tot: %d\n", ritardo_tot);
        printf("Terminato.\n");
    }
    else 
        printf("Parametri succesivi al comando incorretti\n");
}