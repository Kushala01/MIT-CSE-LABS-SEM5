/*Demonstrate the use of different conversion specifiers and resulting output to
allow the items to be printed.*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main()
{
    int a = 20;
    float b = 54.258;
    char c = 'K';
    char str[] = "Kushala";

    // Printing integer 'a' using %d, floating-point 'b' using %f, character 'c' using %c,
    // string 'str' using %s, and 'a' in hexadecimal using %x
    printf("a = %d, b = %f, c = %c, str = %s, Hexadecimal for a = %x\n", a, b, c, str, a);

    // Demonstrating error printing using %m
    errno = EPERM; // Setting an error number
    printf("Error Access Number : %m\n");

    return 0;
}

