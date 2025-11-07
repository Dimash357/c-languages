#include <stdio.h>

int main() {
    int arr[6];
    int i, j, minIndex, temp;

    printf("Enter 6 integers: ");
    for (i = 0; i < 6; i++) {
        scanf("%d", &arr[i]);
    }

    for (i = 0; i < 5; i++) {
        minIndex = i;
        for (j = i + 1; j < 6; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }

    printf("Sorted array in ascending order: ");
    for (i = 0; i < 6; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
