/*
 * Course: CSA02 - C Programming (Assignment 2 - CO2)
 * Task 4: University Grade Classifier using else-if Ladder
 * Standard: C11
 */

#include <stdio.h>

char grade_else_if(int marks) {
    if (marks < 0 || marks > 100) {
        return '?';
    } else if (marks >= 90) {
        return 'S';
    } else if (marks >= 80) {
        return 'A';
    } else if (marks >= 70) {
        return 'B';
    } else if (marks >= 60) {
        return 'C';
    } else if (marks >= 50) {
        return 'D';
    } else {
        return 'F';
    }
}

int main(void) {
    int boundaries[] = {101, 100, 90, 89, 80, 79, 70, 69, 60, 59, 50, 49, 0, -1};
    int n = (int)(sizeof(boundaries) / sizeof(boundaries[0]));

    printf("=========================================================================\n");
    printf("TASK 4: ELSE-IF LADDER GRADE CLASSIFIER BOUNDARY VERIFICATION\n");
    printf("=========================================================================\n");
    for (int i = 0; i < n; i++) {
        printf("  marks = %4d -> grade = %c\n", boundaries[i], grade_else_if(boundaries[i]));
    }
    return 0;
}
