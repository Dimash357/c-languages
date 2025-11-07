#include <stdio.h>
#include <math.h>

#define STUDENTS 10
#define COURSES 5

void inputGrades(float grades[STUDENTS][COURSES]) {
    printf("Enter grades for %d students and %d courses:\n", STUDENTS, COURSES);
    for (int i = 0; i < STUDENTS; i++) {
        for (int j = 0; j < COURSES; j++) {
            printf("Student %d, Course %d: ", i + 1, j + 1);
            scanf("%f", &grades[i][j]);
        }
    }
}

void studentAvg(float g[STUDENTS][COURSES], float a[STUDENTS]){
    for(int i=0;i<STUDENTS;i++){
        float sum=0;
        for(int j=0;j<COURSES;j++) sum+=g[i][j];
        a[i]=sum/COURSES;
    }
}

void courseAvg(float g[STUDENTS][COURSES], float a[COURSES]){
    for(int j=0;j<COURSES;j++){
        float sum=0;
        for(int i=0;i<STUDENTS;i++) sum+=g[i][j];
        a[j]=sum/STUDENTS;
    }
}

void highest(float g[STUDENTS][COURSES], int *si, int *ci, float *max){
    *max=g[0][0];
    *si=0; *ci=0;
    for(int i=0;i<STUDENTS;i++)
        for(int j=0;j<COURSES;j++)
            if(g[i][j]>*max){
                *max=g[i][j];
                *si=i; *ci=j;
            }
}

float variance(float a[STUDENTS]){
    float mean=0,var=0;
    for(int i=0;i<STUDENTS;i++) mean+=a[i];
    mean/=STUDENTS;
    for(int i=0;i<STUDENTS;i++) var+=(a[i]-mean)*(a[i]-mean);
    return var/STUDENTS;
}

int main(){
    float grades[STUDENTS][COURSES], sAvg[STUDENTS], cAvg[COURSES];
    int topS, topC;
    float maxScore;

    inputGrades(grades);
    studentAvg(grades, sAvg);
    courseAvg(grades, cAvg);
    highest(grades, &topS, &topC, &maxScore);

    printf("Student averages:\n");
    for(int i=0;i<STUDENTS;i++) printf("Student %d: %.2f\n", i+1, sAvg[i]);

    printf("Course averages:\n");
    for(int j=0;j<COURSES;j++) printf("Course %d: %.2f\n", j+1, cAvg[j]);

    printf("Highest score: %.2f (Student %d, Course %d)\n", maxScore, topS+1, topC+1);
    printf("Variance of student averages: %.2f\n", variance(sAvg));

    return 0;
}
