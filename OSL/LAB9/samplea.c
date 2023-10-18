#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    char *some_memory = (char *)0; // Declare a character pointer initialized to a null pointer (address 0)
    printf("A read from null %s\n", some_memory); // Attempt to read from the null pointer

    // The next line attempts to write to the null pointer, which will cause a segmentation fault.
    // It's commented out to prevent program termination for demonstration purposes.
    // sprintf(some_memory, "A write to null");

    exit(EXIT_SUCCESS); // Exit the program with a successful status code
}