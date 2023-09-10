/*That accepts an input statement, identifies the verbs present in them and performs the following
functions
a. INSERT: Used to insert a verb into the hash table.
Syntax: insert (char *str)
b. SEARCH: Used to search for a key(verb) in the hash table. This function is called by
INSERT function. If the symbol table already contains an entry for the verb to be inserted,
then it returns the hash value of the respective verb. If a verb is not found, the function
returns -1.
Syntax: int search (key)*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

struct Node {
    char verb[20];
    struct Node* next;
};

struct Node* hashTable[TABLE_SIZE] = { NULL };

unsigned long hash(char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % TABLE_SIZE;
}

int search(char* verb) {
    unsigned long hashVal = hash(verb);
    struct Node* currentNode = hashTable[hashVal];

    while (currentNode != NULL) {
        if (strcmp(currentNode->verb, verb) == 0) {
            return hashVal; // Verb found, return the hash value
        }
        currentNode = currentNode->next;
    }

    return -1; // Verb not found
}

void insert(char* verb) {
    int hashVal = search(verb); // Check if the verb is already in the hash table

    if (hashVal == -1) {
        hashVal = hash(verb); // Calculate the hash value
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
        strcpy(newNode->verb, verb);
        newNode->next = hashTable[hashVal];
        hashTable[hashVal] = newNode;
    }
}

int main() {
    // Example usage:
    insert("run");
    insert("walk");
    insert("jump");

    int result = search("run");
    if (result != -1) {
        printf("Verb 'run' found at hash value %d.\n", result);
    } else {
        printf("Verb 'run' not found.\n");
    }

    result = search("swim");
    if (result != -1) {
        printf("Verb 'swim' found at hash value %d.\n", result);
    } else {
        printf("Verb 'swim' not found.\n");
    }

    return 0;
}
