/*
Write a recursive descent parser for the following simple grammars
S -> a | > | (T)
T ->T,S | S
after removing LR
S -> a | > | (T)
T -> ST'
T' -> ,ST' | empty
*/
#include <stdio.h>
#include <stdlib.h>

int curr = 0;
char str[100];

// Function declarations
void S();
void T();
void invalid();
void valid();

void S() {
    if(str[curr] == 'a') {
        curr++;
    } else if(str[curr] == '>') {
        curr++;
    } else if(str[curr] == '(') {
        curr++;
        T();
        if(str[curr] == ')') {
            curr++;
        } else {
            invalid();
        }
    } else {
        invalid();
    }
}

void T() {
    S();
    while(str[curr] == ',') {
        curr++;
        S();
    }
}

void invalid() {
    printf("ERROR!\n");
    exit(0);
}

void valid() {
    printf("SUCCESS!\n");
    exit(0);
}

int main() {
    printf("Enter String: ");
    scanf("%s", str);
    S();

    if(str[curr] == '\0') {
        valid();
    } else {
        invalid();
    }

    return 0;
}
/*Enter String: a
SUCCESS!

Enter String: (a,a,>)
SUCCESS!

Enter String: (a,)
ERROR!

Enter String: (,a)
ERROR!*/
