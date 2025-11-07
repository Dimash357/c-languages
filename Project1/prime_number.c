#include <stdio.h>
#include <stdbool.h>

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    int n;
    printf("Enter an integer greater than 3: ");
    scanf("%d", &n);

    if (n <= 3) {
        printf("Number must be greater than 3.\n");
        return 1;
    }

    if (isPrime(n)) {
        printf("%d is a prime number.\n", n);
    } else {
        printf("%d is not a prime number.\n", n);
    }

    printf("Prime numbers between 100 and 200:\n");
    for (int i = 100; i <= 200; i++) {
        if (isPrime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}