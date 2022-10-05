#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {char name[30]; char surname[30]; int age;} kid;

int readKids(kid listKids[100], int max, char filename[100]) {
	FILE *fp;
	if((fp = fopen(filename, "r")) == NULL)
		printf("File non trovato");
        int i = 0;
	while(fscanf(fp, "%s %s %d", listKids[i].name, listKids[i].surname, &listKids[i].age) != EOF) {
		i++;
	}
	fclose(fp);
	return i;
}

int selectKids(kid listKids[100], int ns, kid *selKids[100], int ageMax) {
	int j = 0;
	for(int i = 0; i < ns; i++ ) {
		if(listKids[i].age < ageMax) {
			selKids[j] = (kid*)malloc(sizeof(kid));// Devo usare la malloc altrimenti da segmentation fault
			strcpy(selKids[j]->name, listKids[i].name);
			strcpy(selKids[j]->surname, listKids[i].surname);
			(*(selKids)[j]).age = listKids[i].age;
			j++;
		}
	}
	return j;
} 

void printKids(kid *selKids[100], int n) {
	for(int i = 0; i < n; i++) {
		printf("%s %s %d\n", (*(selKids[i])).name, (*(selKids[i])).surname, (*(selKids[i])).age);
	}
}

int main (int argc, char *argv[]) {
	kid listKids[100], *selKids[100];
	int ns,nsel;
	char filename [100] =  "input.txt";
	ns = readKids(listKids, 100, filename);
	nsel = selectKids(listKids, ns, selKids, 18);
	printf("%d\n", nsel);
	printKids(selKids, nsel);
	return 0;
}