// Task 1

#include <stdio.h>
#include <math.h>

int main() {
    double r, h;
    const double PI = 3.14159;

    printf("Enter the radius of the circle (r): ");
    scanf("%lf", &r);

    printf("Enter the height of the cylinder (h): ");
    scanf("%lf", &h);

    double circumference = 2 * PI * r;
    double circle_area = PI * r * r;
    double sphere_surface = 4 * PI * r * r;
    double sphere_volume = (4.0 / 3.0) * PI * pow(r, 3);
    double cylinder_volume = PI * r * r * h;

    printf("\n--- Results ---\n");
    printf("Circumference of the circle: %.2f\n", circumference);
    printf("Area of the circle: %.2f\n", circle_area);
    printf("Surface area of the sphere: %.2f\n", sphere_surface);
    printf("Volume of the sphere: %.2f\n", sphere_volume);
    printf("Volume of the cylinder: %.2f\n", cylinder_volume);

    return 0;
}


// Task 2

#include <stdio.h>

int main() {
    int total_seconds;
    int hours, minutes, seconds;

    printf("Enter total seconds: ");
    scanf("%d", &total_seconds);

    hours = total_seconds / 3600;           
    minutes = (total_seconds % 3600) / 60;  
    seconds = total_seconds % 60;           

    printf("Time: %d:%d:%d\n", hours, minutes, seconds);

    return 0;
}

// Task 3
#include <stdio.h>

int main() {
    int a, b, temp;

    printf("Enter ypur numbers: ");
    scanf("%d %d", &a, &b);           

    printf("Before swap: a = %d, b = %d\n", a, b);

	temp = a;
    a = b;
    b = temp;

    printf("After swap: a = %d, b = %d\n", a, b);


    return 0;
}