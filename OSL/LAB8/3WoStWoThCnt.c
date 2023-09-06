/*Write a multithreaded program for generating prime numbers from a given starting
number to the given ending number.*/
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

int start, end;

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

void* generate_primes(void* param) {
    printf("Prime numbers between %d and %d are:\n", start, end);
    for (int i = start; i <= end; i++) {
        if (is_prime(i)) {
            printf("%d\n", i);
        }
    }
    return NULL;
}

int main() {
    printf("Enter the starting number: ");
    scanf("%d", &start);
    printf("Enter the ending number: ");
    scanf("%d", &end);

    pthread_t prime_thread;
    pthread_create(&prime_thread, NULL, generate_primes, NULL);

    pthread_join(prime_thread, NULL);

    return 0;
}
