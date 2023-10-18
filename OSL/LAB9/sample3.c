#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Define a constant for one kilobyte in bytes
#define ONE_K (1024)

int main() {
    char *some_memory;           // Declare a pointer to hold allocated memory
    int size_to_allocate = ONE_K;  // Define the size of each memory block to allocate (1KB)
    int megs_obtained = 0;       // Counter for tracking the allocated megabytes
    int ks_obtained = 0;         // Counter for tracking the allocated kilobytes

    // Continuously allocate memory in 1KB blocks
    while (1) {
        for (ks_obtained = 0; ks_obtained < 1024; ks_obtained++) {
            some_memory = (char *)malloc(size_to_allocate);  // Allocate memory

            // Check if memory allocation was successful
            if (some_memory == NULL) {
                exit(EXIT_FAILURE);  // Exit the program with failure if memory allocation fails
            }

            // Write "Hello World" into the allocated memory
            sprintf(some_memory, "Hello World");
        }

        megs_obtained++;  // Increment the count of allocated megabytes

        // Print the total allocated megabytes
        printf("Now allocated %d Megabytes\n", megs_obtained);
    }

    exit(EXIT_SUCCESS);  // The program will never reach this point, but it's included for completeness
}