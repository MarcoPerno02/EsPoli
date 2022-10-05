#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEndEspression(char car) {
    if(car == '\0' || car == '[' || car == ']' || car == '.' || car == '\\')
        return 1;
    else 
        return 0;
}

int findSubstringAtTheEnd(char *src, char *regexp, int *idx, char *last_regex_found) {
    int j = 0;
    char str_to_search[10+1] = "";
    while (checkEndEspression(regexp[*idx]) == 0)
    {
        str_to_search[j] = regexp[*idx];
        j++;
        *idx+=1;
    }
    str_to_search[j] = '\0';
    char *pch = strstr(src, str_to_search);
    if (*(pch + j) != '\0')
    {
        
        printf("Not verified\n");
        return 0;
    }
    else {
        printf("Verified\n");
        last_regex_found = pch;
        return 1;
    }
}

char *cercaRegexp(char *src, char *regexp) {
    int len_regexp = strlen(regexp);
    int i = 0;
    char *last_regex_found = NULL;
    int regex_valid = 1;
    while(i < len_regexp && regex_valid == 1) {
        if(regexp[i] == '.'){
            printf("Point found\n");
            i++;
            regex_valid = findSubstringAtTheEnd(src, regexp, &i, last_regex_found);
        }
        else if(regexp[i] == '[') {
            i++;
            if(regexp[i] == '^') {
                printf("[^ found\n");
                i++;
                char *car_found = NULL;
                while (checkEndEspression(regexp[i]) == 0 && car_found == NULL)
                {
                    car_found = strchr(src, regexp[i]);
                    i++;
                }
                if (car_found == NULL)
                {
                    printf("Verified\n");
                }
                else
                {
                    regex_valid = 0;
                    printf("Not verified\n");
                }
            }
            else
            {
                printf("[ found\n");
                char *car_found = NULL;
                while (checkEndEspression(regexp[i]) == 0 && car_found == NULL)
                {
                    car_found = strchr(src, regexp[i]);
                    i++;
                }
                if (car_found != NULL)
                {
                    printf("Verified\n");
                    last_regex_found = car_found;
                }
                else
                {
                    regex_valid = 0;
                    printf("Not verified\n");
                }
            }
        }
        else if(regexp[i] == '\\') {
            i++;
            if(regexp[i] == 'A'){
                printf("\\A found\n");
                if(src[0] >= 65 && src[0] <= 90) {
                    i++;
                    regex_valid = findSubstringAtTheEnd(src, regexp, &i, last_regex_found);
                }
                else {
                    regex_valid = 0;
                    printf("Not verified\n");
                }  
            }
            else {
                printf("\\a found\n");
                if(src[0] >= 97 && src[0] <= 122) {
                    i++;
                    regex_valid = findSubstringAtTheEnd(src, regexp, &i, last_regex_found);
                }
                else {
                    regex_valid = 0;
                    printf("Not verified\n");
                }
            }
        }
    }
}


int main(){
    char aus [10] = "mmoto";
    char regexp [10] = "\\aoto";
    cercaRegexp(aus, regexp);
    return 0;
}