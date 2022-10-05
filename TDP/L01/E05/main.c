#include <stdio.h>

void pulisciBufferTastiera(void);

int main(void)
{
    float x, y;
    char operatore;

    do{
        printf("Inserisci operazione da eseguire: ");
        operatore = getchar();
        pulisciBufferTastiera();
    }while(operatore != '+' && operatore != '-' && operatore != '*' && operatore != '/');
    printf("%c\n", operatore);

    printf("Inserisci primo valore: ");
    while(scanf(" %f", &x) != 1)
    {
        printf("Valore non numerico inserito. Riprovare: ");
        pulisciBufferTastiera();
    }
    pulisciBufferTastiera();
    printf("Hai inserito: %f\n", x);

    printf("Inserisci secondo valore: ");
    while(scanf(" %f", &y) != 1)
    {
        printf("Valore non numerico inserito. Riprovare: ");
        pulisciBufferTastiera();
    }
    pulisciBufferTastiera();
    printf("Hai inserito: %f\n", y);

    switch (operatore)
    {
        case '+':
            printf("+ %f", x+y);
            break;
        case '-':
            printf("- %f", x-y);
            break;
        case '*':
            printf("* %f", x*y);
            break;
        case '/':
            if(y == 0)
                printf("Impossibile effettuare una divisione per 0.");
            else
                printf("/ %f", x/y);
            break;
        default:
            printf("Hai inserito un operatore non riconosciuto.");
            break;
    }
}

void pulisciBufferTastiera(void) 
{
    /* Pulisco il buffer della tastiera in modo da evitare che nel buffer STDIN rimanga qualche carattere non letto*/
    int c;
    while ( (c = getchar()) != '\n' && c != EOF ) { }
}