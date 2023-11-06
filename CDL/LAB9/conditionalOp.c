#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct token {
    char type[20];  // Type of the token, e.g., "Identifier", "Operator", etc.
    char lexeme[50]; // Actual text of the token
    int row;        // Row in the source code where the token is found
    int col;        // Column in the source code where the token is found
};

struct token cur;
FILE *f;

struct token getNextToken(FILE *f) {
    // Implementation of tokenization logic goes here
    // This function should read the next token from the file and return it
    struct token tk;
    // ... (fill tk with the next token's data) ...
    return tk;
}

int isRelationalOperator(const char *lexeme) {
    // This function should return 1 if the lexeme is a relational operator
    // For simplicity, let's assume we're only dealing with '>'
    return strcmp(lexeme, ">") == 0;
}

void parseTernaryExpression() {
    // Expect the current token to be an identifier (for the variable 'max').
    if (strcmp(cur.type, "Identifier") != 0) {
        printf("Expected identifier at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }

    // Get the next token, which should be an assignment operator '='.
    cur = getNextToken(f);
    if (strcmp(cur.lexeme, "=") != 0) {
        printf("Expected '=' at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }

    // Get the next token, which should be '('.
    cur = getNextToken(f);
    if (strcmp(cur.lexeme, "(") != 0) {
        printf("Expected '(' at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }

    // Parse the relational expression inside the parentheses.
    cur = getNextToken(f);
    if (strcmp(cur.type, "Identifier") != 0) {
        printf("Expected identifier at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }

    cur = getNextToken(f);
    if (!isRelationalOperator(cur.lexeme)) {
        printf("Expected relational operator at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }

    cur = getNextToken(f);
    if (strcmp(cur.type, "Identifier") != 0) {
        printf("Expected identifier at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }

    // Get the next token, which should be ')'.
    cur = getNextToken(f);
    if (strcmp(cur.lexeme, ")") != 0) {
        printf("Expected ')' at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }

    // Get the next token, which should be '?'.
    cur = getNextToken(f);
    if (strcmp(cur.lexeme, "?") != 0) {
        printf("Expected '?' at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }

    // Parse the true part of the ternary expression.
    cur = getNextToken(f);
    if (strcmp(cur.type, "Identifier") != 0) {
        printf("Expected identifier at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }

    // Get the next token, which should be ':'.
    cur = getNextToken(f);
    if (strcmp(cur.lexeme, ":") != 0) {
        printf("Expected ':' at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }

    // Parse the false part of the ternary expression.
    cur = getNextToken(f);
    if (strcmp(cur.type, "Identifier") != 0) {
        printf("Expected identifier at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }

    // Get the next token, which should be ';'.
    cur = getNextToken(f);
    if (strcmp(cur.lexeme, ";") != 0) {
        printf("Expected ';' at Row : %d and Column : %d\n", cur.row, cur.col);
        exit(EXIT_FAILURE);
    }

    // If we've reached this point, the ternary expression has been successfully parsed.
    printf("Ternary expression parsed successfully.\n");
}

int main(int argc, char **argv) {
    // ... (code to open the file and initialize 'cur' with the first token) ...

    // Start parsing the ternary expression.
    parseTernaryExpression();

    // ... (rest of the main function) ...
    return 0;
}