#include <stdio.h>


int main() 
{
	int a, b, c;
	printf("Enter a, b, c: ");
	scanf("%d %d %d", &a, &b, &c);
	if (a < b) {
		if (b < c) {
			printf("The max number is %d", c);
		} else {
			printf("The max number is %d", b);
		}
	} else if (a < c) {
		printf("The max number is %d", c);
	} else {
		printf("The max number is %d", a);
	}

	return 0;
	
}