#include <stdio.h>
#include <ctype.h>

int main() {
    char ch;
    int letters = 0, spaces = 0, digits = 0, others = 0;

    printf("Enter a line of text: ");

    while ((ch = getchar()) != '\n') {
        if (isalpha(ch))
            letters++;
        else if (isdigit(ch))
            digits++;
        else if (isspace(ch))
            spaces++;
        else
            others++;
    }

    printf("Letters: %d\n", letters);
    printf("Digits: %d\n", digits);
    printf("Spaces: %d\n", spaces);
    printf("Other characters: %d\n", others);

    return 0;
}
