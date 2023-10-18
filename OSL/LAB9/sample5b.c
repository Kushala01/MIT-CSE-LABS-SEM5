#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    char z = *(const char *)0; // Attempt to read a character from memory location zero (null pointer)

    // The next line is never executed because accessing location zero results in a segmentation fault.
    // It's included to demonstrate the intent.
    printf("I read from location zero\n");

    exit(EXIT_SUCCESS); // Exit the program with a successful status code
}