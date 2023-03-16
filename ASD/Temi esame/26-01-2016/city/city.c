#include <stdio.h>
#include <stdlib.h>
#include "../city/city.h"

typedef struct {
    char name[21];
    int pop;
    int dist;
} City;

struct cityArray_s {
    City * array;
    int N;
};

CityArray CITYARRAYInit(int N) {
    CityArray cityArray = malloc(sizeof(struct cityArray_s));
    cityArray->N = N;
    cityArray->array = malloc(sizeof(City) * cityArray->N);
}

void CITYARRAYFree(CityArray cityArray) {
    free(cityArray->array);
    free(cityArray);
}

CityArray CITYARRAYLoad(FILE * fin) {
    int N;
    fscanf(fin, "%d", &N);
    CityArray cityArray = CITYARRAYInit(N);
    for(int i = 0; i < N; i++) {
        City tmp;
        fscanf(fin, "%s %d %d", tmp.name, &(tmp.pop), &(tmp.dist));
        cityArray->array[i] = tmp;
    }
    return cityArray;
}

void CalcolaMutuaDistanza(CityArray cityArray) {
    for(int i = 0; i < cityArray->N; i++) {
        printf("Distanza da %s:\n", cityArray->array[i].name);
        for(int j = 0; j < cityArray->N; j++) {
            if(i != j) {
                int dist = cityArray->array[i].dist - cityArray->array[j].dist;
                if(dist < 0) {
                    dist = 0 - dist;
                }
                printf("\t%s: %d\n", cityArray->array[j].name, dist);
            }
        }
    }
}

int SommaDistanze(CityArray cityArray, int * sol, int N_ato) {
    CityArray atoArray = CITYARRAYInit(N_ato);
    atoArray->N = N_ato;
    int cont = 0;
    for(int i = 0; i < cityArray->N; i++) {
        if(sol[i] == 1) {
            atoArray->array[cont] = cityArray->array[i];
            cont++;
        }
    }
    atoArray->N = cont;
    cont = 0;
    int sum = 0;
    for(int i = 0; i < cityArray->N && atoArray->N != 0; i++) {
        int dist1 = atoArray->array[cont].dist -  cityArray->array[i].dist;
        if(dist1 < 0) {
            dist1 = 0 - dist1;
        }
        int dist2;
        if(cont + 1 == atoArray->N) {
            dist2 = dist1;
        }
        else {
            dist2 = atoArray->array[cont+1].dist -  cityArray->array[i].dist;
        }
        
        if(dist2 < 0) {
            dist2 = 0 - dist1;
        }
        int dist_min;
        if(dist2 < dist1) {
            cont++;
            dist_min = dist2;
        }
        else {
            dist_min = dist1;
        }
        sum += cityArray->array[i].pop * dist_min;
    }

    CITYARRAYFree(atoArray);
    return sum;
}

void CalcolaAtoR(int * sol, int pos, int N, int cont_ato, int N_ato, int * best_sol, int * sum_min, CityArray cityArray) {
    if(pos == N) {
        // Terminal case
        for(int i = 0; i < N; i++) {
            printf("%d ", sol[i]);
        }
        printf("\n");
        int sum = SommaDistanze(cityArray, sol, N_ato);
        if(sum != 0 && (sum < *sum_min || *sum_min == -1 )) {
            *sum_min = sum;
            for(int i = 0; i < N; i++) {
                best_sol[i] = sol[i];
            }
        }
    }
    else {
        for(int i = 0; i < 2; i++) {
            sol[pos] = i;
            if(i == 1) {
                if(cont_ato + 1 <= N_ato) {//It is useless to go on beacuse every ato has been used
                    //Add ato to city in pos
                    CalcolaAtoR(sol, pos+1, N, cont_ato + 1, N_ato, best_sol, sum_min, cityArray);
                }
            }
            else {
                CalcolaAtoR(sol, pos+1, N, cont_ato, N_ato, best_sol, sum_min, cityArray);
            }
        }
    }
}

void CalcolaAtoWrapper(CityArray cityArray, int N_ato) {
    int sol[cityArray->N];
    int best_sol[cityArray->N];
    int sum_min = -1;
    CalcolaAtoR(sol, 0, cityArray->N, 0, N_ato, best_sol, &sum_min, cityArray);
    printf("Best sol (sum %d):\n", sum_min);
    for(int i = 0; i < cityArray->N; i++) {
        if(best_sol[i] == 1) {
            printf("%s, ", cityArray->array[i].name);
        }
    }
    printf("\n");

}

