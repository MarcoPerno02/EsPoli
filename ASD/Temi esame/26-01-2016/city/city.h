#ifndef CITY_H_DEFINED
#define CITY_H_DEFINED
#include <stdio.h>
#include <stdlib.h>

typedef struct cityArray_s * CityArray;
CityArray CITYARRAYLoad(FILE * fin);
void CITYARRAYFree(CityArray cityArray);
void CalcolaMutuaDistanza(CityArray cityArray);
void CalcolaAtoWrapper(CityArray cityArray, int N_ato);

#endif