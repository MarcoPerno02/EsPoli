#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int copyFile(char *filename1, char *filename2) {
    FILE *fs, *fd;
    if((fs = fopen(filename1, "r")) == NULL)
        return -1;
    if((fd = fopen(filename2, "w")) == NULL)
        return -1;   
    
    int carCop = 0;
    char car;
    while(fscanf(fs, "%c", &car) != EOF) {
        fprintf(fd, "%c", car);
        carCop++;
    }
    fclose(fs);
    fclose(fd);
    return carCop;
}

int main() {
    char filename1[50] = "input.txt";
    char filename2[50] = "output.txt";
    printf("%d", copyFile(filename1, filename2));
}