#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void printVector(double vector[], int size) {
    int i;
    printf("[");
    for(i=0;i<size-1;i++) {
        printf("%.2f, ", vector[i]);
    }
    printf("%.2f]",vector[size-1]);
    printf("\n");
}

void inputVector(int size, double vector[]) {
    int i;
    for(i=0;i<size;i++) {
        printf("%d행: >>", i);
        scanf("%lf", &vector[i]);
    }
}
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

void getRoot(int size, double lower[][size], double upper[][size], double vector[]) {
    double tempVector[size];
    int i = 0, j = 0;
    double sum;

    // 하부 삼각 행렬 //
    tempVector[0] = vector[0]/lower[0][0];

    // Ly = b //
    for(i=1;i<size;i++) {
        sum = 0;
        for(j=0;j<i;j++) {
            sum += tempVector[j] * lower[i][j];
        }
        tempVector[i] = (vector[i]-sum)/lower[i][i];
    }

    // 상부 삼각 행렬 //
    tempVector[size-1] = tempVector[size-1]/upper[size-1][size-1];

    // Ux = y //
    for(i=size-2;i>-1;i--) {
        sum = 0;
        for(j=size-1;j>i;j--) {
            sum += tempVector[j] * upper[i][j];
        }
        tempVector[i] = (tempVector[i]-sum)/upper[i][i];
    }

    printVector(tempVector, size);
}

int main(void) {

    int n;
    // get size //
    printf("배열의 크기 >>");
    scanf("%d", &n);
    double matrix[n][n];
    double upper[n][n];
    double lower[n][n];
    double vector[n];

    // input matrix //
    inputMatrix(n, matrix);
    inputVector(n, vector);

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
    
    printf(" 답: ");
    getRoot(n, lower, upper, vector);
    return 0;
}