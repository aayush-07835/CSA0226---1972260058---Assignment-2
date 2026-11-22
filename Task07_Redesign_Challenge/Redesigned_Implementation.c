/*
 * Course: CSA02 - C Programming (Assignment 2 - CO2)
 * Task 7: Day-4 Design Challenge - Redesigned Odd-Only Sqrt-Bounded Prime Checker
 * Exploits:
 *   1. Even-number elimination (only 2 is an even prime; all other even numbers fail in 1 check).
 *   2. Composite factor symmetry (smallest non-trivial factor <= sqrt(n)).
 *   3. Odd-only stepping (i += 2), halving checks relative to standard sqrt(n).
 *   4. Overflow-safe loop bound (i <= n / i instead of i * i <= n).
 * Standard: C11
 */

#include <stdio.h>

unsigned long redesigned_checks = 0;

int is_prime_redesigned(unsigned long n) {
    redesigned_checks = 0;
    if (n < 2) return 0;
    if (n == 2) return 1;

    /* Single check for all even numbers > 2 */
    redesigned_checks++;
    if (n % 2 == 0) return 0;

    /* Test only odd divisors up to sqrt(n) without multiplication overflow */
    for (unsigned long i = 3; i <= n / i; i += 2) {
        redesigned_checks++;
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
    printf("TASK 7: REDESIGNED IMPLEMENTATION (EVEN-FILTER + ODD-ONLY SQRT BOUND)\n");
    printf("=========================================================================\n");
    for (int k = 0; k < count; k++) {
        int res = is_prime_redesigned(inputs[k]);
        printf("%8lu  %-9s  divisions = %lu\n",
               inputs[k], res ? "prime" : "not prime", redesigned_checks);
    }
    return 0;
}
