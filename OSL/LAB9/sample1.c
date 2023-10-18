#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Define a constant for one megabyte in bytes
#define A_MEGABYTE (1024 * 1024)

int main() {
    char *some_memory;       // Declare a pointer to hold allocated memory
    int megabyte = A_MEGABYTE;   // Define the size of memory to allocate in bytes
    int exit_code = EXIT_FAILURE;  // Set the default exit code to failure
    // Allocate memory using malloc
    some_memory = (char *)malloc(megabyte);
    // Check if malloc was successful
    if (some_memory != NULL) {
        // If successful, write "Hello World" into the allocated memory
        sprintf(some_memory, "Hello World\n");
        // Print the content of the allocated memory
        printf("%s", some_memory);
        // Set the exit code to success
        exit_code = EXIT_SUCCESS;
    }
    // Exit the program with the determined exit code
    exit(exit_code);
}
