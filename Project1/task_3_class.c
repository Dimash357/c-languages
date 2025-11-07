#include <stdio.h>

int leap(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return 1;
    else
        return 0;
}

int sum_day(int year, int month, int day) {
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int i, total_days = 0;

    if (leap(year))
        days_in_month[1] = 29;

    for (i = 0; i < month - 1; i++) {
        total_days += days_in_month[i];
    }

    total_days += day;

    return total_days;
}

int main() {
    int year, month, day;
    int day_number;

    printf("Enter year: ");
    scanf("%d", &year);
    printf("Enter month (1-12): ");
    scanf("%d", &month);
    printf("Enter day: ");
    scanf("%d", &day);

    day_number = sum_day(year, month, day);

    printf("Day number of the year: %d\n", day_number);

    return 0;
}
