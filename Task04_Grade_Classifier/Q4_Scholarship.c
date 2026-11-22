/*
 * Course: CSA02 - C Programming (Assignment 2 - CO2)
 * Task 4: Design Decision - Two-Dimensional Lookup Table for Scholarship Rules
 * Standard: C11
 */

#include <stdio.h>

/*
 * Income Bands (Annual Family Income in INR Lakhs):
 *   Band 0: <= 2.50 Lakhs (EWS / Low Income)
 *   Band 1: > 2.50 to 5.00 Lakhs (Lower-Middle Income)
 *   Band 2: > 5.00 to 8.00 Lakhs (Middle Income)
 *   Band 3: > 8.00 Lakhs (General / High Income)
 *
 * Grade Index: 0->S, 1->A, 2->B, 3->C, 4->D, 5->F
 */

int get_grade_index(char g) {
    switch (g) {
        case 'S': return 0;
        case 'A': return 1;
        case 'B': return 2;
        case 'C': return 3;
        case 'D': return 4;
        case 'F': return 5;
        default:  return -1;
    }
}

int get_income_band(double income_lakhs) {
    if (income_lakhs < 0.0)   return -1;
    if (income_lakhs <= 2.5)  return 0;
    if (income_lakhs <= 5.0)  return 1;
    if (income_lakhs <= 8.0)  return 2;
    return 3;
}

const char *classify_scholarship(char grade_char, double income_lakhs) {
    static const char *SCHOLARSHIP_MATRIX[6][4] = {
        /* Grade S */ {"100% Merit-cum-Means", "100% Merit-cum-Means", "75% Merit Scholarship", "50% Chancellor Merit"},
        /* Grade A */ {"100% Merit-cum-Means", "75% Merit-cum-Means",  "50% Merit Scholarship", "25% Academic Merit"},
        /* Grade B */ {"75% Means Support",     "50% Means Support",    "25% Fee Concession",    "No Scholarship"},
        /* Grade C */ {"50% Means Support",     "25% Means Support",    "No Scholarship",        "No Scholarship"},
        /* Grade D */ {"25% Hardship Grant",    "No Scholarship",       "No Scholarship",        "No Scholarship"},
        /* Grade F */ {"Ineligible (Failed)",   "Ineligible (Failed)",  "Ineligible (Failed)",   "Ineligible (Failed)"}
    };

    int g_idx = get_grade_index(grade_char);
    int i_idx = get_income_band(income_lakhs);

    if (g_idx < 0 || i_idx < 0) {
        return "Invalid Input";
    }
    return SCHOLARSHIP_MATRIX[g_idx][i_idx];
}

int main(void) {
    struct {
        int marks;
        char grade;
        double income;
    } students[] = {
        {96, 'S', 1.8},
        {92, 'S', 9.5},
        {84, 'A', 4.2},
        {75, 'B', 2.0},
        {63, 'C', 6.5},
        {54, 'D', 2.2},
        {42, 'F', 1.5}
    };

    int n = (int)(sizeof(students) / sizeof(students[0]));
    printf("=========================================================================\n");
    printf("TASK 4: SCHOLARSHIP CLASSIFIER (2D DECISION LOOKUP TABLE)\n");
    printf("=========================================================================\n");
    for (int i = 0; i < n; i++) {
        printf("  Marks: %3d | Grade: %c | Income: Rs %4.2f L -> %s\n",
               students[i].marks, students[i].grade, students[i].income,
               classify_scholarship(students[i].grade, students[i].income));
    }
    return 0;
}
