#include <stdio.h>
#include <math.h>


int main() 
{
	int a, b, c;
	printf("Enter a, b, c: ");
	scanf("%d %d %d", &a, &b, &c);
	if (a == 0){
		printf("This is not a quadratic equation");
	} else {
		int discriminant = b * b - 4 * a * c;
		if (discriminant == 0) {
			double root = -b / (2 * a);
            printf("Two equal real roots: %.2lf and %.2lf\n", root, root);
		} else if (discriminant > 0) {
			double root1 = (-b + sqrt(discriminant)) / (2 * a);
            double root2 = (-b - sqrt(discriminant)) / (2 * a);
            printf("Two distinct real roots: %.2lf and %.2lf\n", root1, root2);
		} else if (discriminant < 0) {
			printf("Two complex roots: %.2lf + %.2lfi and %.2lf - %.2lfi\n",
                   -b / (2 * a), sqrt(-discriminant) / (2 * a),
                   -b / (2 * a), sqrt(-discriminant) / (2 * a));
		}
	}
}