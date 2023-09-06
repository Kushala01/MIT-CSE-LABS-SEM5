/*Write a multithreaded program that performs the sum of even numbers and odd
numbers in an input array. Create a separate thread to perform the sum of even
numbers and odd numbers. The parent thread has to wait until both the threads are
done.*/
#include <stdio.h>
#include <pthread.h>

#define MAX_SIZE 100

int numbers[MAX_SIZE];
int size;
int even_sum = 0;
int odd_sum = 0;

void* compute_even_sum(void* param) {
    for (int i = 0; i < size; i++) {
        if (numbers[i] % 2 == 0) {
            even_sum += numbers[i];
        }
    }
    return 0;
}

void* compute_odd_sum(void* param) {
    for (int i = 0; i < size; i++) {
        if (numbers[i] % 2 != 0) {
            odd_sum += numbers[i];
        }
    }
    return 0;
}

int main() {
    printf("Enter the number of elements in the array (max %d): ", MAX_SIZE);
    scanf("%d", &size);

    printf("Enter the array elements:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &numbers[i]);
    }

    pthread_t even_thread, odd_thread;

    // Create threads
    pthread_create(&even_thread, 0, compute_even_sum, 0);
    pthread_create(&odd_thread, 0, compute_odd_sum, 0);

    // Wait for threads to finish
    pthread_join(even_thread, 0);
    pthread_join(odd_thread, 0);

    // Print results
    printf("Sum of even numbers: %d\n", even_sum);
    printf("Sum of odd numbers: %d\n", odd_sum);

    return 0;
}