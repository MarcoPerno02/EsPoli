#include <stdint.h>

// Dichiarazione della funzione assembly `call_svc`
extern void call_svc(void);

// Funzione principale
int main(void) {
    volatile uint32_t result;  // Variabile per memorizzare il risultato della SVC

    // Richiama l'istruzione SVC tramite call_svc
    call_svc();

    // Recupera il risultato dallo stack
    // Nota: questa parte dipende da come il risultato è stato gestito nell'SVC_Handler.
    // Qui assumiamo che il valore sia restituito nel registro R0
    asm volatile (
        "MOV %0, R0\n"          // Sposta il contenuto di R0 nella variabile result
        : "=r" (result)         // Output: assegna il valore di R0 a result
    );

    // Usa il risultato (ad esempio, per debug o altre operazioni)
    while (1) {
        // In un sistema embedded, potresti aggiungere codice per esaminare il risultato.
			printf("%d\n", result);
    }

    return 0;
}
