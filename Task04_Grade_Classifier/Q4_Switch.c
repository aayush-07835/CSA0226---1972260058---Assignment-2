/*
 * Course: CSA02 - C Programming (Assignment 2 - CO2)
 * Task 4: University Grade Classifier using switch on (marks / 10)
 * Standard: C11
 */

#include <stdio.h>

/* Grade rules: 90-100 S, 80-89 A, 70-79 B, 60-69 C, 50-59 D, below 50 F, invalid '?' */
char grade(int marks)
{
    if (marks < 0 || marks > 100) return '?';
    // TODO 1: Use a switch on marks / 10 to return the grade letter (combine cases
    //   where possible)
    switch (marks / 10) {
        case 10:
        case 9:
            return 'S';
        case 8:
            return 'A';
        case 7:
            return 'B';
        case 6:
            return 'C';
        case 5:
            return 'D';
        default:
            return 'F';
    }
}

/* Demonstration of fall-through bug if 'return'/'break' is omitted for case 8 */
char grade_missing_break_demo(int marks)
{
    if (marks < 0 || marks > 100) return '?';
    char g = 'F';
    switch (marks / 10) {
        case 10:
        case 9:
            g = 'S';
            break;
        case 8:
            g = 'A';
            /* INTENTIONAL BUG: missing break causes fall-through into case 7! */
            /* fall through */
        case 7:
            g = 'B';
            break;
        case 6:
            g = 'C';
            break;
        case 5:
            g = 'D';
            break;
        default:
            g = 'F';
            break;
    }
    return g;
}

int main(void)
{
    int marks[] = {100, 95, 83, 50, 49, -5};
    for (int i = 0; i < 6; i++) printf("%d:%c ", marks[i], grade(marks[i]));
    printf("\n");

    /* Full boundary test suite */
    int boundaries[] = {101, 100, 90, 89, 80, 79, 70, 69, 60, 59, 50, 49, 0, -1};
    int n = (int)(sizeof(boundaries) / sizeof(boundaries[0]));
    printf("\nBoundary Test Suite (Switch):\n");
    for (int i = 0; i < n; i++) {
        printf("  marks = %4d -> grade = %c\n", boundaries[i], grade(boundaries[i]));
    }

    printf("\nMissing-Break Fall-Through Demonstration (marks = 83):\n");
    printf("  Normal switch(83)        = %c\n", grade(83));
    printf("  Missing break switch(83) = %c (falls through from case 8 to case 7)\n",
           grade_missing_break_demo(83));

    return 0;
}
