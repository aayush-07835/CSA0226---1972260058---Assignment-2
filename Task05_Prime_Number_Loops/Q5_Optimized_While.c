/*
 * Course: CSA02 - C Programming (Assignment 2 - CO2)
 * Task 5: Optimized Prime Checking using a while Loop
 * Standard: C11
 */

#include <stdio.h>

unsigned long checks = 0;

int is_prime_while(unsigned long n) {
    checks = 0;
    if (n < 2) return 0;

    unsigned long i = 2;
    while (i * i <= n) {
        checks++;
        if (n % i == 0) {
            return 0;
        }
        i++;
    }
    return 1;
}

int main(void) {
    unsigned long tickets[] = {0, 1, 2, 3, 97, 100, 7919, 1000003};
    int count = (int)(sizeof(tickets) / sizeof(tickets[0]));

    printf("=========================================================================\n");
    printf("TASK 5: OPTIMIZED PRIME VERIFICATION (WHILE LOOP, i * i <= n)\n");
    printf("=========================================================================\n");
    for (int k = 0; k < count; k++) {
        int p = is_prime_while(tickets[k]);
        printf("%8lu  %-9s  divisions = %lu\n", tickets[k],
               p ? "prime" : "not prime", checks);
    }
    return 0;
}
