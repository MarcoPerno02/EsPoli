#include <stdio.h>
#include <stdlib.h>

#define LENGTH 7
int majority(int *a, int N);
int checkNumber(int *vet, int elem, int index, int * occurences, int N);

int main() 
{
    FILE *fLog;
    int aus;
    int vet [] = {7, 10, 8, 8, 8, 7, 8};
    int res = majority(vet, LENGTH);
    if(res != -1)
        printf("Elemento maggioritario: %d", res);
    else
        printf("Nessun elemento maggioritario");
    return 0;
}

int majority( int *a, int N) 
{
    int occurences;
    int i = 0;
    do 
    {
        occurences = 0;
        checkNumber(a, a[i], 0, &occurences, N);
        i++;
    } while(occurences <= N/2 && i < N);
    if(occurences > N/2)
        return a[i-1];
    else
        return -1;
}

int checkNumber(int *vet, int elem, int index, int * occurences, int N) {
    if(vet[index] == elem)  
        *occurences += 1;
    index += 1;
    if(index < N)
        checkNumber(vet, elem, index, occurences, N);
}