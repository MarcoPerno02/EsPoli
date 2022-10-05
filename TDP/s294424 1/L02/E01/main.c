#include <stdio.h>

void pulisciBufferTastiera(void);

int main(void)
{
    int vet[2] = {0};
    int i;
    for(i = 0; i < 2; i++) {
        printf("Inserisci numero: ");
        int ris;
        while(ris = scanf("%d", &vet[i]) != 1 || vet[i]<=0)
        {
            printf("Valore non numerico inserito o errato. Riprovare: ");
            pulisciBufferTastiera();
        }
        pulisciBufferTastiera();
        printf("Hai inserito: %d\n", vet[i]);
    }

    int resto;
    int cont = 1;
    do {
        if(vet[0] > vet[1]){
            resto = vet[0] % vet[1];
            printf("Passo %d: %d %% %d = %d", cont, vet[0], vet[1], resto);
            if(resto != 0)
                vet[0] = resto;
            else
                printf("   <- Stop");
        }
        else{
            resto = vet[1] % vet[0];
            printf("Passo %d: %d %% %d = %d", cont, vet[1], vet[0], resto);
            if(resto != 0)
                vet[1] = resto;
            else
                printf("   <- Stop");
        }
        cont++;
        printf("\n");
    } while(resto != 0);

    printf("\nRisultato: MCD = ");
    if(vet[0] > vet[1])
        printf("%d", vet[1]);
    else
        printf("%d", vet[0]);
}

void pulisciBufferTastiera(void) 
{
    /* Pulisco il buffer della tastiera in modo da evitare che nel buffer STDIN rimanga qualche carattere non letto*/
    int c;
    while ( (c = getchar()) != '\n' && c != EOF ) { }
}