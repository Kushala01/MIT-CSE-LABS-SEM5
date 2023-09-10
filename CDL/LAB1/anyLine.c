#include <stdio.h>

int main() {
    FILE *file;
    char filename[100];
    long lineNumber;
    char line[256];  // Adjust the buffer size as needed

    printf("Enter the name of the file: ");
    scanf("%s", filename);

    printf("Enter the line number you want to go to: ");
    scanf("%ld", &lineNumber);

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Could not open the file.\n");
        return 1;
    }

    // Calculate the offset to the start of the desired line
    long offset = 0;
    long currentLine = 1;
    while (currentLine < lineNumber) {
        if (fgets(line, sizeof(line), file) == NULL) {
            printf("Line number %ld does not exist in the file.\n", lineNumber);
            fclose(file);
            return 1;
        }
        offset = ftell(file);
        currentLine++;
    }

    // Seek to the calculated offset
    fseek(file, offset, SEEK_SET);

    // Read and print the desired line
    if (fgets(line, sizeof(line), file) != NULL) {
        printf("Line %ld: %s", lineNumber, line);
    }

    fclose(file);

    return 0;
}
