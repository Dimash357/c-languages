#include <stdio.h>

int max(int a, int b);

int main() {
    int num1, num2, result;

    printf("Enter two integers: ");
    scanf("%d %d", &num1, &num2);

    result = max(num1, num2);
    printf("The larger number is: %d\n", result);

    return 0;
}

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}
