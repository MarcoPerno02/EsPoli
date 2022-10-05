#include <stdio.h>
#include <string.h>
void reverseString(char* s);
int main() {
    char s[10]= "ciao";
    reverseString(s);
    printf("%s", s);
    return 0;
}
void reverseString(char* s){
    int i,j,l;
    char tmp;
    l = strlen(s);
    for(i=0,j=l-1; i<l/2;i++,j--){
        tmp = s[i];
        s[i] = s[j];
        s[j]=tmp;
    }
}