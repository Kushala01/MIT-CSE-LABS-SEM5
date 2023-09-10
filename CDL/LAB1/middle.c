#include <stdio.h>

int main() {
    FILE *file;
    char filename[100];
    long middle;

    printf("Enter the name of the file: ");
    scanf("%s", filename);

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Could not open the file.\n");
        return 1;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);

    // Calculate the middle position
    middle = fileSize / 2;

    // Move to the middle of the file
    fseek(file, middle, SEEK_SET);

    // Read and print from the middle to the end of the file
    int c;
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }

    fclose(file);

    return 0;
}
