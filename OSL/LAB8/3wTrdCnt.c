/*Write a multithreaded program for generating prime numbers from a given starting
number to the given ending number.*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function to check if a number is prime
int isPrime(int num) {
    if (num <= 1) {
        return 0; // 0 and 1 are not prime
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0; // It's divisible by a number other than 1 and itself
        }
    }
    return 1; // It's prime
}

// Function to find prime numbers in a range and store them in an array
void* findPrimes(void* arg) {
    int* params = (int*)arg;
    int start = params[0];
    int end = params[1];

    // Find prime numbers in the given range
    for (int num = start; num <= end; num++) {
        if (isPrime(num)) {
            printf("%d is prime.\n", num);
        }
    }

    pthread_exit(NULL);
}

int main() {
    int start, end, numThreads;

    // Prompt the user for input
  
    printf("Enter the starting number: ");
    scanf("%d", &start);
    printf("Enter the ending number: ");
    scanf("%d", &end);
    printf("Enter the number of threads: ");
    scanf("%d", &numThreads);

    //if you dont want the user to specify the number of threads
 // numThreads = 4; // Use 4 threads


    if (start < 2 || end < 2 || start > end || numThreads <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    // Calculate the range for each thread
    int range = (end - start + 1) / numThreads;
    pthread_t threads[numThreads];
    int params[numThreads][2];

    // Create and start the threads
    for (int i = 0; i < numThreads; i++) {
        params[i][0] = start + i * range;
        params[i][1] = i == numThreads - 1 ? end : start + (i + 1) * range - 1;

        if (pthread_create(&threads[i], 0, findPrimes, params[i]) != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    // Wait for the threads to finish
    for (int i = 0; i < numThreads; i++) {
        if (pthread_join(threads[i], 0) != 0) {
            perror("pthread_join");
            return 1;
        }
    }

    return 0;
}
