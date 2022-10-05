#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void compressString(char *testo) {
    printf("%c", testo[0]);
    char aus = testo[0];
    int cont = 1;
    for(int i = 1; i< strlen(testo); i++) {
        if(testo[i] == aus)
            cont++;
        else {
            if(cont != 1) {
                printf("%d", cont);
            }
            cont = 1;
            aus = testo[i];
            printf("%c", aus);
        }
    }
    if(cont != 1) {
        printf("%d", cont);
    }
}

int main() {
    char testo[50] = "abbabbbaAAAAAaCCaDDDeeeF";
    compressString(testo);
}