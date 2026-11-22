/*
 * Course: CSA02 - C Programming (Assignment 2 - CO2)
 * Task 4: Alternative Concept - O(1) Lookup Table Grade Classifier
 * Standard: C11
 */

#include <stdio.h>

char grade_lookup(int marks) {
    static const char grades[11] = {
        'F', 'F', 'F', 'F', 'F', 'D', 'C', 'B', 'A', 'S', 'S'
    };

    if (marks < 0 || marks > 100) {
        return '?';
    }
    return grades[marks / 10];
}

int main(void) {
    int boundaries[] = {101, 100, 90, 89, 80, 79, 70, 69, 60, 59, 50, 49, 0, -1};
    int n = (int)(sizeof(boundaries) / sizeof(boundaries[0]));

    printf("=========================================================================\n");
    printf("TASK 4: O(1) LOOKUP TABLE GRADE CLASSIFIER\n");
    printf("=========================================================================\n");
    for (int i = 0; i < n; i++) {
        printf("  marks = %4d -> grade = %c\n", boundaries[i], grade_lookup(boundaries[i]));
    }
    printf("\nTable Memory Footprint: %zu bytes (static const char grades[11])\n",
           11 * sizeof(char));
    return 0;
}
