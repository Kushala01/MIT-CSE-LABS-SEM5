#include <stdio.h>
#include <string.h>

#define MAX_RULES 10
#define MAX_RULE_LEN 20

char grammar[MAX_RULES][MAX_RULE_LEN];
int numRules;

// Function to compute the First set for a given non-terminal X
void first(char X) {
    printf("First(%c): ", X);
    for (int i = 0; i < numRules; i++) {
        if (grammar[i][0] == X) {
            if (grammar[i][2] >= 'a' && grammar[i][2] <= 'z') {
                printf("%c ", grammar[i][2]);
            } else if (grammar[i][2] >= 'A' && grammar[i][2] <= 'Z') {
                first(grammar[i][2]);
            }
        }
    }
}

// Function to compute the Follow set for a given non-terminal X
void follow(char X) {
    printf("Follow(%c): ", X);
    if (X == grammar[0][0]) {
        printf("$ ");  // '$' represents end of input
    }
    for (int i = 0; i < numRules; i++) {
        for (int j = 2; j < strlen(grammar[i]); j++) {
            if (grammar[i][j] == X) {
                if (j == strlen(grammar[i]) - 1) {
                    if (grammar[i][0] != X) {
                        follow(grammar[i][0]);
                    }
                } else {
                    if (grammar[i][j + 1] >= 'a' && grammar[i][j + 1] <= 'z') {
                        printf("%c ", grammar[i][j + 1]);
                    } else if (grammar[i][j + 1] >= 'A' && grammar[i][j + 1] <= 'Z') {
                        first(grammar[i][j + 1]);
                    }
                }
            }
        }
    }
}

int main() {
    printf("Enter the number of production rules: ");
    scanf("%d", &numRules);

    printf("Enter the production rules:\n");
    for (int i = 0; i < numRules; i++) {
        scanf("%s", grammar[i]);
    }

    char nonTerminal;
    printf("Enter the non-terminal to find First and Follow for: ");
    scanf(" %c", &nonTerminal);

    first(nonTerminal);
    printf("\n");
    follow(nonTerminal);
    printf("\n");

    return 0;
}