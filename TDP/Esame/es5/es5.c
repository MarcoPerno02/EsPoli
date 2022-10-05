#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXM 5



int count(char A[][MAXM], int n, int m, char str[]) {
	int count = 0;
	int len_str = strlen(str);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			// Controllo per riga
			int aus = j;
			while(str[aus-j] != '\0' && aus < m && A[i][aus] == str[aus-j]) {
				aus++;
			}
			if(str[aus-j] == '\0')
				count++;
			// Controllo per colonna
			aus = i;
			while(str[aus-i] != '\0' && aus < n && A[aus][j] == str[aus-i]) {
				aus++;
			}
			if(str[aus-i] == '\0')
				count++;
		}
	}
	return count;
}

int main(int argvc, char argv[]) {
	char A[4][5] = {{'a', 'c', 'c', 'd', 'e'}, {'a', 'a', 'c', 'c', 'e'}, {'a', 't', 'c', 'a', 'e'}, {'a', 'c', 'a', 't', 'e'}};
	char str[10] = "cat";
	printf("%d", count(A, 4, 5, str));
}