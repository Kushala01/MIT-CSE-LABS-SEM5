/*Write a program to copy character-by character copy is accomplished using calls to the
functions referenced in stdio.h*/

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char c; // Variable to store the character being read/written
    int in, out; // File descriptors for input and output files

    // Open the source file for reading ('in' file descriptor)
    in = open(argv[1], O_RDONLY);
    // Open or create the destination file for writing ('out' file descriptor)
    out = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

    // Check if file opening was successful
    if (in == -1 || out == -1) {
        write(1, "Error\n", 6); // Write error message to standard output
        exit(0); // Exit the program
    }

    // Read characters from the source file and write them to the destination file
    while (read(in, &c, 1) == 1) {
        write(out, &c, 1); // Write the character to the destination file
    }

    // Write success message to standard output
    write(1, "Copied!\n", 8);

    return 0; // Return success status code
}
