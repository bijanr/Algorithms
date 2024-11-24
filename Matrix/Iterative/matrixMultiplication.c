#include <stdio.h>
#include <stdlib.h>

int** alloc(int row, int col);
void input(int** matrix, int row, int col);
int** multiplication(int** matrixA, int** matrixB, int rowA, int colA, int rowB, int colB);
void display(int** matrix, int row, int col);
void freeAlloc(int** matrix, int row);

int main(){
    int **matrixA, **matrixB, **matrix, rowA, colA, rowB, colB, row, col;
    printf("Enter the row and column of Matrix A: ");
    scanf("%d%d", &rowA, &colA);
    printf("Enter the row and column of Matrix B: ");
    scanf("%d%d", &rowB, &colB);

    // Check if the matrices can be multiplied
    if (colA != rowB) {
        printf("Error: Number of columns in Matrix A must be equal to number of rows in Matrix B for multiplication.\n");
        return 1;
    }

    matrixA = alloc(rowA, colA);
    matrixB = alloc(rowB, colB);

    printf("Enter Matrix A: \n");
    input(matrixA, rowA, colA);
    printf("Enter Matrix B: \n");
    input(matrixB, rowB, colB);

    row = rowA;
    col = colB;
    matrix = alloc(row, col);

    matrix = multiplication(matrixA, matrixB, rowA, colA, rowB, colB);
    printf("Resultant Matrix is: \n");
    display(matrix, row, col);

    freeAlloc(matrix, row);
    freeAlloc(matrixA, rowA);
    freeAlloc(matrixB, rowB);

    return 0;
}

int** alloc(int row, int col){
    int **matrix = (int**)malloc(row * sizeof(int*));
    for(int i = 0; i < row; i++)
        matrix[i] = (int*)malloc(col * sizeof(int));
    return matrix;
}

void input(int** matrix, int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            scanf("%d", (*(matrix + i) + j));
        }
    }
}

int** multiplication(int** matrixA, int** matrixB, int rowA, int colA, int rowB, int colB){
    int **matrix = alloc(rowA, colB);
    for(int i = 0; i < rowA; i++){
        for(int j = 0; j < colB; j++){
            *(*(matrix + i) + j) = 0;
            for(int k = 0; k < colA; k++){
                *(*(matrix + i) + j) += *(*(matrixA + i) + k) * *(*(matrixB + k) + j);
            }
        }
    }
    return matrix;
}

void display(int** matrix, int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            printf("%d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

void freeAlloc(int** matrix, int row){
    for(int i = 0; i < row; i++)
        free(matrix[i]);
    free(matrix);
}
