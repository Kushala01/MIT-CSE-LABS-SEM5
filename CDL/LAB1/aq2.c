#include <stdio.h>

int main() {
    FILE *file;
    char filename[100];
    char c;
    int lineCount = 0;
    int continuePrinting = 1;

    printf("Enter the name of the file: ");
    scanf("%s", filename);

    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Could not open the file.\n");
        return 1;
    }

    while ((c = fgetc(file)) != EOF) {
        putchar(c);

        if (c == '\n') {
            lineCount++;

            if (lineCount == 5) {
                printf("Press 'C' to continue or 'Q' to quit: ");
                char option;
                scanf(" %c", &option);

                if (option == 'Q' || option == 'q') {
                    continuePrinting = 0;
                    break;
                }

                lineCount = 0;
            }
        }
    }

    fclose(file);

    return 0;
}
