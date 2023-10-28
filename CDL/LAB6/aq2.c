#include <stdio.h>
#include <string.h>

#define MAX_RULES 10
#define MAX_RULE_LEN 50

char grammar[MAX_RULES][MAX_RULE_LEN];
int numRules;

void removeLeftRecursion(char nonTerminal) {
    int i, j;
    char newNonTerminal[MAX_RULE_LEN];
    char production[MAX_RULE_LEN];

    for (i = 0; i < numRules; i++) {
        if (grammar[i][0] == nonTerminal) {
            int len = strlen(grammar[i]);
            if (grammar[i][3] == nonTerminal) {
                // Left recursion detected

                // Create a new non-terminal
                sprintf(newNonTerminal, "%c'", nonTerminal);
                printf("%s -> %s%s\n", newNonTerminal, grammar[i] + 4, newNonTerminal);

                // Modify the original production
                production[0] = '\0';
                strcat(production, grammar[i] + 4);
                strcat(production, newNonTerminal);

                // Update the production rule
                strcpy(grammar[i], production);

                // Add new production rules for the new non-terminal
                for (j = 0; j < numRules; j++) {
                    if (grammar[j][0] == nonTerminal && grammar[j][3] != nonTerminal) {
                        strcat(grammar[j], newNonTerminal);
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
    printf("Enter the non-terminal to remove left recursion: ");
    scanf(" %c", &nonTerminal);

    removeLeftRecursion(nonTerminal);

    printf("Grammar after left recursion removal:\n");
    for (int i = 0; i < numRules; i++) {
        printf("%s\n", grammar[i]);
    }

    return 0;
}
