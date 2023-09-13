//Write a multithreaded program for matrix multiplication.
#include <stdio.h>
#include <stdlib.h>

// Function to perform matrix multiplication
void multiply(int** matrix1, int** matrix2, int** result, int rows, int cols, int size) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = 0;
            for (int k = 0; k < size; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

int main() {
    int size;

    printf("Enter the size of the square matrices: ");
    scanf("%d", &size);

    int** matrix1 = (int**)malloc(size * sizeof(int*));
    int** matrix2 = (int**)malloc(size * sizeof(int*));
    int** result = (int**)malloc(size * sizeof(int*));

    for (int i = 0; i < size; i++) {
        matrix1[i] = (int*)malloc(size * sizeof(int));
        matrix2[i] = (int*)malloc(size * sizeof(int));
        result[i] = (int*)malloc(size * sizeof(int));
    }

    printf("Enter values for Matrix 1:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &matrix1[i][j]);
        }
    }

    printf("Enter values for Matrix 2:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &matrix2[i][j]);
        }
    }

    multiply(matrix1, matrix2, result, size, size, size);

    printf("Result Matrix:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // Free dynamically allocated memory
    for (int i = 0; i < size; i++) {
        free(matrix1[i]);
        free(matrix2[i]);
        free(result[i]);
    }
    free(matrix1);
    free(matrix2);
    free(result);

    return 0;
}
