#include <stdio.h>
#include <string.h>

const char *direct[] = {"#include", "#define", "#if"};

int is_directive(const char *str) {
    for (int i = 0; i < sizeof(direct) / sizeof(char *); i++) {
        int len = strlen(direct[i]);
        if (strncmp(str, direct[i], len) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char fileName1[100], fileName2[100], fileName3[100];
    char buf[2048];
    FILE *fptr1, *fptr2, *fptr3;
    int flag = 0;

    printf("Enter file name for reading: ");
    scanf("%s", fileName1);
    printf("Enter file name for writing: ");
    scanf("%s", fileName2);

    fptr1 = fopen(fileName1, "r");
    fptr2 = fopen(fileName2, "w");

    if (fptr1 == NULL || fptr2 == NULL) {
        printf("Could not open input or output file!\n");
        return 1;
    }

    char c;
    while ((c = fgetc(fptr1)) != EOF) {
        if (c == ' ' || c == '\t') {
            if (!flag) {
                fputc(' ', fptr2);
                flag = 1;
            }
        } else {
            fputc(c, fptr2);
            flag = 0;
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    printf("Enter file name for writing: ");
    scanf("%s", fileName3);
    fptr2 = fopen(fileName2, "r");
    fptr3 = fopen(fileName3, "w");

    while (fgets(buf, sizeof(buf), fptr2) != NULL) {
        if (!is_directive(buf)) {
            fputs(buf, fptr3);
        }
    }
    fclose(fptr2);
    fclose(fptr3);


    return 0;
}