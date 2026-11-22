/*
 * Course: CSA02 - C Programming (Assignment 2 - CO2)
 * Task 7: Day-4 Design Challenge - Original Brute-Force Implementation
 * Standard: C11
 */

#include <stdio.h>

unsigned long original_checks = 0;

int is_prime_original(unsigned long n) {
    original_checks = 0;
    if (n < 2) return 0;
    for (unsigned long i = 2; i < n; i++) {
        original_checks++;
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    unsigned long inputs[] = {2, 3, 17, 97, 100, 1009, 7919, 104729, 1000003};
    int count = (int)(sizeof(inputs) / sizeof(inputs[0]));

    printf("=========================================================================\n");
    printf("TASK 7: ORIGINAL IMPLEMENTATION (BRUTE-FORCE TRIAL DIVISION 2..n-1)\n");
    printf("=========================================================================\n");
    for (int k = 0; k < count; k++) {
        int res = is_prime_original(inputs[k]);
        printf("%8lu  %-9s  divisions = %lu\n",
               inputs[k], res ? "prime" : "not prime", original_checks);
    }
    return 0;
}
