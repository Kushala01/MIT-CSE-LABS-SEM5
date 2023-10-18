#include <stdlib.h>
#include <stdio.h>

#define ONE_K (1024)

int main() {
    char *some_memory; // Declare a pointer to char
    int exit_code = EXIT_FAILURE; // Initialize the exit code to indicate failure

    // Allocate memory for one kilobyte (1024 bytes) and store the pointer in some_memory
    some_memory = (char *)malloc(ONE_K);

    if (some_memory != NULL) { // Check if memory allocation was successful
        free(some_memory); // Free the allocated memory to prevent memory leaks
        printf("Memory allocated and freed again\n");
        exit_code = EXIT_SUCCESS; // Set the exit code to indicate success
    }

    exit(exit_code); // Exit the program with the appropriate exit code
}