/*
 * Course: CSA02 - C Programming (Assignment 2 - CO2)
 * Task 5: Optimized Prime Checking using a do-while Loop (with n = 2, 3 Guards)
 * Standard: C11
 */

#include <stdio.h>

unsigned long checks = 0;

int is_prime_do_while(unsigned long n) {
    checks = 0;
    if (n < 2) return 0;
    /*
     * Special care for n = 2 and n = 3:
     * A do-while loop executes its body BEFORE checking (i * i <= n).
     * Without guarding n == 2 and n == 3, i = 2 would execute (2 % 2 == 0)
     * and falsely classify 2 as composite!
     */
    if (n == 2 || n == 3) return 1;

    unsigned long i = 2;
    do {
        checks++;
        if (n % i == 0) {
            return 0;
        }
        i++;
    } while (i * i <= n);

    return 1;
}

int main(void) {
    unsigned long tickets[] = {0, 1, 2, 3, 97, 100, 7919, 1000003};
    int count = (int)(sizeof(tickets) / sizeof(tickets[0]));

    printf("=========================================================================\n");
    printf("TASK 5: OPTIMIZED PRIME VERIFICATION (DO-WHILE LOOP WITH EDGE GUARDS)\n");
    printf("=========================================================================\n");
    for (int k = 0; k < count; k++) {
        int p = is_prime_do_while(tickets[k]);
        printf("%8lu  %-9s  divisions = %lu\n", tickets[k],
               p ? "prime" : "not prime", checks);
    }
    return 0;
}
