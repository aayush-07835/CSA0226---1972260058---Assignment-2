/*
 * Course: CSA02 - C Programming (Assignment 2 - CO2)
 * Task 5: Alternative Concept - Sieve of Eratosthenes up to N = 1,000,003
 * Standard: C11
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000003UL

int main(void) {
    unsigned char *is_prime = (unsigned char *)malloc((MAX_N + 1) * sizeof(unsigned char));
    if (is_prime == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    for (unsigned long i = 0; i <= MAX_N; i++) {
        is_prime[i] = 1;
    }
    is_prime[0] = 0;
    is_prime[1] = 0;

    unsigned long composite_markings = 0;
    for (unsigned long p = 2; p <= MAX_N / p; p++) {
        if (is_prime[p]) {
            for (unsigned long multiple = p * p; multiple <= MAX_N; multiple += p) {
                is_prime[multiple] = 0;
                composite_markings++;
            }
        }
    }

    unsigned long tickets[] = {0, 1, 2, 3, 97, 100, 7919, 1000003};
    int count = (int)(sizeof(tickets) / sizeof(tickets[0]));

    printf("=========================================================================\n");
    printf("TASK 5: SIEVE OF ERATOSTHENES ALTERNATIVE (N = %lu)\n", MAX_N);
    printf("=========================================================================\n");
    printf("Preprocessing composite markings : %lu\n", composite_markings);
    printf("Auxiliary memory allocated       : %lu bytes (~%.2f KB)\n\n",
           (MAX_N + 1) * sizeof(unsigned char), (double)(MAX_N + 1) / 1024.0);

    for (int k = 0; k < count; k++) {
        unsigned long t = tickets[k];
        printf("%8lu  %-9s  query_divisions = 0 (O(1) array lookup)\n",
               t, is_prime[t] ? "prime" : "not prime");
    }

    free(is_prime);
    return 0;
}
