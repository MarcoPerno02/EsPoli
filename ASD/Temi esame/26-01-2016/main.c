#include <stdio.h>
#include <stdlib.h>
#include "city/city.h"

int main() {
    FILE * fin;
    fin = fopen("citta.txt", "r");
    CityArray cityArray = CITYARRAYLoad(fin);
    fclose(fin);
    CalcolaMutuaDistanza(cityArray);
    CalcolaAtoWrapper(cityArray, 4);
    CITYARRAYFree(cityArray);
}
