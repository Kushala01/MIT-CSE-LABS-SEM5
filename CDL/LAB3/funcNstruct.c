//Design a lexical Analyzer to generate tokens for functions and structures in ‘C’.
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Define token types
#define KEYWORD 1
#define IDENTIFIER 2
#define SYMBOL 3
#define LITERAL 4
#define END_OF_INPUT 5
#define INVALID_TOKEN 6

// Function to skip whitespace characters
void skipWhitespace(FILE *input) {
    int c;
    while ((c = fgetc(input)) != EOF && isspace(c))
        ;
    ungetc(c, input);
}

// Function to check if a character is a symbol
int isSymbol(char c) {
    return (c == '{' || c == '}' || c == '(' || c == ')' || c == ';' || c == ',' || c == '=' || c == '*');
}

// Function to get the next token from input
int getNextToken(FILE *input, char *lexeme) {
    skipWhitespace(input);

    int c = fgetc(input);

    if (c == EOF) {
        return END_OF_INPUT;
    } else if (isalpha(c) || c == '_') {
        int i = 0;
        lexeme[i++] = c;
        while ((c = fgetc(input)) != EOF && (isalnum(c) || c == '_')) {
            lexeme[i++] = c;
        }
        lexeme[i] = '\0';

        // Check if it's a keyword or an identifier
        if (strcmp(lexeme, "int") == 0 || strcmp(lexeme, "char") == 0 ||
            strcmp(lexeme, "float") == 0 || strcmp(lexeme, "double") == 0 ||
            strcmp(lexeme, "struct") == 0 || strcmp(lexeme, "void") == 0 ||
            strcmp(lexeme, "return") == 0) {
            return KEYWORD;
        } else {
            return IDENTIFIER;
        }
    } else if (isSymbol(c)) {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return SYMBOL;
    } else if (c == '"') {
        int i = 0;
        lexeme[i++] = c;
        while ((c = fgetc(input)) != EOF && c != '"') {
            lexeme[i++] = c;
        }
        if (c == '"') {
            lexeme[i++] = c;
        }
        lexeme[i] = '\0';
        return LITERAL;
    } else {
        // Invalid token
        lexeme[0] = c;
        lexeme[1] = '\0';
        return INVALID_TOKEN;
    }
}

int main() {
    FILE *inputFile = fopen("inp.c", "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    char lexeme[100];
    int tokenType;

    while ((tokenType = getNextToken(inputFile, lexeme)) != END_OF_INPUT) {
        switch (tokenType) {
            case KEYWORD:
                printf("Token: KEYWORD, Lexeme: %s\n", lexeme);
                break;
            case IDENTIFIER:
                printf("Token: IDENTIFIER, Lexeme: %s\n", lexeme);
                break;
            case SYMBOL:
                printf("Token: SYMBOL, Lexeme: %s\n", lexeme);
                break;
            case LITERAL:
                printf("Token: LITERAL, Lexeme: %s\n", lexeme);
                break;
            case INVALID_TOKEN:
                printf("Token: INVALID, Lexeme: %s\n", lexeme);
                break;
        }
    }

    fclose(inputFile);
    return 0;
}
