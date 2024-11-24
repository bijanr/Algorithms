#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function prototypes
void printParenthesis(int i, int j, int n, int* bracket, char* name);
void matrixChainOrder(int p[], int n);

int main() {
    int arr[] = { 40, 20, 30, 10, 30 };
    int n = sizeof(arr) / sizeof(arr[0]);
    matrixChainOrder(arr, n);
    return 0;
}

// Function to print the optimal parenthesization
void printParenthesis(int i, int j, int n, int* bracket, char* name) {
    if (i == j) {
        printf("%c", *name);
        (*name)++;
        return;
    }

    printf("(");
    printParenthesis(i, *(bracket + i * n + j), n, bracket, name);
    printParenthesis(*(bracket + i * n + j) + 1, j, n, bracket, name);
    printf(")");
}

// Function to compute the optimal parenthesization and cost
void matrixChainOrder(int p[], int n) {
    int m[n][n];
    int bracket[n][n];

    // Initialize the matrix for the cost calculation
    for (int i = 1; i < n; i++) {
        m[i][i] = 0;
    }

    // Compute the minimum cost for each chain length L
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; k++) {
                // Compute cost/scalar multiplications
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    bracket[i][j] = k;
                }
            }
        }
    }

    // Print the optimal parenthesization
    char name = 'A';
    printf("Optimal Parenthesization is : ");
    printParenthesis(1, n - 1, n, (int*)bracket, &name);
    printf("\nOptimal Cost is : %d\n", m[1][n - 1]);
}
