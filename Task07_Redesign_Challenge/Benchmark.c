/*
 * Course: CSA02 - C Programming (Assignment 2 - CO2)
 * Task 7: Day-4 Design Challenge - Comparative Benchmark (Original vs Redesigned)
 * Standard: C11
 */

#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <time.h>

static unsigned long g_orig_checks = 0;
static unsigned long g_red_checks  = 0;

int is_prime_original(unsigned long n) {
    g_orig_checks = 0;
    if (n < 2) return 0;
    for (unsigned long i = 2; i < n; i++) {
        g_orig_checks++;
        if (n % i == 0) return 0;
    }
    return 1;
}

int is_prime_redesigned(unsigned long n) {
    g_red_checks = 0;
    if (n < 2) return 0;
    if (n == 2) return 1;
    g_red_checks++;
    if (n % 2 == 0) return 0;
    for (unsigned long i = 3; i <= n / i; i += 2) {
        g_red_checks++;
        if (n % i == 0) return 0;
    }
    return 1;
}

static double elapsed_ms(struct timespec start, struct timespec end) {
    return (double)(end.tv_sec - start.tv_sec) * 1000.0 +
           (double)(end.tv_nsec - start.tv_nsec) / 1e6;
}

int main(void) {
    unsigned long inputs[] = {2, 3, 17, 97, 100, 1009, 7919, 104729, 1000003};
    int count = (int)(sizeof(inputs) / sizeof(inputs[0]));

    FILE *fp = fopen("comparison.csv", "w");
    if (fp != NULL) {
        fprintf(fp, "input_n,is_prime,original_divisions,redesigned_divisions,divisions_saved,reduction_percent,speedup_factor\n");
    }

    printf("========================================================================================\n");
    printf("TASK 7: BENCHMARK COMPARISON (ORIGINAL BRUTE-FORCE vs REDESIGNED ODD-SQRT)\n");
    printf("========================================================================================\n");
    printf("   Input n | Status    | Orig Divs | Redesigned Divs | Saved     | Reduction | Speedup\n");
    printf("-----------+-----------+-----------+-----------------+-----------+-----------+--------\n");

    for (int k = 0; k < count; k++) {
        unsigned long n = inputs[k];
        int p1 = is_prime_original(n);
        unsigned long d1 = g_orig_checks;

        int p2 = is_prime_redesigned(n);
        unsigned long d2 = g_red_checks;

        if (p1 != p2) {
            fprintf(stderr, "MISMATCH on %lu!\n", n);
            return 1;
        }

        long saved = (long)d1 - (long)d2;
        double red_pct = (d1 > 0) ? (100.0 * (double)saved / (double)d1) : 0.0;
        double speedup = (d2 > 0) ? ((double)d1 / (double)d2) : 1.0;

        printf("%10lu | %-9s | %9lu | %15lu | %9ld | %8.2f%% | %6.2fx\n",
               n, p1 ? "prime" : "not prime", d1, d2, saved, red_pct, speedup);

        if (fp != NULL) {
            fprintf(fp, "%lu,%d,%lu,%lu,%ld,%.4f,%.2f\n",
                    n, p1, d1, d2, saved, red_pct, speedup);
        }
    }

    if (fp != NULL) fclose(fp);

    /* Batch workload benchmark: all integers from 2 to 25,000 */
    const unsigned long BATCH_MAX = 25000UL;
    unsigned long total_orig_divs = 0;
    unsigned long total_red_divs  = 0;
    int primes_orig = 0, primes_red = 0;
    struct timespec t0, t1, t2, t3;

    clock_gettime(CLOCK_MONOTONIC, &t0);
    for (unsigned long n = 2; n <= BATCH_MAX; n++) {
        primes_orig += is_prime_original(n);
        total_orig_divs += g_orig_checks;
    }
    clock_gettime(CLOCK_MONOTONIC, &t1);

    clock_gettime(CLOCK_MONOTONIC, &t2);
    for (unsigned long n = 2; n <= BATCH_MAX; n++) {
        primes_red += is_prime_redesigned(n);
        total_red_divs += g_red_checks;
    }
    clock_gettime(CLOCK_MONOTONIC, &t3);

    double ms_orig = elapsed_ms(t0, t1);
    double ms_red  = elapsed_ms(t2, t3);

    printf("\nBatch Workload Benchmark (All integers 2..%lu, Primes found = %d == %d):\n",
           BATCH_MAX, primes_orig, primes_red);
    printf("  Original Total Divisions   : %lu (Time: %.3f ms)\n", total_orig_divs, ms_orig);
    printf("  Redesigned Total Divisions : %lu (Time: %.3f ms)\n", total_red_divs, ms_red);
    printf("  Total Operation Reduction  : %.4f%%\n",
           100.0 * (double)(total_orig_divs - total_red_divs) / (double)total_orig_divs);

    return 0;
}
