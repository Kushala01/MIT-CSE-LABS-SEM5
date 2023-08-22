/*Write a program to print the lines of a file that contain a word given as the program
argument (a simple version of grep UNIX utility)*/
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>


void main(int argc, char* argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 3) {
        printf("Insufficient Arguments\n");
        exit(1); // Exit with an error code
    }

    // Open the file for reading
    int fd = open(argv[2], O_RDONLY);
    if (fd == -1) {
        printf("File Not Found\n");
        exit(1); // Exit with an error code
    }

    char c; // To store individual characters from the file
    char temp[100]; // To temporarily store content of a line from the file
    int i = 0; // Counter for current position in the 'temp' array
    int k = 0; // Counter for current line number

    // Loop to read characters from the file
    while (read(fd, &c, 1) > 0) {
        // If the character is not a newline, add it to 'temp'
        if (c != '\n') {
            temp[i++] = c;
        }
        else {
            k++; // Increment line counter
            temp[i] = '\0'; // Terminate 'temp' string
            i = 0; // Reset 'i' for next line

            // Check if the word exists in the line
            if (strstr(temp, argv[1])) {
                // Print the line number and the line content
                printf("Line:%d \t %s \n", k, temp);
            }
        }
    }

    // Close the file
    close(fd);

    exit(0); // Exit with a success code
}
