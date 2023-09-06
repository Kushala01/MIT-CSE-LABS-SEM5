/*Write a multithreaded program for generating prime numbers from a given starting
number to the given ending number.*/
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct {
    int start;
    int end;
} PrimeRange;

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
    PrimeRange* range = (PrimeRange*)param;

    printf("Prime numbers between %d and %d are:\n", range->start, range->end);
    for (int i = range->start; i <= range->end; i++) {
        if (is_prime(i)) {
            printf("%d\n", i);
        }
    }

    return NULL;
}

int main() {
    PrimeRange range;
    printf("Enter the starting number: ");
    scanf("%d", &range.start);
    printf("Enter the ending number: ");
    scanf("%d", &range.end);

    pthread_t prime_thread;
    pthread_create(&prime_thread, NULL, generate_primes, &range);

    pthread_join(prime_thread, NULL);

    return 0;
}