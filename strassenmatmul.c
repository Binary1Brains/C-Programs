#include <stdio.h>
#include <stdlib.h>

void matrix_add(int n, int **A, int **B, int **C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void matrix_subtract(int n, int **A, int **B, int **C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void matrix_multiply_recursive(int n, int **A, int **B, int **C) {
    // Base case: If the matrix is 1x1
    if (n == 1) {
        C[0][0] += A[0][0] * B[0][0]; // Single element multiplication
        return;
    }

    int half = n / 2;

    // Dynamically allocate submatrices as pointers to pointers (2D arrays)
    int **A11 = (int **)malloc(half * sizeof(int *));
    int **A12 = (int **)malloc(half * sizeof(int *));
    int **A21 = (int **)malloc(half * sizeof(int *));
    int **A22 = (int **)malloc(half * sizeof(int *));
    int **B11 = (int **)malloc(half * sizeof(int *));
    int **B12 = (int **)malloc(half * sizeof(int *));
    int **B21 = (int **)malloc(half * sizeof(int *));
    int **B22 = (int **)malloc(half * sizeof(int *));
    int **C11 = (int **)malloc(half * sizeof(int *));
    int **C12 = (int **)malloc(half * sizeof(int *));
    int **C21 = (int **)malloc(half * sizeof(int *));
    int **C22 = (int **)malloc(half * sizeof(int *));

    // Allocate memory for each row of the submatrices
    for (int i = 0; i < half; i++) {
        A11[i] = (int *)malloc(half * sizeof(int));
        A12[i] = (int *)malloc(half * sizeof(int));
        A21[i] = (int *)malloc(half * sizeof(int));
        A22[i] = (int *)malloc(half * sizeof(int));
        B11[i] = (int *)malloc(half * sizeof(int));
        B12[i] = (int *)malloc(half * sizeof(int));
        B21[i] = (int *)malloc(half * sizeof(int));
        B22[i] = (int *)malloc(half * sizeof(int));
        C11[i] = (int *)malloc(half * sizeof(int));
        C12[i] = (int *)malloc(half * sizeof(int));
        C21[i] = (int *)malloc(half * sizeof(int));
        C22[i] = (int *)malloc(half * sizeof(int));
    }

    // Divide matrices A and B into 4 submatrices
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    // Conquer step: recursive calls to multiply submatrices
    matrix_multiply_recursive(half, A11, B11, C11);
    matrix_multiply_recursive(half, A11, B12, C12);
    matrix_multiply_recursive(half, A21, B11, C21);
    matrix_multiply_recursive(half, A21, B12, C22);
    matrix_multiply_recursive(half, A12, B21, C11);
    matrix_multiply_recursive(half, A12, B22, C12);
    matrix_multiply_recursive(half, A22, B21, C21);
    matrix_multiply_recursive(half, A22, B22, C22);

    // Combine the results (adding the submatrices to form the full matrix C)
    matrix_add(half, C11, C12, C11);   // C11 = C11 + C12
    matrix_add(half, C21, C22, C21);   // C21 = C21 + C22
    matrix_add(half, C11, C21, C);     // C = C11 + C21

    // Free dynamically allocated memory for the submatrices
    for (int i = 0; i < half; i++) {
        free(A11[i]);
        free(A12[i]);
        free(A21[i]);
        free(A22[i]);
        free(B11[i]);
        free(B12[i]);
        free(B21[i]);
        free(B22[i]);
        free(C11[i]);
        free(C12[i]);
        free(C21[i]);
        free(C22[i]);
    }

    free(A11);
    free(A12);
    free(A21);
    free(A22);
    free(B11);
    free(B12);
    free(B21);
    free(B22);
    free(C11);
    free(C12);
    free(C21);
    free(C22);
}

void print_matrix(int n, int **A) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter the size of the matrix (n x n): ");
    scanf("%d", &n);

    // Dynamically allocate memory for matrices A, B, and C
    int **A = (int **)malloc(n * sizeof(int *));
    int **B = (int **)malloc(n * sizeof(int *));
    int **C = (int **)malloc(n * sizeof(int *));
    
    for (int i = 0; i < n; i++) {
        A[i] = (int *)malloc(n * sizeof(int));
        B[i] = (int *)malloc(n * sizeof(int));
        C[i] = (int *)malloc(n * sizeof(int));
    }

    // Initialize matrix C with 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
        }
    }

    // Input for matrix A
    printf("Enter matrix A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    // Input for matrix B
    printf("Enter matrix B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    // Perform matrix multiplication recursively
    matrix_multiply_recursive(n, A, B, C);

    // Output the result matrix
    printf("Resultant Matrix C (A * B):\n");
    print_matrix(n, C);

    // Free dynamically allocated memory for matrices
    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }

    free(A);
    free(B);
    free(C);

    return 0;
}
