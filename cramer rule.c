#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>

void inputMatrix(int size, int matrix[][size]) {
    int i, j;
    for(i=0;i<size;i++) {
        for(j=0;j<size;j++) {
            printf("%dX%d >>", i+1,j+1);
            scanf("%d", &matrix[i][j]);
        }
    }
}

int get2by2Deter(int size, int matrix[][size]) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]; 
}

void makeMinorMatrix(int size, int matrix[][size], int tempMatrix[][size-1], int colToRemove) {

    // 0 row i col delete
    int i, j;
    int k = 0;
    int l = 0;
    for(i=1;i<size;i++) {
        l = 0;
        for(j=0;j<size;j++) {
            if(j == colToRemove) continue;

            tempMatrix[k][l++] = matrix[i][j];
        }
        k++;
    }

}

int getDeterminant(int size, int matrix[][size]) {
    if(size == 2) return get2by2Deter(size, matrix);

    int i = 0;
    int tempMatrix[size-1][size-1];
    int sum = 0;

    for(i=0;i<size;i++) {
        
        makeMinorMatrix(size, matrix, tempMatrix, i);
        
        if(i%2 == 0) sum += matrix[0][i] * getDeterminant(size-1, tempMatrix);
        else sum -= matrix[0][i] * getDeterminant(size-1, tempMatrix);
    }

    return sum;

}

void inputVector(int size, int vector[]) {
    for(int i=0;i<size;i++) {
        printf("b%d 벡터 >>", i+1);
        scanf("%d", &vector[i]);
    }
}

void getRoot(int size, int matrix[][size], int vector[]) {
    double rootVector[size];
    int tempVector[size];
    int determinant = getDeterminant(size, matrix);
    int i, j;

    for(i=0;i<size;i++) {
        for(j=0;j<size;j++) {
            tempVector[j] = matrix[j][i];
            matrix[j][i] = vector[j];
        }
        rootVector[i] = (double)getDeterminant(size, matrix)/determinant;
        printf("%2f ", rootVector[i]);
        for(j=0;j<size;j++) {
            matrix[j][i] = tempVector[j];
        }
    }

}


int main(void) {
    int size;
    // Ax = b
    printf("행렬의 크기 >>");
    scanf("%d", &size);
    int matrixA[size][size];
    int vector[size];

    // input Matrix //
    inputMatrix(size, matrixA);

    // input Vector //
    inputVector(size, vector);

    // get root //
    getRoot(size, matrixA, vector);

    return 0;
}