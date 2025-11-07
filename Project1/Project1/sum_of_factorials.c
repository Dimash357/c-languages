#include <stdio.h>

int main() {
    unsigned long long sum = 0;
    unsigned long long factorial = 1;

    for (int n = 1; n <= 20; n++) {
        factorial *= n;
        sum += factorial;
    }

    printf("The sum of factorials from 1! to 20! is: %llu\n", sum);

    return 0;
}
