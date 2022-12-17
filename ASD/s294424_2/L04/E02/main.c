#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct Person *link;
struct Person
{
    char id[5+1];
    char nome[50+1];
    char cognome[50+1];
    char data_di_nascita[10+1];
    char via[50+1];
    char citta[50+1];
    char cap[5+1];
    long data_di_nascita_unix_format;
    link next;
    link prev;
};

typedef enum {
    r_ins_tast, r_ins_file, r_ricerca_cod,
    r_canc_1, r_canc_2, r_stampa_file
} t_comandi;

void pulisciBufferTastiera(void);
void toLower(char str[]);
t_comandi leggiComando();
long convertDateToUnixTime(char * str);
int checkNewId(link head, char * new_id);
void insertionPeopleFromCmd(link * head);
void insertionPeopleFromFile(link * head, char * fname);
link createNode();
void orderedInsertion(link * head, link node);
void headInsertion(link * head, link node);
void middleInsertion(link x, link node);
void bottomInsertion(link x, link node);
struct Person removeFromList(link * head, char * id);
struct Person removeFromListV2(link * head, char * id);
struct Person searchByIdStruct(link head);
link searchByIdPointer(link head);
int dateBetweenTwoDates(long date_to_check, long date1, long date2);
void printPerson(struct Person person, FILE *f);
void printFile(link head);
void freeList(link head);

int main() {
    link head = NULL;
    insertionPeopleFromFile(&head, "anag1.txt");
    t_comandi comando;

    do {
        comando = leggiComando();
        switch(comando) {
            case r_ins_tast:
                insertionPeopleFromCmd(&head);
                break;
            case r_ins_file:
                insertionPeopleFromFile(&head, "anag2.txt");
                break;
            case r_ricerca_cod:
                struct Person person = searchByIdStruct(head);
                if(strcmp(person.id, "") != 0)
                    printPerson(person, stdout);
                else
                    printf("ID non trovato\n");
                break;
            case r_canc_1:
                link result = searchByIdPointer(head);
                if(strcmp(result->id, "") != 0) {
                    struct Person result_2 = removeFromListV2(&head, result->id);
                    printf("Eliminato: ");
                    printPerson(result_2, stdout);
                }
                else {
                    free(result);
                    printf("ID non trovato\n");
                }
                break;
            case r_canc_2:
                char date1[10+1], date2[10+1];
                printf("data1: ", date1);
                scanf("%s", date1);
                printf("data2: ", date2);
                scanf("%s", date2);
                long date1_unix = convertDateToUnixTime(date1);
                long date2_unix = convertDateToUnixTime(date2);
                if(date1_unix > date2_unix) {
                    long tmp = date1_unix;
                    date1_unix = date2_unix;
                    date2_unix = tmp;
                }
                link x;
                x = head;
                while(x != NULL) {
                    if(dateBetweenTwoDates(x->data_di_nascita_unix_format, date1_unix, date2_unix) == 1) {
                        char id[5+1];
                        strcpy(id, x->id);
                        x = x->next;
                        struct Person result_2 = removeFromListV2(&head, id);
                        printf("Eliminato: ");
                        printPerson(result_2, stdout);
                    }
                    else {
                        x = x->next;
                    }
                }
            case r_stampa_file:
                printFile(head);
                break;
            default:
                break;
        }
        pulisciBufferTastiera();
    }while(comando != 6);
    freeList(head);
}

link createNode() {
    link node = malloc(sizeof(struct Person));
    if(node == NULL) exit(-1);
    return node;
}

void headInsertion(link * head, link node) {
    // Head insertion
    node->next = (*head);
    (*head)->prev = node;
    (*head) = node;
}

void middleInsertion(link x, link node) {
    // Middle insertion between (*x)->prev and (*x)
    node->next = x;
    node->prev = x->prev;

    // Copy the (*x)->prev pointer because otherwise I would lose the pointer to to prev element with the instruction "(*x)->prev = *node;"
    link prev = x->prev;
    x->prev = node;
    prev->next = node;
}

void bottomInsertion(link x, link node) {
    x->next = node;
    node->prev = x;
}

struct Person removeFromList(link * head, char * id) {
    if(*head != NULL) {
        link * x;
        for(x = head; x != NULL && strcmp((*x)->id, id) != 0; x = &((*x)->next)) {}
        if(x != NULL) {
            struct Person result;
            result = **x;
            if((*x)->prev == NULL) {
                if((*x)->next == NULL) {
                    // only one node in the lis
                    *head = NULL;
                    free(*x);
                }
                else {
                    // Head deletion
                    // Save the pointer to the ex head because after the instruction "(*head) = (*x)->next;" *x will contain the address of the new head and I will free the new head
                    link ex_head = malloc(sizeof(struct Person));
                    ex_head = *x;
                    (*head) = (*x)->next;
                    (*head)->prev = NULL;
                    free(ex_head);
                }
                
            }
            else if((*x)->next == NULL) {
                // Bottom deletion
                (*x)->prev->next = NULL;
                free(*x);
            }
            else {
                // Middle deletion
                link node_to_delete = *x;
                link prev = (*x)->prev;
                link next = (*x)->next;
                prev->next = next;
                next->prev = prev;
                free(node_to_delete);
            }
            return result;
        }
    }
    struct Person result;
    strcpy(result.id, "");
    return result;
}

struct Person removeFromListV2(link * head, char * id) {
    // othere version of removeFromList
    if(*head != NULL) {
        link x;
        for(x = *head; x != NULL && strcmp(x->id, id) != 0; x = (x->next)) {}
        if(x != NULL) {
            struct Person result;
            result = *x;
            if(x->prev == NULL) {
                if(x->next == NULL) {
                    // only one node in the lis
                    *head = NULL;
                    free(x);
                }
                else {
                    // Head deletion
                    (*head) = x->next;
                    (*head)->prev = NULL;
                    free(x);
                }
                
            }
            else if(x->next == NULL) {
                // Bottom deletion
                x->prev->next = NULL;
                free(x);
            }
            else {
                // Middle deletion
                x->prev->next = x->next;
                x->next->prev = x->prev;
                free(x);
            }
            return result;
        }
    }
    struct Person result;
    strcpy(result.id, "");
    return result;
}

void orderedInsertion(link * head, link node) {
    if((*head) == NULL) {
        // Initialize list
        (*head) = node;
    }
    else {
        link * x = head;
        while((*x)->next != NULL && node->data_di_nascita_unix_format > (*x)->data_di_nascita_unix_format) {
            x = &((*x)->next);
        }
        if((*x)->next == NULL && node->data_di_nascita_unix_format > (*x)->data_di_nascita_unix_format) {
            // Bottom insertion
            bottomInsertion(*x, node);
        }
        else {
            if((*x)->prev == NULL) {
                // Head insertion
                headInsertion(x, node);
            }
            else {
                // Middle insertion
                middleInsertion(*x, node);
            }
        }
    }
}

void insertionPeopleFromCmd(link * head) {
    link node = createNode();
    printf("Inserisci id: ");
    scanf("%s", node->id);
    printf("Inserisci nome: ");
    scanf("%s", node->nome);
    printf("Inserisci cognome: ");
    scanf("%s", node->cognome);
    printf("Inserisci data_di_nascita: ");
    scanf("%s", node->data_di_nascita);
    printf("Inserisci via: ");
    scanf("%s", node->via);
    printf("Inserisci citta: ");
    scanf("%s", node->citta);
    printf("Inserisci cap: ");
    scanf("%s", node->cap);
    node->prev = NULL;
    node->next = NULL;
    node->data_di_nascita_unix_format = convertDateToUnixTime(node->data_di_nascita);
    if(checkNewId(*head, node->id) == 0)
        orderedInsertion(head, node);
    else
        printf("Id %s già presente\n", node->id);
    printFile(*head);
}

void insertionPeopleFromFile(link * head, char * fname) {
    FILE *fin;
    if((fin = fopen(fname, "r")) == NULL) {
        printf("Errore nell'apertura del file %s", fname);
        exit(1);
    }

    link node;
    node = createNode();
    while(fscanf(fin, "%s %s %s %s %s %s %s", node->id, node->nome, node->cognome, node->data_di_nascita, node->via, node->citta, node->cap) != EOF) {
        node->data_di_nascita_unix_format = convertDateToUnixTime(node->data_di_nascita);
        //printf("%s %s %s %s %s %s %s \n", node->id, node->nome, node->cognome, node->data_di_nascita, node->via, node->citta, node->cap);
        node->next = NULL;
        node->prev = NULL;
        if(checkNewId(*head, node->id) == 0)
            orderedInsertion(head, node);
        else
            printf("Id %s già presente\n", node->id);
        node = createNode();
    }
    fclose(fin);
}

void printPerson(struct Person person, FILE *f) {
    fprintf(f, "%s %s %s %s %s %s %s\n", person.id, person.nome, person.cognome, person.data_di_nascita, person.via, person.citta, person.cap);
}

void printFile(link head) {
    FILE *f;
    f = fopen("out.txt", "w");
    if(f == NULL) exit(-1);
    link x;
    for( x = head; x != NULL; x = x->next) {
       printPerson(*x, f);
    }
    fclose(f);
}

void freeList(link head) {
    link node = head;
    while(node != NULL) {
        link next = node->next;
        free(node);
        node = next;
    }
}

void pulisciBufferTastiera(void)
{
    /* Pulisco il buffer della tastiera in modo da evitare che nel buffer STDIN rimanga qualche carattere non letto*/
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

struct Person searchByIdStruct(link head) {
    char id[5+1];
    printf("Inserisci codice da cercare: ");
    scanf("%s", id);
    link x;
    for(x = head; x != NULL && strcmp(x->id, id); x = x->next) { }
    if(x!=NULL) {
        return *x;
    }
    struct Person person_empty;
    strcpy(person_empty.id, "");
    return person_empty;
}

link searchByIdPointer(link head) {
    char id[5+1];
    printf("Inserisci codice da cercare: ");
    scanf("%s", id);
    link x;
    for(x = head; x != NULL && strcmp(x->id, id); x = x->next) { }
    if(x!=NULL) {
        return x;
    }
    link person_empty = malloc(sizeof(struct Person));
    strcpy(person_empty->id, "");
    return person_empty;
}

void toLower(char str[]) {
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

long convertDateToUnixTime(char * str) {
    int year, month, day;
    sscanf(str, "%d/%d/%d", &day, &month, &year);
    struct tm t ={0};
    time_t t_of_day;
    t.tm_year = year-1900;  // Year - 1900
    t.tm_mon = month-1;           // Month, where 0 = jan
    t.tm_mday = day;
    t_of_day = mktime(&t);
    return t_of_day;
}

int checkNewId(link head, char * new_id) {
    // 0 stands for okay, 1 for error
    link x;
    x = head;
    int found = 0;
    while(x != NULL && found == 0) {
        if(strcmp(x->id, new_id) == 0)
            found = 1;
        x = x->next;
    }
    return found;
}

int dateBetweenTwoDates(long date_to_check, long date1, long date2) {
    if(date_to_check >= date1 && date_to_check <= date2)
        return 1;
    return 0;
}

t_comandi leggiComando (void) {
    t_comandi c;
    c = 0;
    char cmd[30];
    char tabella[50][30] = {"ins_tast", "ins_file", "ricerca_cod", "canc_1", "canc_2", "stampa_file", "fine"};
    do {
        c = 0;
        printf("Digitare uno dei seguenti comandi:\n\t- ins_tast\n\t- ins_file\n\t- ricerca_cod \n\t- canc_1 \n\t- canc_2 \n\t- stampa_file \n\t- fine\nScelta: ");
        scanf("%s",cmd);
        for(int i = 0; cmd[i]; i++){
            cmd[i] = tolower(cmd[i]);
        }
        while(c<7 && strcmp(cmd,tabella[c])!=0)
            c++;
        if(c == 7) {
            printf("Comando errato.\n");
            pulisciBufferTastiera();
        }
    }while(c==7);
    return (c);
}