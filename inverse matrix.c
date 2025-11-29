#define _CRT_NO_SECURE_WARNINGS
#include <stdio.h>

void printMatrix(int size, int matrix[][size]);


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

void getCofactorMatrix(int size, int matrix[][size], int tempMatrix[][size-1], int rowToRemove, int colToRemove) {
    int i, j;
    int m=0;
    int n=0;
    for(i=0;i<size;i++) {
        if(i == rowToRemove) continue;
        n=0;
        for(j=0;j<size;j++) {
            if(j == colToRemove) continue;
            tempMatrix[m][n++] = matrix[i][j];
        }
        m++;
    }
}

void getAdjMatrix(int size, int matrix[][size]) {
    if(getDeterminant(size, matrix) == 0) {
        printf("행렬식 = 0 이므로 비가역적입니다.");
        return;
    }

    int i, j;
    int inverseMatrix[size][size];
    int tempMatrix[size-1][size-1];

    for(i=0;i<size;i++) {
        for(j=0;j<size;j++) {
            getCofactorMatrix(size, matrix, tempMatrix, i, j);

            if((i+j)%2 == 0) inverseMatrix[j][i] = getDeterminant(size-1, tempMatrix);
            else inverseMatrix[j][i] = -1 * getDeterminant(size-1, tempMatrix);        
        }
    }

    printMatrix(size, inverseMatrix);
    printf("\n");
    printf("determinant: %d", getDeterminant(size, matrix));

}

void printMatrix(int size, int matrix[][size]) {
    int i, j;
    for(i=0;i<size;i++) {
        printf("|\t");
        for(j=0;j<size;j++) {
            printf("%d \t", matrix[i][j]);
        }
        printf("|\n");
    }
}

int main(void) {
    int size;

    printf("행렬의 크기 >>");
    scanf("%d", &size);
    int matrix[size][size];

    // input Matrix //
    inputMatrix(size, matrix);

    // print Matrix //
    printMatrix(size, matrix);
    printf("\n");
    // inverse Matrix //

    getAdjMatrix(size, matrix);

    return 0;
}