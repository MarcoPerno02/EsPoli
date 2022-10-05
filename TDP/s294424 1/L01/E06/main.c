#include <stdio.h>

void pulisciBufferTastiera(void);

int main(void)
{
    FILE *fInput;
    FILE *fOutput;
    float x, y;
    char operatore;

    /* Suppongo che il contenuto del file non presenti errori di scrittura o logici come divisione per 0 visto che il compilatore restituisce inf, ma quello sarebbe il risultato del limite*/
    if((fInput = fopen("Operations.txt", "r")) == NULL)
    {
        printf("Errore nell'aprire il file Operations.txt\n");
        return 1;
    }
    if((fOutput = fopen("Results.txt", "wb")) == NULL)
    {
        printf("Errore nell'aprire il file Results.txt\n");
        return 1;
    }

    while (fscanf(fInput, "%c %f %f ", &operatore, &x, &y) != EOF) {
        float risultato;
        switch (operatore)
        {
            case '+':
                risultato = x+y;
                break;
            case '-':
                risultato = x-y;
                break;
            case '*':
                risultato = x*y;
                break;
            default:
                risultato = x/y;
                break;
        }
        fprintf(fOutput, "%c %0.2f\n",operatore, risultato);
    }
    fclose(fInput);
    fclose(fOutput);
}

void pulisciBufferTastiera(void) 
{
    /* Pulisco il buffer della tastiera in modo da evitare che nel buffer STDIN rimanga qualche carattere non letto*/
    int c;
    while ( (c = getchar()) != '\n' && c != EOF ) { }
}
