/*Write a C program to collect statistics of a source file and display total number of blank lines, total
number of lines ending with semicolon, total number of blank spaces.*/

#include <stdio.h>

int main() {
    FILE *file;
    char filename[100];
    int blankLines = 0, semicolonLines = 0, blankSpaces = 0;
    char c, prevChar = '\n'; // Initialize prevChar to '\n' to handle the start of the file

    printf("Enter the name of the source file: ");
    scanf("%s", filename);

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Could not open the file.\n");
        return 1;
    }

    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            // Check if the line is blank (only contains spaces or tabs)
            int isBlank = 1;
            while ((c = fgetc(file)) != '\n') {
                if (c != ' ' && c != '\t') {
                    isBlank = 0;
                }
            }

            if (isBlank) {
                blankLines++;
            } else if (prevChar == ';') {
                semicolonLines++;
            }
        } else if (c != ' ' && c != '\t') {
            // Count non-space characters to calculate blank spaces
            blankSpaces++;
        }

        prevChar = c;
    }

    fclose(file);

    printf("Total blank lines: %d\n", blankLines);
    printf("Total lines ending with a semicolon: %d\n", semicolonLines);
    printf("Total blank spaces: %d\n", blankSpaces);

    return 0;
}
