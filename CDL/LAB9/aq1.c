#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Function to skip whitespace characters
void skipWhitespace(const char **expr) {
    while (**expr == ' ' || **expr == '\t' || **expr == '\n' || **expr == '\r') {
        (*expr)++;
    }
}

// Function to parse a number from the expression
int parseNumber(const char **expr) {
    int num = 0;
    while (**expr >= '0' && **expr <= '9') {
        num = num * 10 + (**expr - '0');
        (*expr)++;
    }
    return num;
}

// Function to parse the conditional expression
int parseConditional(const char **expr);

// Function to parse the right-hand side of the assignment
int parseAssignment(const char **expr) {
    skipWhitespace(expr);
    int result = parseConditional(expr);
    skipWhitespace(expr);
    return result;
}

// Function to parse the conditional expression
int parseConditional(const char **expr) {
    skipWhitespace(expr);
    int condition = parseAssignment(expr);
    skipWhitespace(expr);

    if (**expr == '?') {
        (*expr)++;
        skipWhitespace(expr);
        int trueValue = parseAssignment(expr);
        skipWhitespace(expr);
        if (**expr == ':') {
            (*expr)++;
            skipWhitespace(expr);
            int falseValue = parseAssignment(expr);
            skipWhitespace(expr);
            return condition ? trueValue : falseValue;
        } else {
            printf("Error: Expected ':' after '?' in conditional expression.\n");
            exit(1);
        }
    }
    return condition;
}

int main() {
    const char *expression = "max = a ? a : b;";
    int result;

    result = parseAssignment(&expression);
    if (*expression == '\0') {
        printf("Parsed successfully: max = %d\n", result);
    } else {
        printf("Error: Unexpected characters in the expression.\n");
    }

    return 0;
}
