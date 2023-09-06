/*Write a multithreaded program that calculates the summation of non-negative
integers in a separate thread and passes the result to the main thread.*/

#include <stdio.h>
#include <pthread.h>
#include <stdint.h> 

// Function to calculate the summation of non-negative integers
void* calculateSum(void* arg) {
    int n = *((int*)arg);
    int sum = 0;

    for (int i = 1; i <= n; i++) {
        sum += i;
    }

    pthread_exit((void*)(intptr_t)sum);
}

int main() {
    int n;

    // Prompt the user for input
    printf("Enter a non-negative integer (up to 30): ");
    scanf("%d", &n);

    if (n < 0 || n > 30) {
        printf("Please enter a non-negative integer up to 30.\n");
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
    int result;
    if (pthread_join(tid, (void**)&result) != 0) {
        perror("pthread_join");
        return 1;
    }

    printf("Sum of non-negative integers from 1 to %d: %d\n", n, result);

    return 0;
}