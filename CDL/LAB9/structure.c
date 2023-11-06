/*structure -> struct id { struct-declaration-list } ;
struct-declaration-list -> struct-declaration struct-declaration-list | ε
struct-declaration -> type-specifier identifier-list ;
type-specifier -> int | char | float | double | struct id
identifier-list -> id | id , identifier-list*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct token {
    char type[20];  // Type of the token, e.g., "Identifier", "Keyword", etc.
    char lexeme[50]; // Actual text of the token
    int row;        // Row in the source code where the token is found
    int col;        // Column in the source code where the token is found
};

struct token cur;
FILE *f;

struct token getNextToken(FILE *f) {
    // Implementation of tokenization logic goes here
    struct token tk;
    // ... (fill tk with the next token's data) ...
    return tk;
}

int isTypeSpecifier(struct token tk) {
    // This function checks if the token is a type specifier
    const char *types[] = {"int", "char", "float", "double", "struct"};
    for (int i = 0; i < 5; ++i) {
        if (strcmp(tk.lexeme, types[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void identifierList() {
    if (strcmp(cur.type, "Identifier") == 0) {
        cur = getNextToken(f);
        while (strcmp(cur.lexeme, ",") == 0) {
            cur = getNextToken(f);
            if (strcmp(cur.type, "Identifier") != 0) {
                printf("Expected identifier at Row : %d and Column : %d\n", cur.row, cur.col);
                exit(EXIT_FAILURE);
            }
            cur = getNextToken(f);
        }
    } else {
        printf("Expected identifier at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }
}

void structDeclaration() {
    if (isTypeSpecifier(cur)) {
        cur = getNextToken(f);
        identifierList();
        if (strcmp(cur.lexeme, ";") == 0) {
            cur = getNextToken(f);
        } else {
            printf("Expected ';' at Row : %d and Column : %d\n", cur.row, cur.col);
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Expected type specifier at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }
}

void structDeclarationList() {
    while (isTypeSpecifier(cur)) {
        structDeclaration();
    }
}

void structure() {
    if (strcmp(cur.lexeme, "struct") == 0) {
        cur = getNextToken(f);
        if (strcmp(cur.type, "Identifier") == 0) {
            cur = getNextToken(f);
            if (strcmp(cur.lexeme, "{") == 0) {
                cur = getNextToken(f);
                structDeclarationList();
                if (strcmp(cur.lexeme, "}") == 0) {
                    cur = getNextToken(f);
                    if (strcmp(cur.lexeme, ";") == 0) {
                        cur = getNextToken(f);
                    } else {
                        printf("Expected ';' at Row : %d and Column : %d\n", cur.row, cur.col);
                        exit(EXIT_FAILURE);
                    }
                } else {
                    printf("Expected '}' at Row : %d and Column : %d\n", cur.row, cur.col);
                    exit(EXIT_FAILURE);
                }
            } else {
                printf("Expected '{' at Row : %d and Column : %d\n", cur.row, cur.col);
                exit(EXIT_FAILURE);
            }
        } else {
            printf("Expected identifier after 'struct' at Row : %d and Column : %d\n", cur.row, cur.col);
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Expected 'struct' at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv) {
    // ... (code to open the file and initialize 'cur' with the first token) ...

    // Start parsing the structure.
    cur = getNextToken(f);
    structure();

    // If we reach this point, the structure has been successfully parsed.
    printf("Structure parsed successfully.\n");

    // ... (rest of the main function) ...
    return 0;
}