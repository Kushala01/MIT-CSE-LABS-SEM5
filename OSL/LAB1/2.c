/*Write a program to list the files given as arguments, stopping every 20 lines until a
key is hit. (a simple version of more UNIX utility)*/
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char* argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 2) {
        printf("Insufficient Arguments\n");
        exit(1); // Exit with an error code
    }

    // Open the file for reading
    int fd = open(argv[1], O_RDONLY);
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
            temp[i] = c;
            i++;
        }
        else {
            k++; // Increment line counter
            temp[i] = '\0'; // Terminate 'temp' string
            i = 0; // Reset 'i' for next line

            // Print the line number and the line content
            printf("Line:%d \t %s \n", k, temp);

            // Check if 20 lines have been displayed
            if (k % 20 == 0) {
                char key;
                printf("\n\nPress Any Key to Continue : \t");
                scanf("%c", &key);
                printf("\n\n");
            }
        }
    }

    // Close the file
    close(fd);

    exit(0); // Exit with a success code
}
