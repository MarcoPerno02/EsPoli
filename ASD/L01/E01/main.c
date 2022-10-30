#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEndEspression(char car)
{
    if (car == '\0' || car == '[' || car == ']' || car == '.' || car == '\\')
        return 1;
    else
        return 0;
}

char *cercaRegexp(char *src, char *regexp)
{
    int len_regexp = strlen(regexp);
    int len_src = strlen(src);
    int idx_src = 0;
    int idx_regexp = 0;
    char *last_regex_found = NULL;
    int regex_valid = 1;
    while (idx_regexp < len_regexp && regex_valid == 1 && idx_src < len_src)
    {
        if (regexp[idx_regexp] == '.')
        {
            printf("Point found\n");
        }
        else if (regexp[idx_regexp] == '[')
        {
            idx_regexp++;
            if (regexp[idx_regexp] == '^')
            {
                printf("[^ found\n");
                idx_regexp++;
                char *car_found = NULL;
                while (checkEndEspression(regexp[idx_regexp]) == 0 && car_found == NULL)
                {
                    if (src[idx_src] == regexp[idx_regexp])
                        car_found = &src[idx_src];
                    idx_regexp++;
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
                while (checkEndEspression(regexp[idx_regexp]) == 0 && car_found == NULL)
                {
                    if (src[idx_src] == regexp[idx_regexp])
                        car_found = &src[idx_src];
                    idx_regexp++;
                }
                if (car_found != NULL)
                {
                    printf("Verified\n");
                    while (checkEndEspression(regexp[idx_regexp]) == 0)
                    {
                        idx_regexp++;
                    }
                }
                else
                {
                    regex_valid = 0;
                    printf("Not verified\n");
                }
            }
        }
        else if (regexp[idx_regexp] == '\\')
        {
            idx_regexp++;
            if (regexp[idx_regexp] == 'A')
            {
                printf("\\A found\n");
                if (src[idx_src] >= 65 && src[idx_src] <= 90)
                {
                    printf("verified\n");
                }
                else
                {
                    regex_valid = 0;
                    printf("Not verified\n");
                }
            }
            else
            {
                printf("\\a found\n");
                if (src[idx_src] >= 97 && src[idx_src] <= 122)
                {
                    printf("Verified\n");
                }
                else
                {
                    regex_valid = 0;
                    printf("Not verified\n");
                }
            }
        }
        else
        {
            if (src[idx_src] != regexp[idx_regexp])
                regex_valid = 0;
            else
                printf("Character found\n");
        }
        idx_src++;
        idx_regexp++;
    }
    if (regex_valid == 1 && idx_regexp == len_regexp)
        return src;
    else
        return NULL;
}

int main()
{
    char *src = "ciao Ad5t1Raad aaaaaSo5t3g";
    char regexp[30] = "\\A[aeiou]5t[123].";
    int len_regexp = strlen(regexp);
    int len_src = strlen(src);
    char * found = NULL;
    int i = 0;
    do {
        found = cercaRegexp(src+i, regexp);
        i++;
    } while(found == NULL && i < strlen(src));
    if(found != NULL) {
        printf("Occorenza trovata. ");
        printf("La prima occorrenza trovata inizia qui: %s", found);
    }
    else {
        printf("Nessuna occorenza trovata. ");
    }
    return 0;
}