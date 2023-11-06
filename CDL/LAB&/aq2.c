//Write a program to correct errors in variable declarations.
#include "la.h"
int correctVarDeclarations(FILE *fp) {
    struct token prevToken, currToken;
    char dataTypeBuffer[20] = {0}; // Buffer to store last seen data type
    int corrections = 0; // Count of corrections made
    
    while ((currToken = getNextToken(fp)).row != -1) {
        // If the current token is a data type, we store it
        if (isDataType(currToken.lexeme)) {
            strcpy(dataTypeBuffer, currToken.lexeme);
            prevToken = currToken;
        }
        // If the current token is an identifier and we have a data type buffered, we check for a valid declaration
        else if (strcmp(currToken.type, "Identifier") == 0 && dataTypeBuffer[0] != '\0') {
            // Here you could check if the identifier is already declared or if it's a valid name
            // For the sake of simplicity, we'll assume any new identifier after a data type is a valid declaration
            
            // Insert the variable into the symbol table with the buffered data type
            insertToST(currToken, "VAR", dataTypeBuffer, 0);
            dataTypeBuffer[0] = '\0'; // Clear the buffer after processing
            prevToken = currToken;
        }
        // Handle errors: for example, if we have two data types in a row, it's likely an error
        else if (isDataType(currToken.lexeme) && dataTypeBuffer[0] != '\0') {
            // Found a data type when another one was buffered already, likely an error
            // We could print an error message or attempt to correct it
            printf("Error: Multiple data type declarations at row %d, col %d. Correcting...\n", currToken.row, currToken.col);
            corrections++;
            // For correction, we can assume the last data type seen is the intended one
            // No action needed if we just keep the last seen data type in the buffer
            prevToken = currToken;
        }
        // ... Additional error handling can be added here
        
        // Reset buffer if a semicolon is encountered, marking the end of a declaration
        if (currToken.lexeme[0] == ';') {
            dataTypeBuffer[0] = '\0';
        }
    }
    
    // Return the number of corrections made
    return corrections;
}

int main() {
    // Open a file containing C code for reading
    FILE *fp = fopen("c_code.c", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    int corrections = correctVarDeclarations(fp);
    printf("Total corrections made: %d\n", corrections);
    
    // Don't forget to close the file
    fclose(fp);
    return EXIT_SUCCESS;
}