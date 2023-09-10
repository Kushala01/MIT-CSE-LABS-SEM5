//Design a Lexical Analyzer to generate tokens for a simple arithmetic calculator.
#include <stdio.h>

#include <ctype.h>
#include <string.h>

// Define token types
#define INTEGER 1
#define OPERATOR 2
#define LEFT_PAREN 3
#define RIGHT_PAREN 4
#define END_OF_INPUT 5
#define INVALID_TOKEN 6

// Function to check if a character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to skip whitespace characters
void skipWhitespace(FILE *input) {
    int c;
    while ((c = fgetc(input)) != EOF && isspace(c))
        ;
    ungetc(c, input);
}

// Function to get the next token from input
int getNextToken(FILE *input, char *lexeme) {
    skipWhitespace(input);

    int c = fgetc(input);

    if (c == EOF) {
        return END_OF_INPUT;
    } else if (isdigit(c)) {
        int i = 0;
        lexeme[i++] = c;
        while ((c = fgetc(input)) != EOF && isdigit(c)) {
            lexeme[i++] = c;
        }
        lexeme[i] = '\0';
        ungetc(c, input);
        return INTEGER;
    } else if (isOperator(c)) {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return OPERATOR;
    } else if (c == '(') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return LEFT_PAREN;
    } else if (c == ')') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return RIGHT_PAREN;
    } else {
        // Invalid token
        lexeme[0] = c;
        lexeme[1] = '\0';
        return INVALID_TOKEN;
    }
}

int main() {
    FILE *inputFile = fopen("inp.txt", "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    char lexeme[100];
    int tokenType;

    while ((tokenType = getNextToken(inputFile, lexeme)) != END_OF_INPUT) {
        switch (tokenType) {
            case INTEGER:
                printf("Token: INTEGER, Lexeme: %s\n", lexeme);
                break;
            case OPERATOR:
                printf("Token: OPERATOR, Lexeme: %s\n", lexeme);
                break;
            case LEFT_PAREN:
                printf("Token: LEFT_PAREN, Lexeme: %s\n", lexeme);
                break;
            case RIGHT_PAREN:
                printf("Token: RIGHT_PAREN, Lexeme: %s\n", lexeme);
                break;
            case INVALID_TOKEN:
                printf("Token: INVALID, Lexeme: %s\n", lexeme);
                break;
        }
    }

    fclose(inputFile);
    return 0;
}
