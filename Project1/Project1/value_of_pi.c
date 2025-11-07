#include <stdio.h>
#include <math.h>


int main() 
{
	double pi = 0.0;
    double term = 1.0;
    double n = 1.0;
    double sign = 1.0;
	
	while (fabs(term) >= 1e-6) {
		pi += term;
		n += 2;
		sign = -sign;
		term = sign / n;
	}

	pi *= 4;
	printf("Pi: %f", pi);
	
	return 0;

}