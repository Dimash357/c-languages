#include <stdio.h>

int main() {
    int numbers[6];
    int i, j, temp;

    printf("Enter 6 integers:\n");
    for (i = 0; i < 6; i++) {
        scanf("%d", &numbers[i]);
    }

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5 - i; j++) {
            if (numbers[j] > numbers[j + 1]) {
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }

    printf("Numbers in ascending order: ");
    for (i = 0; i < 6; i++) {
        printf("%d ", numbers[i]);
    }

    printf("\n");
    return 0;
}
