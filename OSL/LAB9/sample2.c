#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Define a constant for one megabyte in bytes
#define A_MEGABYTE (1024 * 1024)

// Define the desired amount of physical memory in megabytes
#define PHY_MEM_MEGS 1024

int main() {
    char *some_memory;                 // Declare a pointer to hold allocated memory
    size_t size_to_allocate = A_MEGABYTE;  // Define the size of each memory block to allocate
    int megs_obtained = 0;             // Counter for tracking the allocated megabytes

    // Keep allocating memory until we reach twice the specified physical memory size
    while (megs_obtained < (PHY_MEM_MEGS * 2)) {
        some_memory = (char *)malloc(size_to_allocate);  // Allocate memory

        // Check if memory allocation was successful
        if (some_memory != NULL) {
            megs_obtained++;  // Increment the count of allocated megabytes

            // Write "Hello World" into the allocated memory
            sprintf(some_memory, "Hello World");

            // Print the allocated memory content and the total megabytes allocated
            printf("%s - now allocated %d Megabytes\n", some_memory, megs_obtained);
        } else {
            exit(EXIT_FAILURE);  // Exit the program with failure if memory allocation fails
        }
    }

    exit(EXIT_SUCCESS);  // Exit the program with success once we've allocated the desired memory
}