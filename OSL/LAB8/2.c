/*Write a multithreaded program that calculates the summation of non-negative
integers in a separate thread and passes the result to the main thread.*/

#include <stdio.h>
#include<stdlib.h>
#include <pthread.h>

// Define a structure to hold the result
struct SumResult {
    unsigned long long sum;
};

// Function to calculate the summation of non-negative integers
void* calculateSum(void* arg) {
    int n = *((int*)arg);
    unsigned long long sum = 0;

    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    // Create a result structure and store the sum
    struct SumResult* result = (struct SumResult*)malloc(sizeof(struct SumResult));
    result->sum = sum;
    pthread_exit(result);
}

int main() {
    int n;

    // Prompt the user for input
    printf("Enter a non-negative integer: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Please enter a non-negative integer.\n");
        return 1;
    }

    pthread_t tid;
    int thread_arg = n;

    // Create a thread to calculate the summation
    if (pthread_create(&tid, 0, calculateSum, &thread_arg) != 0) {
        perror("pthread_create");
        return 1;
    }

    // Wait for the thread to finish and get the result
    struct SumResult* result;
    if (pthread_join(tid, (void**)&result) != 0) {
        perror("pthread_join");
        return 1;
    }

    // Print the result
    printf("Sum of non-negative integers from 1 to %d: %llu\n", n, result->sum);

    // Free the result structure
    free(result);

    return 0;
}