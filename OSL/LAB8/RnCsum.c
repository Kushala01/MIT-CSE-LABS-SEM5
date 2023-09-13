//Write a multithreaded program for finding row sum and column sum
#include <stdio.h>
#include <pthread.h>

#define SIZE 3

int matrix[SIZE][SIZE] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

int rowSum[SIZE] = {0};
int colSum[SIZE] = {0};

void* calculateRowSum(void* arg) {
    int row = *((int*)arg);
    
    for (int j = 0; j < SIZE; j++) {
        rowSum[row] += matrix[row][j];
    }
    
    pthread_exit(NULL);
}

void* calculateColSum(void* arg) {
    int col = *((int*)arg);
    
    for (int i = 0; i < SIZE; i++) {
        colSum[col] += matrix[i][col];
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_t rowThreads[SIZE];
    pthread_t colThreads[SIZE];
    int threadArgs[SIZE];
    
    // Create threads to calculate row sums
    for (int i = 0; i < SIZE; i++) {
        threadArgs[i] = i;
        pthread_create(&rowThreads[i], NULL, calculateRowSum, &threadArgs[i]);
    }
    
    // Create threads to calculate column sums
    for (int j = 0; j < SIZE; j++) {
        threadArgs[j] = j;
        pthread_create(&colThreads[j], NULL, calculateColSum, &threadArgs[j]);
    }
    
    // Wait for row threads to finish
    for (int i = 0; i < SIZE; i++) {
        pthread_join(rowThreads[i], NULL);
    }
    
    // Wait for column threads to finish
    for (int j = 0; j < SIZE; j++) {
        pthread_join(colThreads[j], NULL);
    }
    
    // Print row sums
    printf("Row sums:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("Row %d: %d\n", i + 1, rowSum[i]);
    }
    
    // Print column sums
    printf("Column sums:\n");
    for (int j = 0; j < SIZE; j++) {
        printf("Column %d: %d\n", j + 1, colSum[j]);
    }
    
    return 0;
}
