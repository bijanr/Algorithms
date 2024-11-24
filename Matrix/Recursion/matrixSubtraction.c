#include <stdio.h>
#include <stdlib.h>

// Function to allocate memory for a matrix
int **allocateMatrix(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    return matrix;
}

// Function to free memory allocated for a matrix
void freeMatrix(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to subtract matrices using pure recursion
void subtractMatrices(int **a, int **b, int **result, int rows, int cols, int i, int j) {
    if (i == rows) {
        return;
    }

    if (j == cols) {
        subtractMatrices(a, b, result, rows, cols, i + 1, 0);
    } else {
        result[i][j] = a[i][j] - b[i][j];
        subtractMatrices(a, b, result, rows, cols, i, j + 1);
    }
}

// Function to display a matrix
void displayMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int rows, cols;

    // Input dimensions of matrices A and B
    printf("Enter the number of rows and columns for matrices: ");
    scanf("%d %d", &rows, &cols);

    int **matrixA = allocateMatrix(rows, cols);
    int **matrixB = allocateMatrix(rows, cols);
    int **result = allocateMatrix(rows, cols);

    // Input elements of matrix A
    printf("Enter elements of matrix A:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrixA[i][j]);
        }
    }

    // Input elements of matrix B
    printf("Enter elements of matrix B:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrixB[i][j]);
        }
    }

    // Initialize result matrix with zeros
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = 0;
        }
    }

    // Subtract matrices using pure recursion
    subtractMatrices(matrixA, matrixB, result, rows, cols, 0, 0);

    // Display the result matrix
    printf("Resultant Matrix:\n");
    displayMatrix(result, rows, cols);

    // Free allocated memory
    freeMatrix(matrixA, rows);
    freeMatrix(matrixB, rows);
    freeMatrix(result, rows);

    return 0;
}
