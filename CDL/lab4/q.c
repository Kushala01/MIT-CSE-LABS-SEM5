#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getNextToken.h"

struct node {
    char lexeme[20];
    struct node* next;
};

struct entry {
    char lexeme[20];
    char dtype[10];
    char rtype[10];
    char funcType[20]; // New field to store function type
    int numArgs;       // New field to store number of arguments
};

const char *Datatypes[] = {"int", "char", "float"};
const char *Operators[] = {"+", "-"};
const char *Predef[] = {"printf", "scanf"};
struct entry symbolTable[100];
int entryCount = 0;

unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return (hash % 100);
}

struct node* HashMap[100] = {NULL};

void insert(char* str) {
    int hashVal = hash(str);
    struct node* temp = (struct node*) malloc(sizeof(struct node));
    strcpy(temp->lexeme, str);

    if (HashMap[hashVal] == NULL) {
        HashMap[hashVal] = temp;
    } else {
        temp->next = HashMap[hashVal];
        HashMap[hashVal] = temp;
    }
}

int search(char* str) {
    int hashVal = hash(str);
    struct node* temp = HashMap[hashVal];

    while(temp != NULL) {
        if (strcmp(temp->lexeme, str) == 0) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int isDtype(const char *str) {
    for (int i = 0; i < sizeof(Datatypes) / sizeof(char *); i++) {
        if (strcmp(str, Datatypes[i]) == 0)
            return 1;
    }
    return 0;
}

int isOperator(const char *str) {
    for (int i = 0; i < sizeof(Operators) / sizeof(char *); i++) {
        if (strcmp(str, Operators[i]) == 0)
            return 1;
    }
    return 0;
}

int notPreDefined(char* str) {
    for (int i = 0; i < sizeof(Predef) / sizeof(char *); i++) {
        if (strcmp(str, Predef[i]) == 0)
            return 0;
    }
    return 1;
}

int main() {
    FILE *fin = fopen("input.c", "r");
    if (!fin) {
        printf("Error! File cannot be opened!\n");
        return 0;
    }
    struct token tkn;
    struct token nxt;

    char dtypeBuf[10] = "unkwn"; 
    int serialNumber = 1;

    while ((tkn = getNextToken(fin)).row != -1) {
        printf("<%s, %d, %d>\n", tkn.type, tkn.row, tkn.col);

        if (strcmp(tkn.type, "Identifier") == 0 && notPreDefined(tkn.lexeme) && !isOperator(tkn.lexeme)) {
            if (search(tkn.lexeme) == 0) {
                struct entry tuple;
                strcpy(tuple.dtype, dtypeBuf);
                strcpy(tuple.rtype, "NULL");
                strcpy(tuple.lexeme, tkn.lexeme);
                strcpy(tuple.funcType, "-");
                tuple.numArgs = 0;

                // Check if the identifier is "main"
                if (strcmp(tkn.lexeme, "main") == 0) {
                    if ((nxt = getNextToken(fin)).row != -1 && strcmp(nxt.lexeme, "(") == 0) {
                        strcpy(tuple.dtype, "FUNC");
                        strcpy(tuple.rtype, "int"); // Assuming "main" returns int

                        // Parse function arguments and update tuple.numArgs
                        int numArgs = 0;
                        while ((nxt = getNextToken(fin)).row != -1) {
                            if (strcmp(nxt.lexeme, ")") == 0) {
                                break;
                            }
                            if (strcmp(nxt.type, "Identifier") == 0) {
                                numArgs++;
                            }
                        }

                        // Update tuple fields
                        strcpy(tuple.funcType, "int");
                        tuple.numArgs = numArgs;
                    }
                }
                else if ((nxt = getNextToken(fin)).row != -1 && strcmp(nxt.lexeme, "(") == 0) {
                    strcpy(tuple.dtype, "FUNC");
                    strcpy(tuple.rtype, dtypeBuf);

                    // Parse function arguments and update tuple.numArgs
                    int numArgs = 0;
                    while ((nxt = getNextToken(fin)).row != -1) {
                        if (strcmp(nxt.lexeme, ")") == 0) {
                            break;
                        }
                        if (strcmp(nxt.type, "Identifier") == 0) {
                            numArgs++;
                        }
                    }

                    // Update tuple fields
                    strcpy(tuple.funcType, dtypeBuf);
                    tuple.numArgs = numArgs;
                }

                symbolTable[entryCount++] = tuple;
                insert(tuple.lexeme);
            }
        }
        else if (strcmp(tkn.type, "Keyword") == 0) {
            if (isDtype(tkn.lexeme) == 0) {
                strcpy(dtypeBuf, "-");
            } else {
                strcpy(dtypeBuf, tkn.lexeme);
            }
        }
    }

    printf("\n\nSymbol Table\n\n");
    printf("S.No.\tLexeme\t\tDtype\t\tRtype\t\tFunction Type\t\tNum Args\n");
    for (int i = 0; i < entryCount; i++) {
        printf("%d\t%s\t\t%s\t\t%s\t\t%s\t\t%d\n", serialNumber++, symbolTable[i].lexeme, symbolTable[i].dtype, symbolTable[i].rtype, symbolTable[i].funcType, symbolTable[i].numArgs);
    }
    fclose(fin);
    return 0;
}
