//1. Write a program to parse pointer declarations.
//type *pointer_name;
#include <stdio.h>
#include <string.h>

typedef struct {
    char lexeme[100];
    int row, col;
} Token;

FILE *f;
Token cur;

Token getNextToken(FILE *f) {
    Token t;
    // Here, you'd implement the logic to get the next token from the input stream.
    // This would involve reading from the file 'f', identifying the token, and updating its row and column.
    // ...
    return t;
}

void dataType() {
    cur = getNextToken(f);
    if (strcmp(cur.lexeme, "int") != 0 && strcmp(cur.lexeme, "float") != 0 && strcmp(cur.lexeme, "char") != 0) {
        printf("Error: Expected data type at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }
}

void pointerDeclaration() {
    dataType();
    cur = getNextToken(f);
    if (strcmp(cur.lexeme, "*") != 0) {
        printf("Error: Expected '*' at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }
    cur = getNextToken(f);
    if (strcmp(cur.lexeme, "Identifier") != 0) {
        printf("Error: Expected identifier at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }
    cur = getNextToken(f);
    if (strcmp(cur.lexeme, ";") != 0) {
        printf("Error: Expected ';' at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }
    printf("Pointer declaration parsed successfully.\n");
}

int main() {
    f = fopen("input.txt", "r");
    if (!f) {
        printf("Error opening file.\n");
        return 1;
    }
    pointerDeclaration();
    fclose(f);
    return 0;
}