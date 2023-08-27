#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main() {
    int num1, num2;

    printf("Enter the first number: ");
    scanf("%d", &num1);

    printf("Enter the second number: ");
    scanf("%d", &num2);
    int sum = add(num1, num2);

    printf("Sum: %d\n", sum);

    return 0;
}
