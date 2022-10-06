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

int findSubstringAtTheEnd(char *src, char *regexp, int *idx, char *last_regex_found)
{
    int j = 0;
    char str_to_search[10 + 1] = "";
    while (checkEndEspression(regexp[*idx]) == 0)
    {
        str_to_search[j] = regexp[*idx];
        j++;
        *idx += 1;
    }
    str_to_search[j] = '\0';
    char *pch = strstr(src, str_to_search);
    if (*(pch + j) != '\0')
    {

        printf("Not verified\n");
        return 0;
    }
    else
    {
        printf("Verified\n");
        last_regex_found = pch;
        return 1;
    }
}

char *cercaRegexp(char *src, char *regexp, int len_regexp, int len_src)
{
    int idx_src = 0;
    int i = 0;
    char *last_regex_found = NULL;
    int regex_valid = 1;
    while (i < len_regexp && regex_valid == 1 && idx_src < len_src)
    {
        if (regexp[i] == '.')
        {
            printf("Point found\n");
        }
        else if (regexp[i] == '[')
        {
            i++;
            if (regexp[i] == '^')
            {
                printf("[^ found\n");
                i++;
                char *car_found = NULL;
                while (checkEndEspression(regexp[i]) == 0 && car_found == NULL)
                {
                    if (src[idx_src] == regexp[i])
                        car_found = &src[idx_src];
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
                    if (src[idx_src] == regexp[i])
                        car_found = &src[idx_src];
                    i++;
                }
                if (car_found != NULL)
                {
                    printf("Verified\n");
                    while (checkEndEspression(regexp[i]) == 0)
                    {
                        i++;
                    }
                }
                else
                {
                    regex_valid = 0;
                    printf("Not verified\n");
                }
            }
        }
        else if (regexp[i] == '\\')
        {
            i++;
            if (regexp[i] == 'A')
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
                    i++;
                    printf("Verified/n");
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
            if (src[idx_src] != regexp[i])
                regex_valid = 0;
        }
        idx_src++;
        i++;
    }
    if (regex_valid == 1 && i == len_regexp)
        return src;
    else
        return NULL;
}

int main()
{
    char *src = "ciao mSoto";
    char regexp[30] = ".\\A[mo][^s]o";
    int len_regexp = strlen(regexp);
    int len_src = strlen(src);
    char * found = NULL;
    int i = 0;
    do {
        found = cercaRegexp(src+i, regexp, len_regexp, len_src-i);
        i++;
    } while(found == 0 && i < strlen(src));
    printf("%c", found);
    return 0;
}