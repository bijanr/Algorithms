#include <stdio.h>
#include <stdlib.h>

int** alloc(int row, int col);
void input(int** matrix, int row, int col);
int** addition(int** matrixA, int** matrixB, int row, int col);
void display(int** matrix, int row, int col);
void freeAlloc(int** matrix, int row);

int main(){
    int **matrixA, **matrixB, **matrix, rowA, colA, rowB, colB, row, col;
    printf("Enter the row and column of Matrix A: ");
    scanf("%d%d", &rowA, &colA);
    printf("Enter the row and column of Matrix B: ");
    scanf("%d%d", &rowB, &colB);

    matrixA = alloc(rowA, colA);
    matrixB = alloc(rowB, colB);
    if (rowA != rowB || colA != colB) {
        printf("Error: Matrices dimensions do not match for addition.\n");
        return 1;
    }
    row = rowA;
    col = colA;
    matrix = alloc(row, col);
    printf("Enter Matrix A: \n");
    input(matrixA, rowA, colA);
    printf("Enter Matrix B: \n");
    input(matrixB, rowB, colB);

    matrix = addition(matrixA, matrixB, row, col);
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
            scanf("%d", (*(matrix+i)+j));
        }
    }
}

int** addition(int** matrixA, int** matrixB, int row, int col){
    int **matrix = alloc(row, col);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            *(*(matrix + i)+ j) = *(*(matrixA + i)+ j) + *(*(matrixB + i)+ j);
        }
    }
    return matrix;
}

void display(int** matrix, int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            printf("%d ", *(*(matrix + i)+ j));
        }
        printf("\n");
    }
}

void freeAlloc(int** matrix, int row){
    for(int i = 0; i < row; i++)
       free(matrix[i]);
    free(matrix);
}