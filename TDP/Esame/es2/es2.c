#include <stdlib.h>
#include <stdio.h>

int charErase (char str[], int pos[]) {
	int i = 0;
	while(pos[i] != -1) {
		int j = pos[i];
		while(str[j]!='\0') {
			str[j] = str[j+1];
			j++;
		}
		i++;
	}
	return i;
}

int main() {
	char str[15] = "ThisIsAString";
	int pos[6] = {7, 4, 2, 0, 11, -1};
	int canc = charErase(str, pos);
	printf("%d, %s", canc, str);
}