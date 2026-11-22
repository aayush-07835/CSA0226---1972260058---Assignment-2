/*
 * Course: CSA02 - C Programming (Assignment 2 - CO2)
 * Task 2: Short-Circuit Evaluation in Railway Senior-Citizen Concession
 * Standard: C11
 */

#include <stdio.h>
#include <stdlib.h>

#define NUM_PASSENGERS 1000

typedef struct {
    int id;
    int is_senior;          /* 1 if age >= 60, else 0 (30% of sample) */
    int is_eligible_class;  /* 1 if Sleeper/3AC eligible class, else 0 (40% of sample) */
    int has_disability;     /* 1 if valid disability card, else 0 (15% of sample) */
} Passenger;

static long g_verify_calls = 0;
static long g_audit_entries = 0;

/* Deterministic LCG pseudo-random generator (Fixed Seed = 42) */
static unsigned int lcg_next(unsigned int *state) {
    *state = (*state * 1664525u) + 1013904223u;
    return *state;
}

/* Slow server verification function that counts calls and optionally logs audit events */
int verify_disability_card(const Passenger *p, int audit_mode) {
    g_verify_calls++;
    if (audit_mode) {
        g_audit_entries++;
    }
    /* Simulated deterministic server verification work */
    volatile int checksum = 0;
    for (int k = 1; k <= 50; k++) {
        checksum += (p->id * k) % 17;
    }
    (void)checksum;
    return p->has_disability;
}

void generate_passengers(Passenger list[], int n) {
    unsigned int seed = 42u;
    for (int i = 0; i < n; i++) {
        list[i].id = 1001 + i;
        list[i].is_senior         = ((lcg_next(&seed) % 100u) < 30u) ? 1 : 0;
        list[i].is_eligible_class = ((lcg_next(&seed) % 100u) < 40u) ? 1 : 0;
        list[i].has_disability    = ((lcg_next(&seed) % 100u) < 15u) ? 1 : 0;
    }
}

int main(void) {
    Passenger passengers[NUM_PASSENGERS];
    generate_passengers(passengers, NUM_PASSENGERS);

    /* Export deterministic passenger dataset to CSV */
    FILE *fp_data = fopen("passenger_data.csv", "w");
    if (fp_data != NULL) {
        fprintf(fp_data, "passenger_id,is_senior,is_eligible_class,has_disability\n");
        for (int i = 0; i < NUM_PASSENGERS; i++) {
            fprintf(fp_data, "%d,%d,%d,%d\n",
                    passengers[i].id,
                    passengers[i].is_senior,
                    passengers[i].is_eligible_class,
                    passengers[i].has_disability);
        }
        fclose(fp_data);
    }

    /* Count distribution */
    int senior_cnt = 0, class_cnt = 0, both_sc_cnt = 0, disab_cnt = 0;
    for (int i = 0; i < NUM_PASSENGERS; i++) {
        if (passengers[i].is_senior) senior_cnt++;
        if (passengers[i].is_eligible_class) class_cnt++;
        if (passengers[i].is_senior && passengers[i].is_eligible_class) both_sc_cnt++;
        if (passengers[i].has_disability) disab_cnt++;
    }

    printf("=========================================================================\n");
    printf("TASK 2: SHORT-CIRCUIT EVALUATION EXPERIMENT (N = %d, SEED = 42)\n", NUM_PASSENGERS);
    printf("=========================================================================\n");
    printf("Sample Distribution:\n");
    printf("  Senior Citizens (30%% target)       : %d\n", senior_cnt);
    printf("  Eligible Ticket Class (40%% target) : %d\n", class_cnt);
    printf("  Both Senior & Eligible Class       : %d (Short-circuits '||' RHS)\n", both_sc_cnt);
    printf("  Disability Card Holders (15%%)      : %d\n\n", disab_cnt);

    /* Order 1: (is_senior && is_eligible_class) || verify_disability_card */
    g_verify_calls = 0;
    int granted_1 = 0;
    for (int i = 0; i < NUM_PASSENGERS; i++) {
        if ((passengers[i].is_senior && passengers[i].is_eligible_class) ||
            verify_disability_card(&passengers[i], 0)) {
            granted_1++;
        }
    }
    long calls_order1 = g_verify_calls;

    /* Order 2: (is_eligible_class && is_senior) || verify_disability_card */
    g_verify_calls = 0;
    int granted_2 = 0;
    for (int i = 0; i < NUM_PASSENGERS; i++) {
        if ((passengers[i].is_eligible_class && passengers[i].is_senior) ||
            verify_disability_card(&passengers[i], 0)) {
            granted_2++;
        }
    }
    long calls_order2 = g_verify_calls;

    /* Order 3: verify_disability_card || (is_senior && is_eligible_class) */
    g_verify_calls = 0;
    int granted_3 = 0;
    for (int i = 0; i < NUM_PASSENGERS; i++) {
        if (verify_disability_card(&passengers[i], 0) ||
            (passengers[i].is_senior && passengers[i].is_eligible_class)) {
            granted_3++;
        }
    }
    long calls_order3 = g_verify_calls;

    /* Order 4 (Changed Condition - Audit Logging): verify_disability_card placed FIRST */
    g_verify_calls = 0;
    g_audit_entries = 0;
    int granted_4 = 0;
    for (int i = 0; i < NUM_PASSENGERS; i++) {
        if (verify_disability_card(&passengers[i], 1) ||
            (passengers[i].is_senior && passengers[i].is_eligible_class)) {
            granted_4++;
        }
    }
    long calls_audit_first = g_verify_calls;
    long audit_logged_first = g_audit_entries;

    /* Order 5 (Broken Audit Logging if placed SECOND) */
    g_verify_calls = 0;
    g_audit_entries = 0;
    for (int i = 0; i < NUM_PASSENGERS; i++) {
        if ((passengers[i].is_senior && passengers[i].is_eligible_class) ||
            verify_disability_card(&passengers[i], 1)) {
            /* concession granted */
        }
    }
    long audit_logged_second = g_audit_entries;

    printf("Condition Ordering Results:\n");
    printf("  1. (senior && class) || verify() : Concessions = %d | Slow Calls = %ld\n",
           granted_1, calls_order1);
    printf("  2. (class && senior) || verify() : Concessions = %d | Slow Calls = %ld\n",
           granted_2, calls_order2);
    printf("  3. verify() || (senior && class) : Concessions = %d | Slow Calls = %ld\n",
           granted_3, calls_order3);
    printf("\nChanged Condition (Audit Log Side Effect):\n");
    printf("  - When verify() is SECOND: Audit entries = %ld / %d (INCOMPLETE AUDIT!)\n",
           audit_logged_second, NUM_PASSENGERS);
    printf("  - When verify() is FIRST : Audit entries = %ld / %d (COMPLETE AUDIT, Calls = %ld, Granted = %d)\n",
           audit_logged_first, NUM_PASSENGERS, calls_audit_first, granted_4);

    FILE *fp_counts = fopen("call_counts.csv", "w");
    if (fp_counts != NULL) {
        fprintf(fp_counts, "strategy,expression,total_passengers,concessions_granted,slow_verify_calls,audit_entries_recorded\n");
        fprintf(fp_counts, "Order_1_Cheap_First,(is_senior && is_eligible_class) || verify(),%d,%d,%ld,%ld\n",
                NUM_PASSENGERS, granted_1, calls_order1, audit_logged_second);
        fprintf(fp_counts, "Order_2_Class_First,(is_eligible_class && is_senior) || verify(),%d,%d,%ld,%ld\n",
                NUM_PASSENGERS, granted_2, calls_order2, audit_logged_second);
        fprintf(fp_counts, "Order_3_Slow_First,verify() || (is_senior && is_eligible_class),%d,%d,%ld,%ld\n",
                NUM_PASSENGERS, granted_3, calls_order3, audit_logged_first);
        fclose(fp_counts);
    }

    return 0;
}
