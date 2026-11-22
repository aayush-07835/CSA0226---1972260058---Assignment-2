/*
 * Course: CSA02 - C Programming (Assignment 2 - CO2)
 * Task 2: Alternative Concept 2 - Non-Short-Circuit Bitwise & and | Comparison
 * Standard: C11
 */

#include <stdio.h>

#define NUM_PASSENGERS 1000

typedef struct {
    int id;
    int is_senior;
    int is_eligible_class;
    int has_disability;
} Passenger;

static long g_verify_calls = 0;

static unsigned int lcg_next(unsigned int *state) {
    *state = (*state * 1664525u) + 1013904223u;
    return *state;
}

int verify_disability_card(const Passenger *p) {
    g_verify_calls++;
    return p->has_disability;
}

int main(void) {
    Passenger passengers[NUM_PASSENGERS];
    unsigned int seed = 42u;
    for (int i = 0; i < NUM_PASSENGERS; i++) {
        passengers[i].id = 1001 + i;
        passengers[i].is_senior         = ((lcg_next(&seed) % 100u) < 30u) ? 1 : 0;
        passengers[i].is_eligible_class = ((lcg_next(&seed) % 100u) < 40u) ? 1 : 0;
        passengers[i].has_disability    = ((lcg_next(&seed) % 100u) < 15u) ? 1 : 0;
    }

    /* Non-short-circuit evaluation using bitwise & and | on 0/1 flags */
    g_verify_calls = 0;
    int granted = 0;
    for (int i = 0; i < NUM_PASSENGERS; i++) {
        if ((passengers[i].is_senior & passengers[i].is_eligible_class) |
            verify_disability_card(&passengers[i])) {
            granted++;
        }
    }

    printf("=========================================================================\n");
    printf("TASK 2: NON-SHORT-CIRCUIT BITWISE (& and |) COMPARISON\n");
    printf("=========================================================================\n");
    printf("Total Passengers    : %d\n", NUM_PASSENGERS);
    printf("Concessions Granted : %d\n", granted);
    printf("Slow Verify Calls   : %ld (100%% of passengers evaluated; NO short-circuit)\n\n", g_verify_calls);

    /* Pitfall demonstration: non-normalized truthy integers with & vs && */
    int flag_a = 2; /* Non-zero (true in C logical context), binary 0010 */
    int flag_b = 4; /* Non-zero (true in C logical context), binary 0100 */
    printf("Bitwise '&' vs Logical '&&' Truthiness Pitfall:\n");
    printf("  flag_a = %d (true), flag_b = %d (true)\n", flag_a, flag_b);
    printf("  flag_a && flag_b = %d (Correct logical AND)\n", (flag_a && flag_b));
    printf("  flag_a &  flag_b = %d (WRONG! Disjoint bits produce 0 / false)\n", (flag_a & flag_b));

    return 0;
}
