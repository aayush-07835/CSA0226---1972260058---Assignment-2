/*
 * Course: CSA02 - C Programming (Assignment 2 - CO2)
 * Task 2: Alternative Concept 1 - Nested If Statements
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

int check_concession_nested_if(const Passenger *p) {
    if (p->is_senior) {
        if (p->is_eligible_class) {
            return 1; /* Granted via senior + eligible class; slow check skipped */
        } else {
            return verify_disability_card(p);
        }
    } else {
        return verify_disability_card(p);
    }
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

    g_verify_calls = 0;
    int granted = 0;
    for (int i = 0; i < NUM_PASSENGERS; i++) {
        if (check_concession_nested_if(&passengers[i])) {
            granted++;
        }
    }

    printf("=========================================================================\n");
    printf("TASK 2: NESTED-IF ALTERNATIVE (EQUIVALENT TO SHORT-CIRCUIT ORDER 1)\n");
    printf("=========================================================================\n");
    printf("Total Passengers    : %d\n", NUM_PASSENGERS);
    printf("Concessions Granted : %d\n", granted);
    printf("Slow Verify Calls   : %ld (Matches short-circuit Order 1 exactly)\n", g_verify_calls);

    return 0;
}
