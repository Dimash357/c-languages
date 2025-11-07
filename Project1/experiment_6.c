#include <stdio.h>

#define STUDENTS 5
#define SUBJECTS 3

struct Student {
    int num;
    char name[50];
    float score[SUBJECTS]; 
};

void input(struct Student students[]);
void print(struct Student students[]);

int main() {
    struct Student students[STUDENTS];

    input(students);
    print(students);

    return 0;
}

void input(struct Student students[]) {
    for (int i = 0; i < STUDENTS; i++) {
        printf("\nEnter data for student %d:\n", i + 1);
        printf("Student number: ");
        scanf("%d", &students[i].num);

        printf("Name: ");
        scanf("%s", students[i].name);

        for (int j = 0; j < SUBJECTS; j++) {
            printf("Score %d: ", j + 1);
            scanf("%f", &students[i].score[j]);
        }
    }
}

void print(struct Student students[]) {
    printf("\n%-10s %-15s %-10s %-10s %-10s\n", "Number", "Name", "Score1", "Score2", "Score3");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < STUDENTS; i++) {
        printf("%-10d %-15s %-10.2f %-10.2f %-10.2f\n",
            	students[i].num,
            	students[i].name,
            	students[i].score[0],
            	students[i].score[1],
            	students[i].score[2]);
    }
}
