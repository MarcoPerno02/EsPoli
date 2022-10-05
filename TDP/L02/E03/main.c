#include <stdio.h>
#include <stdlib.h>

void pulisciBufferTastiera(void);
int comprimi(FILE *fin, FILE *fout);
int decomprimi(FILE *fin, FILE *fout);

int main(void)
{
    FILE *fin;
    FILE *fout;
    char riga[255];
    int scelta;
    char file_names[3][50] = {{"sorgente.txt"}, {"compresso.txt"}, {"decompresso.txt"}};

    printf("Inserisci scelta(0 comprimi, 1 decomprimi): ");
    while(scanf("%d", &scelta) != 1 || scelta<0 || scelta >1) {
        printf("Valore non numerico inserito o errato inserito. Riprovare: ");
        pulisciBufferTastiera();
    }
    
    if((fin = fopen(file_names[scelta] , "r")) == NULL) {
        printf("Errore nell'aprire il file %s\n", file_names[scelta]);
        return 1;
    }
    if((fout = fopen(file_names[scelta+1], "wb")) == NULL) {
        printf("Errore nell'aprire il file %s\n", file_names[scelta+1]);
        return 1;
    }

    if(scelta == 0) printf("Num caratteri scritti: %d", comprimi(fin, fout));
    else printf("Num caratteri scritti: %d", decomprimi(fin, fout));

    fclose(fin);
    fclose(fout);
}

int comprimi(FILE *fin, FILE *fout) {
    char c1, c2;
    int num_caratteri_scritti = 0, eof = 1;// Flag eof per determinare quando la fscanf legge eof perchè ritornerà -1
    eof = fscanf(fin, "%c", &c1);
    while(eof == 1) {
        int cont = 0;
        //Quando si esce dal ciclo c2 punta sempre al carettere successivo da cui riprendere la compressione
        eof = fscanf(fin, "%c", &c2);
        while(c1 == c2 && c2 != '\0' && cont != 9 && eof == 1) {
            cont++;
            eof = fscanf(fin, "%c", &c2);
        }

        if(cont == 0 || cont == 1) {
            for(int i = 0; i < cont + 1; i++) {
                fprintf(fout, "%c", c1);
                num_caratteri_scritti++;
            }
        }
        else {
            fprintf(fout, "%c$", c1);
            fprintf(fout, "%d", cont);
            num_caratteri_scritti += 3;
        }
        c1 = c2;
    }
    return num_caratteri_scritti;
}

int decomprimi(FILE *fin, FILE *fout) {
    char c1, c2;
    int num_caratteri_scritti = 0, eof = 1;// Flag eof per determinare quando la fscanf legge eof perchè ritornerà -1
    eof = fscanf(fin, "%c", &c1);
    while(eof == 1) {
        eof = fscanf(fin, "%c", &c2);
        int cont = 0;
        if(c2 == '$') {
            char cont_char;
            eof = fscanf(fin, "%c", &cont_char);
            cont = atoi(&cont_char);
            eof = fscanf(fin, "%c", &c2);
        }
        for(int i = 0; i < cont + 1; i++) {
            fprintf(fout, "%c", c1);
            num_caratteri_scritti++;
        }
        c1 = c2;
    }
    return num_caratteri_scritti;
}

void pulisciBufferTastiera(void) {
    /* Pulisco il buffer della tastiera in modo da evitare che nel buffer STDIN rimanga qualche carattere non letto*/
    int c;
    while ( (c = getchar()) != '\n' && c != EOF ) { }
}