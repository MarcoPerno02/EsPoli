#include <stdio.h>
#include <stdlib.h>

void prodCartFilt(int *v1, int d1, int *v2, int d2, char * aaa) {
	printf("%s", aaa);
	for(int i = 0; i < d1; i++){
		for(int j = 0; j < d2; j++) {
			if(v1[i]-v2[j] != 0 && v1[i]-v2[j] != 1 && v1[i]-v2[j] != -1)
				printf("%d %d \n", v1[i], v2[j]);
		}
	}
}

int main() {
	int v1[2] = {1,2};
	int v2[2] = {3,2};
	prodCartFilt(v1, 2, v2, 2, "sss");
}