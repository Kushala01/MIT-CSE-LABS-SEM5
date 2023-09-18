/*
Write a recursive descent parser for the following simple grammars.
S -> UVW
U -> (S) | aSb | d
V -> aV | empty
W -> cW | empty
*/
#include <stdio.h>
#include <stdlib.h>

int curr = 0;
char str[100];

// Function declarations
void S();
void U();
void V();
void W();
void invalid();
void valid();

void S() {
    U();
    V();
    W();
}

void U() {
    if(str[curr] == '(') {
        int temp = curr;  // store the current position
        curr++;
        S();
        if(str[curr] == ')') {
            curr++;
            return;
        } else {
            curr = temp;  // backtrack
        }
    }
    
    if(str[curr] == 'a') {
        int temp = curr;  // store the current position
        curr++;
        S();
        if(str[curr] == 'b') {
            curr++;
            return;
        } else {
            curr = temp;  // backtrack
        }
    }

    if(str[curr] == 'd') {
        curr++;
    } else {
        invalid();
    }
}

void V() {
    while(str[curr] == 'a') {
        curr++;
    }
}

void W() {
    if(str[curr] == 'c') {
        curr++;
        W();
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
/*tudent@dslab-pc:~/Desktop/210905190_CD$ ./w5q2
Enter String: daca
ERROR!
student@dslab-pc:~/Desktop/210905190_CD$ ./w5q2
Enter String: dac
SUCCESS!
student@dslab-pc:~/Desktop/210905190_CD$ ./w5q2
Enter String: a(d)c
ERROR!
student@dslab-pc:~/Desktop/210905190_CD$ ./w5q2
Enter String: daaaac
SUCCESS!
student@dslab-pc:~/Desktop/210905190_CD$ ./w5q2
Enter String: a(dac)b
SUCCESS!
student@dslab-pc:~/Desktop/210905190_CD$ ./w5q2
Enter String: (d)ac
SUCCESS!
student@dslab-pc:~/Desktop/210905190_CD$ ./w5q2
Enter String: d
SUCCESS!
student@dslab-pc:~/Desktop/210905190_CD$ ./w5
bash: ./w5: No such file or directory
student@dslab-pc:~/Desktop/210905190_CD$ ./w5q2
Enter String: daca
ERROR!*/