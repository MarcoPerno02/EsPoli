#include <stdio.h>
#include <stdlib.h>

#define MAXM 4
#define MAXC 3


void dispRanking(int c[MAXM][MAXC], int n, int m)
{
    printf("La capolista per ogni giornata delle %d giornate sono: ");
    for (int j = 0; j < m; j++)
    {
        int max = -1, id = -1;
        for (int i = 0; i < n; i++)
        {
            int sum = 0;
            for (int k = 0; k <= j; k++)
            {
                sum += c[i][k];
            }
            if (sum > max)
            {
                max = sum;
                id = i;
            }
        }
        printf("%d ", id);
    }
}

int moveIndexes(int M[MAXM][MAXC], int *rp, int *cp, int delta)
{
    int i, j, *p, *p0;

    i = *rp;

    j = *cp;

    if (i < 0 || i >= MAXM || j < 0 || j >= MAXC)

        return 1; // error – nothing done

    p0 = &(M[0][0]);

    p = &(M[i][j]);

    p = p + delta;

    if (p < p0 || p > &(M[MAXM - 1][MAXC - 1]))

        return 1; // error – nothing done

    *rp = (p - p0) / MAXC;

    *cp = (p - p0) % MAXC;

    return 0;
}

void test(int **vet) {
    printf("ss");
    int aus = 10;
    vet[0] = &aus;
    printf("\nval: %d", *(vet[0]));
}

int main()
{
    int c[4][3] = {{3, 1, 0}, {0, 8, 1}, {1, 1, 1}, {1, 1, 3}};
    dispRanking(c, 4, 3);
    int i=0, j=0, *pi=&i, *pj=&j;
    moveIndexes(c, pi, pj, 5);

    int (*vet_aus)[4][3];
    vet_aus = &c;
    printf(" %d ", (*vet_aus)[1][1]);
    int *punt = &(c[0][0]);
    printf("%d", *(punt+4));
    printf("ciaooo\n");
    int *vet[3];
    test(vet);
}