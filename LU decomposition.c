#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <stdlib.h>


void printMatrix(int size, double matrix[][size]) {
    int i, j;
    for(i=0;i<size;i++) {
        printf("|\t");
        for(j=0;j<size;j++) {
            printf("%.1f \t", matrix[i][j]);
        }
        printf("|\n");
    }
}

void inputMatrix(int size, double matrix[][size]) {
    int i, j;
    for(i=0;i<size;i++) {
        for(j=0;j<size;j++) {
            printf("%dX%d >>", i+1,j+1);
            scanf("%lf", &matrix[i][j]);
        }
    }
}
void getLUMatrix(int n, double matrix[][n], double upper[][n], double lower[][n]) {
    int i, j, k;    // i is pivot //
    double ratio;

    for(i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            upper[i][j] = matrix[i][j];
            if(i == j) lower[i][j] = 1;
            else lower[i][j] = 0;
        }
    }

    for(i=0;i<n;i++) {
        for(j=i+1;j<n;j++) {
            if(upper[i][i] == 0) continue;

            ratio = (double)upper[j][i]/upper[i][i];
            lower[j][i] = ratio;
            
            for(k=i;k<n;k++) {
                upper[j][k] = upper[j][k] - ratio * upper[i][k];
            }
        }
    }
}

double getDeterminant(int n, double lower[][n], double upper[][n]) {
    double det = 1;
    int i;
    for(i=0;i<n;i++) {
        det *= upper[i][i] * lower[i][i];
    }
    return det;
}

int main(void) {

    int n;
    // get size //
    printf("배열의 크기 >>");
    scanf("%d", &n);
    double matrix[n][n];
    double upper[n][n];
    double lower[n][n];

    // input matrix //
    inputMatrix(n, matrix);

    // get upper //
    getLUMatrix(n, matrix, upper, lower);

    printf("원래 행렬 \n");
    printMatrix(n, matrix);
    printf("----------------------------\n");
    printf("상부 삼각 행렬 \n");
    printMatrix(n, upper);
    printf("하부 삼각 행렬 \n");
    printMatrix(n, lower);

    printf("행렬식: %.1f", getDeterminant(n, lower, upper));

    return 0;
}