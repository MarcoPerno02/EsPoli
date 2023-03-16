#include <stdio.h>
#include <stdlib.h>
#include "person.h"
#include "activity.h"

typedef struct {
    int id; // corrispondennza id pos per sicurezza
    int exp;
    int available;
} Person;

struct person_wrapper_s {
    int N;
    Person * vett;
};

Person_Wrapper PERSONLoad(FILE * fin) {
    int N;
    fscanf(fin, "%d", &N);
    Person_Wrapper p_wrapper = malloc(sizeof(struct person_wrapper_s));
    p_wrapper->vett = malloc(sizeof(Person)*N);
    p_wrapper->N = N;
    for(int i = 0; i < N; i++) {
        p_wrapper->vett[i].id = i;
        fscanf(fin, "%d", &(p_wrapper->vett[i].exp));
        p_wrapper->vett[i].available = 1;
    }
    return p_wrapper;
}

// Salva in *vet_sol tutte le combinazioni generate
void generateComb(int * sol, int start, int pos, int * val, int N, int k, int *** vett_sol, int * cont_vett_sol, int * N_vett_sol) {// dimenticato * davanti a cont_vett_sol e start ERRORE
    if (pos == k)
    {
        // Terminal case
        // Salvataggio della soluzione nel *vett_sol
        if (*N_vett_sol == *cont_vett_sol)
        {
            *N_vett_sol *= 2;
            *vett_sol = realloc(*vett_sol, *N_vett_sol * sizeof(int *));
        }
        (*vett_sol)[*cont_vett_sol] = malloc(sizeof(int) * k);
        for (int i = 0; i < k; i++)
        {
            (*vett_sol)[*cont_vett_sol][i] = sol[i]; // dimenticato * ERRORE
        }
        *cont_vett_sol += 1; // dimticato di incrementare ERRORE
    }
    else
    {
        for (int i = start; i < N; i++)
        {
            sol[pos] = val[i];
            generateComb(sol, i, pos + 1, val, N, k, vett_sol, cont_vett_sol, N_vett_sol);
        }
    }
}

// Ritorna il valore delle sinergie generate dal personale
int searchSinergie(int * person, int N_person, int **mat) {
    if (N_person == 1)
        return 0;
    int sinergie = 0;
    int N_comb_person = 1;
    // Salvo in comb_person tutte le combinazioni da 2 del personale
    int **comb_person = malloc(sizeof(int *) * 2);
    comb_person[0] = malloc(sizeof(int) * 2);// 0 e non 1 ERRORE
    int cont_comb_person = 0;
    int sol[2];
    generateComb(sol, 0, 0, person, N_person, 2, &comb_person, &cont_comb_person, &N_comb_person);// al posto di pos volevo mettere 0 ERRORE
    for (int i = 0; i < cont_comb_person; i++)
    {
        sinergie += mat[comb_person[i][0]][comb_person[i][1]]; // sbagliato ad accedere ERRORE
    }
    // sbagliato dove mettere la free ERRORE
    for (int i = 0; i < cont_comb_person; i++)// cont_comb_person e non N_comb_person ERRORE
    {
        free(comb_person[i]);
    }
    free(comb_person);
    return sinergie;
}

// Ritorna l'exp necessaria per l'attività se i criteri sono soddisfatti, altrimenti -1
int verify(int *person, int N_person, int id_activity, Person_Wrapper p_wrapper, Activity_Wrapper a_wrapper, int **mat)
{
    // Calcolo sinergie
    int punt = searchSinergie(person, N_person, mat);
    int valid = 1;
    for (int i = 0; i < N_person && valid == 1; i++)
    {
        if (p_wrapper->vett[person[i]].available == 0) { // volevo accedere a p_wrapper ERRORE
            valid = 0;
        }
        else
        {
            punt += p_wrapper->vett[person[i]].exp;
        }
    }
    float punt_min = a_wrapper->vett[id_activity].diff; // salvo in un float ERRORE
    punt_min = punt_min / 100 * 75;
    // Smarco ogni persona
    for (int i = 0; i < N_person; i++)
    {
        p_wrapper->vett[i].available = 1;
    }
    // Verifica finale
    if (valid == 1 && punt >= punt_min) // dimenticato di accedere a diff ERRORE
        if(punt >= a_wrapper->vett[id_activity].diff )
            return a_wrapper->vett[id_activity].diff;
        else
            return punt;
    return - 1;
}

// Lettura proposta (si suppone che gli id delle persone e attività esistano)
/*
Es. contenuto p_sol = {0, 1} ---> significa persone con id 0 e 1 assegnate a "id_activity" attività
*/
void ReadFileSol(FILE *fin, Person_Wrapper p_wrapper, Activity_Wrapper a_wrapper, int **mat)
{
    int N_activities;
    fscanf(fin, "%d", &(N_activities));
    int valid = 1;
    for (int i = 0; i < N_activities && valid == 1; i++)
    {
        int N_person, id_activity;
        fscanf(fin, "%d %d", &N_person, &id_activity);// dimenticato %d ERRORE
        int p_sol[N_person];
        for (int i = 0; i < N_person; i++)//N_person ERRORE
        {
            fscanf(fin, "%d", &(p_sol[i]));// dimenticato & ERRORE
        }
        if (verify(p_sol, N_person, id_activity, p_wrapper, a_wrapper, mat) >= 0)// dimenticato parametri ERRORE
        {
            // Rendo indisponibili le persone già assegante
            for(int i = 0; i < N_person; i++)
            {
                p_wrapper->vett[p_sol[i]].available = 0;
            }
        }
        else
            valid = 0;
    }
    if (valid == 1)
        printf("ok");
    else
        printf("errata");
}

void disp_simp(int * sol, int pos, Person_Wrapper p_wrapper, Activity_Wrapper a_wrapper, int ** mat, int ** best_sol, int * best_sol_dim, int * best_punt) {
    if(pos == p_wrapper->N) {
        // Terminal case
        /*
        es. tmp = {
            {1, 2}, ----> Attività 0 assoociata a persone con id 1 e 2
            {}, ----> Attività 1 assoociata a nessuno
            {3,0} ----> Attività 2 assoociata a persone con id 3 e 0
        }
        */
        int * tmp[a_wrapper->N]; // Ricostruisco sol
        int tmp_dim[a_wrapper->N];
        for(int i = 0; i < a_wrapper->N; i++) {
            tmp[i] = malloc(sizeof(int) * p_wrapper->N);
            tmp_dim[i] = 0;
        }
        for(int i = 0; i < p_wrapper->N; i++) {
            tmp[sol[i]][tmp_dim[sol[i]]] = i;
            tmp_dim[sol[i]] += 1;
        }
        for(int i = 0; i < a_wrapper->N; i++) {
            printf("Attività %d:\n", i);
            for(int j = 0; j < tmp_dim[i]; j++) {
                printf("%d, ", tmp[i][j]);
            }
            printf("\n");
        }
        if(tmp_dim[0] == 0 && tmp_dim[1] == 0 && tmp_dim[2] == 2 && tmp_dim[3] == 2) {
            printf("");
        }
        int punt_tmp = 0;
        int valid = 1;
        // Valido la soluzione
        for(int i = 0; i < a_wrapper->N && valid == 1; i++) {
            if(tmp_dim[i] != 0) {
                int punt_for_act = verify(tmp[i], tmp_dim[i], i, p_wrapper, a_wrapper, mat);
                if(punt_for_act > 0) {
                    punt_tmp += punt_for_act;
                }
                else {
                    valid = 0;
                }
            }
        }
        // Controllo validità finale e aggiornamento best_sol se ciò è possibile
        if(valid == 1 && punt_tmp>*best_punt) {
            for(int i = 0; i < a_wrapper->N; i++) {
                for(int j = 0; j < tmp_dim[i]; j++) {
                    best_sol[i][j] = tmp[i][j];
                }
                best_sol_dim[i] = tmp_dim[i];
            }
            *best_punt = punt_tmp;
        }

        for(int i = 0; i < a_wrapper->N; i++) {
            free(tmp[i]);
        }

    }
    else {
        for(int i = 0; i < a_wrapper->N; i++) {
            sol[pos] = i;
            disp_simp(sol, pos+1, p_wrapper, a_wrapper, mat, best_sol, best_sol_dim, best_punt);
        }
    }
}

// Wrapper per la disp_simp
void FindBestSol(Person_Wrapper p_wrapper,  Activity_Wrapper a_wrapper, int ** mat) {
    int * best_sol[a_wrapper->N];
    int best_sol_dim[a_wrapper->N];
    int sol[p_wrapper->N];
    int best_punt = -1;
    for(int i = 0; i < a_wrapper->N; i++) {
        best_sol[i] = malloc(sizeof(int) * p_wrapper->N);
        best_sol_dim[i] = 0;
    }
    disp_simp(sol, 0, p_wrapper, a_wrapper, mat, best_sol, best_sol_dim, &best_punt);
    printf("Best_sol con diff totale %d:\n", best_punt);
    for(int i = 0; i < a_wrapper->N; i++) {
        printf("Attività %d:\n", i);
        for(int j = 0; j < best_sol_dim[i]; j++) {
            printf("%d, ", best_sol[i][j]);
        }
        free(best_sol[i]);
        printf("\n");
    }
}

void FREE2D(int ** mat, int N) {
    for(int i = 0; i < N; i++) {
        free(mat[i]);
    }
    free(mat);
}

void PERSONFree(Person_Wrapper p_wrapper, int ** mat) {// Dimenticato di passare mat per la free ERRORE
    FREE2D(mat, p_wrapper->N);
    free(p_wrapper->vett);
    free(p_wrapper);
}


int ** PERSONBuildMat(FILE * fin, Person_Wrapper p_wrapper) {//dimenticato fin e volevo passare p_wrapper essendo ADT 1 Classe ERRORE
    // non allocato la matrice e la sua free2D ERRORE
    int ** mat = malloc(sizeof(int *) * p_wrapper->N);
    for(int i = 0; i < p_wrapper->N; i++) {
        mat[i] = malloc(sizeof(int) * p_wrapper->N);
        for(int j = 0; j < p_wrapper->N; j++) {
            fscanf(fin, "%d", &(mat[i][j]));
        }
    }
    return mat;
}




