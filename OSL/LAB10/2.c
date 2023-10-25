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
                if(can_allocate){
                    finish[i]=true;
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

   

int main() {

}