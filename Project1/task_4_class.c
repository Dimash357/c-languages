#include <stdio.h>
#include <string.h>

int main() {
    char str1[100], str2[100], str3[100], *p1, *p2, *p3, *temp;

    printf("Enter 3 strings:\n");
    scanf("%s %s %s", str1, str2, str3);

    p1 = str1;
    p2 = str2;
    p3 = str3;

    if (strcmp(p1, p2) > 0) { 
		temp = p1; p1 = p2; p2 = temp; 
	}
    if (strcmp(p1, p3) > 0) { 
		temp = p1; p1 = p3; p3 = temp; 
	}
    if (strcmp(p2, p3) > 0) { 
		temp = p2; p2 = p3; p3 = temp; 
	}

    printf("\nStrings in ascending order:\n%s\n%s\n%s\n", p1, p2, p3);

    return 0;
}
