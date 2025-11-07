#include <stdio.h>


int main() 
{
	int x;
	printf("Enter x value: ");
	scanf("%d", &x);

	if (x < 1) {
		printf("y = %d", x);
	} else if ( x >= 1 && x < 10) {
		int result = 2 * x - 1;
		printf("y = %d", result);
	} else if (x >= 10) {
		int result = 3 * x - 11;
		printf("y = %d", result);
	}

	return 0;
}