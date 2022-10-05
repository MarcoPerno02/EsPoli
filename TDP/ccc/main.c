#include <stdio.h>
#include <string.h>
#define SOURCE_PATH "sorgente.txt"
#define DICT_PATH "dizionario.txt"
#define OUT_PATH "ricodificato.txt"
#define MAX_LEN_WORDS 20
#define MAX_LEN_DICT 20

typedef struct {
    char original[MAX_LEN_WORDS];
    char modified[MAX_LEN_WORDS];
} change;

int readDict(change dict[], FILE *dict_file);
void changeSource(FILE *source_file, FILE *out_file, change dict[], int dim_dict);
int readFile(FILE **file, char PATH[], char mode[]);

int main() {
    FILE *source_file, *dict_file, *out_file;
    int dim_dict;
    change dict[MAX_LEN_DICT];

    if(readFile(&source_file, SOURCE_PATH, "r")){
        return 1;
    }
    printf("%p", source_file);
    char a;
    fscanf(source_file, "%c", &a);

    if(readFile(dict_file, DICT_PATH, "r")){
        return 1;
    }

    if(readFile(out_file, OUT_PATH, "w")){
        return 1;
    }
    /*source_file = fopen(SOURCE_PATH, "r");
    if (source_file == NULL){
        printf("Errore nell'apertura del file: %s\n", SOURCE_PATH);
        return 1;
    }
    dict_file = fopen(DICT_PATH, "r");
    if (dict_file == NULL){
        printf("Errore nell'apertura del file: %s\n", DICT_PATH);
        return 1;
    }
    out_file = fopen(OUT_PATH, "w");
    if (out_file == NULL){
        printf("Errore nell'apertura del file: %s\n", OUT_PATH);
        return 1;
    }*/

    dim_dict = readDict(dict, dict_file);
    changeSource(source_file, out_file, dict, dim_dict);

    fclose(source_file);
    fclose(dict_file);
    fclose(out_file);
    return 0;
}

int readDict(change dict[], FILE *dict_file){
    int dim_dict;
    fscanf(dict_file, "%d", &dim_dict);
    for(int i=0; i<dim_dict; i++){
        fscanf(dict_file, "%s %s", dict[i].modified, dict[i].original);
    }
    return dim_dict;
}

void changeSource(FILE *source_file, FILE *out_file, change dict[], int dim_dict){
    char word[MAX_LEN_WORDS], ch, *occ;
    int found, i;
    while(fscanf(source_file, "%s%c", word, &ch)!=EOF){
        found = 0;
        for(i=0; i<dim_dict && !found; i++){
            occ = strstr(word, dict[i].original);
            if(occ){
                word[occ-&word[0]] = '\0';
                found = 1;
            }
        }
        fputs(word, out_file);
        if(found)
            fputs(dict[i].modified, out_file);
        fputc(ch, out_file);
    }
    return;
}

int readFile(FILE **file, char PATH[], char mode[]){

    *file = fopen(PATH, mode);
    if(file == NULL){
        return 1;
    }
    char a;
    return 0;
}
