#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

#define NUM_CUSTOMERS 5
#define NUM_RESOURCES 3

int available[NUM_RESOURCES];
int maximum[NUM_CUSTOMERS][NUM_RESOURCES];
int allocation[NUM_CUSTOMERS][NUM_RESOURCES];
int need[NUM_CUSTOMERS][NUM_RESOURCES];

pthread_mutex_t mutex;

bool isSafeState(int customer) {
    int work[NUM_RESOURCES];
    int finish[NUM_CUSTOMERS];

    // Initialize work and finish arrays
    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = available[i];
    }
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        finish[i] = false;
    }

    // Find a customer that can be satisfied
    int customer_count = 0;
    while (customer_count < NUM_CUSTOMERS) {
        bool found = false;
        for (int i = 0; i < NUM_CUSTOMERS; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < NUM_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    // Customer can be satisfied
                    finish[i] = true;
                    for (int j = 0; j < NUM_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                    found = true;
                    customer_count++;
                }
            }
        }
        if (!found) {
            // No customer can be satisfied
            return false;
        }
    }

    // All customers can be satisfied
    return true;
}

bool requestResources(int customer, int request[]) {
    // Check if the request exceeds the maximum needs of the customer.
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (request[i] > need[customer][i]) {
            return false; // Request exceeds maximum needs
        }
    }

    // Check if the request can be satisfied with the available resources.
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (request[i] > available[i]) {
            return false; // Request cannot be satisfied immediately
        }
    }

    // Attempt to allocate the resources temporarily to check for safety.
    for (int i = 0; i < NUM_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[customer][i] += request[i];
        need[customer][i] -= request[i];
    }

    if (isSafeState(customer)) {
        // The request is granted as it keeps the system in a safe state.
        return true;
    } else {
        // The request is denied as it would lead to an unsafe state.
        // Rollback the temporary allocation.
        for (int i = 0; i < NUM_RESOURCES; i++) {
            available[i] += request[i];
            allocation[customer][i] -= request[i];
            need[customer][i] += request[i];
        }
        return false;
    }
}

void releaseResources(int customer, int release[]) {
    pthread_mutex_lock(&mutex);

    // Check if the release exceeds the allocated resources for the customer.
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (release[i] > allocation[customer][i]) {
            // Invalid release request: trying to release more than allocated.
            pthread_mutex_unlock(&mutex);
            return; // Handle this case according to your needs.
        }
    }

    // Update the allocation and need matrices and release the resources.
    for (int i = 0; i < NUM_RESOURCES; i++) {
        allocation[customer][i] -= release[i];
        need[customer][i] += release[i];
        available[i] += release[i];
    }

    pthread_mutex_unlock(&mutex);
}

void initializeDataStructures() {
    // Initialize available array with the total number of each resource.
    int total_resources[NUM_RESOURCES] = {10, 5, 7};
    for (int i = 0; i < NUM_RESOURCES; i++) {
        available[i] = total_resources[i];
    }

    // Initialize the maximum matrix with the maximum resource needs of each customer.
    int max_requests[NUM_CUSTOMERS][NUM_RESOURCES] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            maximum[i][j] = max_requests[i][j];
        }
    }

    // Initialize allocation and need matrices to zero.
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            allocation[i][j] = 0;
            need[i][j] = maximum[i][j];
        }
    }
}


void* customerThread(void* arg) {
    int customer = *((int*)arg);
    int request[NUM_RESOURCES];

    // Generate a random request
    for (int i = 0; i < NUM_RESOURCES; i++) {
        request[i] = rand() % (need[customer][i] + 1);
    }

    printf("Customer %d requesting resources: ", customer);
    for (int i = 0; i < NUM_RESOURCES; i++) {
        printf("%d ", request[i]);
    }
    printf("\n");

    if (requestResources(customer, request)) {
        printf("Customer %d's request granted.\n", customer);
        releaseResources(customer, request);
        printf("Customer %d released resources.\n", customer);
    } else {
        printf("Customer %d's request denied.\n", customer);
    }

    pthread_exit(NULL);
}

   

int main() {
    pthread_t threads[NUM_CUSTOMERS];
    int customer_args[NUM_CUSTOMERS];

    srand(time(NULL));

    // Initialize data structures (available, maximum, allocation, and need)
    initializeDataStructures();

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create customer threads
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        customer_args[i] = i;
        pthread_create(&threads[i], NULL, customerThread, &customer_args[i]);
    }

    // Join customer threads
    for (int i = 0; i < NUM_CUSTOMERS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
