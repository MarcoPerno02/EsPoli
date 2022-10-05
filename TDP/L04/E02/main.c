#include <stdio.h>
#define maxN 30
void ruota(int v[maxN], int N, int P, int dir);
void stampaVet(int v[], int N);

void pulisciBufferTastiera(void);

int main(void)
{
    FILE *finput;
    int vet[maxN];
    int len_vet = 0;
    int ris_lettura = 0;
    do {
        printf("Inserisci numero o un carattere per uscire: ");
        ris_lettura = scanf(" %d", &vet[len_vet]);
        if(ris_lettura > 0) 
            len_vet++;
        pulisciBufferTastiera();
    }while(len_vet < maxN && ris_lettura > 0);

    stampaVet(vet, len_vet);
    
    int passi = -1;
    if(len_vet >= 2) {
        do {
            // Gestione direzione
            int dir = 0;
            do {
                printf("Premere -1 per destra, 1 per sinistra: ");
                ris_lettura = scanf(" %d", &dir);
                if(ris_lettura > 0) {
                    if(dir != 1 && dir != -1)
                        printf("Direzione non corretta\n");
                }
                pulisciBufferTastiera();
            } while(dir != 1 && dir != -1);

            // Gestione passi
            do {
                printf("Inserire num passi, 0 per uscire: ");
                ris_lettura = scanf(" %d", &passi);
                if(ris_lettura > 0) {
                    if(passi < 0)
                        printf("Passi non corretti\n");
                }
                pulisciBufferTastiera();
            } while(passi < 0);

            //Gestione passi su vettore
            if(passi != 0) {
                ruota(vet, len_vet, passi, dir);
            }

        } while(passi != 0);
    }
    else {
        printf("Dimensione vettore non sufficiente.");
    }
    
    return 0;
}

void ruota(int v[maxN], int N, int P, int dir) {
    int v_aus[maxN];
    for(int i = 0; i < N; i++) {
        v_aus[i] = v[i];
    }
    for (int i = 0; i < N; i++)
    {
        if(dir == 1) {
            // Gestione sinistra
            int new_pos = i - P;
            while(new_pos < 0) {
                new_pos += N;
            }
            v[new_pos] = v_aus[i];
        }
        else {
            // Gestione destra
            int new_pos = i + P;
            while(new_pos >= N) {
                new_pos -= N;
            }
            v[new_pos] = v_aus[i];
        }
    }
    stampaVet(v, N);
    

}

void stampaVet(int v[], int N) {
    printf("[");
    for(int i = 0; i < N; i++) {
        printf("%d ", v[i]);
    }
    printf("]\n");
}

void pulisciBufferTastiera(void) 
{
    /* Pulisco il buffer della tastiera in modo da evitare che nel buffer STDIN rimanga qualche carattere non letto*/
    int c;
    while ( (c = getchar()) != '\n' && c != EOF ) { }
}