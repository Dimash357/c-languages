#include <stdio.h>

int main() {
    float x = 2.5;
    int a = 7;
	int b = 3;
    float y = 4.7;

    float result1 = x + a % 3 * (int)(x + y) % 2 / 4;
    float result2 = (float)(a + b) / 2 + (int)x % (int)y;

    printf("Result1 = %d\n", result1);
    printf("Result2 = %d\n", result2);
    return 0;
}
