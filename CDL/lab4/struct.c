#include <stdio.h>

// Define a simple structure
struct Student {
    char name[50];
    int roll_number;
    float marks;
};

int main() {
    // Declare and initialize a structure variable
    struct Student s1;
    strcpy(s1.name, "Alice");
    s1.roll_number = 101;
    s1.marks = 95.5;

    // Print the structure values
    printf("Student Name: %s\n", s1.name);
    printf("Roll Number: %d\n", s1.roll_number);
    printf("Marks: %.2f\n", s1.marks);

    return 0;
}
