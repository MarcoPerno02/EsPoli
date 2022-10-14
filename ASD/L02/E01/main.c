#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b);

int main() {
    int a, b;
    printf("Inserisci a: ");
    scanf("%d", &a);
    printf("Inserisci b: ");
    scanf("%d", &b);
    
    printf("%d", gcd(a, b));
}

int gcd(int a, int b)
{   
    if(b > a)
    {
        int aus = a;
        a = b;
        b = aus;   
    }
    if(a == b)
        return a;
    else if(a == 1 || b == 1) 
        return 1;

    if(a == 0 || b == 0) {
        return 1;
    }  
    if(a % 2 == 0 && b % 2 == 0)
    {
        return 2 * gcd(a/2, b/2);
    }
    else if(a % 2 != 0 && b % 2 != 0)
    {
        return gcd((a-b)/2, b);
    }
    else if(a % 2 != 0 && b % 2 == 0)
    {
        return gcd(a, b/2);
    }
    else if(a % 2 == 0 && b % 2 != 0)
    {
        return gcd(a/2, b);
    }
    printf("Errore");/*
    else
    {
        int resto;
        while (b > 0)	{
            resto = a % b;
            a = b;
            b = resto;
        }
        return a;
    }*/
}