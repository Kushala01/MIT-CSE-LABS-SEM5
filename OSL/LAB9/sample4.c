#include <stdlib.h>

// Define a constant for one kilobyte in bytes
#define ONE_K (1024)

int main() {
    char *some_memory;  // Declare a pointer to hold allocated memory
    char *scan_ptr;     // Declare a pointer for scanning through allocated memory

    // Allocate 1KB of memory using malloc
    some_memory = (char *)malloc(ONE_K);

    // Check if memory allocation was successful
    if (some_memory == NULL) {
        exit(EXIT_FAILURE);  // Exit the program with failure if memory allocation fails
    }

    scan_ptr = some_memory;  // Initialize the scanning pointer with the start of the allocated memory

    while(1) {
        *scan_ptr = '\0';   // Set the current memory location to null (string termination)
        scan_ptr++;         // Move the scanning pointer to the next location in memory
    }

    exit(EXIT_SUCCESS);  // The program will never reach this point, but it's included for completeness
}