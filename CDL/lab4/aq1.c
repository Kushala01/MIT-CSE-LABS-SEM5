/* aq1=same as q1 just need to add strcut in keywords[]
Write a getNextToken ( ) to generate tokens for the perl script given below.
#! /usr/bin/perl
#get total number of arguments passed.
$n = scalar (@_);
$sum = 0;
foreach $item(@_) {
$sum += $item;
}
$average = $sum + $n;
#! Represents path which has to be ignored by getNextToken().
# followed by any character other than ! represents comments.
$n followed by any identifier should be treated as a single token.
Scalar, foeach are considered as keywords.
@_, += are treated as single tokens.
Remaining symbols are tokenized accordingly.*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct token {
    char lexeme[65];
    int row, col;
    char type[20];
};

static int row = 1, col = 1;

int isKeyword(const char *str) {
    const char *keywords[] = {"scalar", "foreach"};
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isSymbol(char c) {
    const char symbols[] = {'@', '+', '=', '!', '#', '$', '%', '^', '&', '*', '(', ')'};
    for (int i = 0; i < sizeof(symbols) / sizeof(symbols[0]); i++) {
        if (c == symbols[i])
            return 1;
    }
    return 0;
}

void fillToken(struct token *tkn, char *lexeme, int row, int col, const char *type) {
    tkn->row = row;
    tkn->col = col;
    strcpy(tkn->type, type);
    strncpy(tkn->lexeme, lexeme, 64);
    tkn->lexeme[64] = '\0';
}

struct token getNextToken(FILE *fin) {
    int c;
    struct token tkn = {.row = -1};
    int gotToken = 0;
    char lexeme[65] = "";
    int lexemeIndex = 0;

    while (!gotToken && (c = fgetc(fin)) != EOF) {
        if (c == '!') {
            // Ignore comments starting with '!'
            while ((c = fgetc(fin)) != EOF && c != '\n')
                ;
            if (c == '\n') {
                row++;
                col = 1;
            }
        } else if (isSymbol(c)) {
            // Symbols are treated as single tokens
            lexeme[0] = c;
            lexeme[1] = '\0';
            fillToken(&tkn, lexeme, row, col, "symbol");
            gotToken = 1;
            col++;
        } else if (isalpha(c)) {
            // Start of an identifier or keyword
            lexeme[lexemeIndex++] = c;
            while ((c = fgetc(fin)) != EOF && (isalnum(c) || c == '_')) {
                lexeme[lexemeIndex++] = c;
            }
            lexeme[lexemeIndex] = '\0';

            if (isKeyword(lexeme)) {
                fillToken(&tkn, lexeme, row, col, "keyword");
            } else {
                fillToken(&tkn, lexeme, row, col, "identifier");
            }

            gotToken = 1;
            fseek(fin, -1, SEEK_CUR); // Move the file pointer back by one character
        } else if (isdigit(c)) {
            // Start of a number
            lexeme[lexemeIndex++] = c;
            while ((c = fgetc(fin)) != EOF && isdigit(c)) {
                lexeme[lexemeIndex++] = c;
            }
            lexeme[lexemeIndex] = '\0';
            fillToken(&tkn, lexeme, row, col, "number");
            gotToken = 1;
            fseek(fin, -1, SEEK_CUR); // Move the file pointer back by one character
        } else if (isspace(c)) {
            // Ignore whitespace characters
            if (c == '\n') {
                row++;
                col = 1;
            } else {
                col++;
            }
        } else {
            // Treat any other character as a single token
            lexeme[0] = c;
            lexeme[1] = '\0';
            fillToken(&tkn, lexeme, row, col, "unknown");
            gotToken = 1;
            col++;
        }
    }

    return tkn;
}

int main() {
    FILE *fin = fopen("hello.pl", "r");
    if (!fin) {
        printf("Error! File cannot be opened!\n");
        return 1;
    }

    struct token tkn;
    while ((tkn = getNextToken(fin)).row != -1) {
        printf("<%s, %d, %d>\n", tkn.type, tkn.row, tkn.col);
    }

    fclose(fin);
    return 0;
}
