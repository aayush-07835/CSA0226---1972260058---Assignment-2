/*
 * Course: CSA02 - C Programming (Assignment 2 - CO2)
 * Task 6: Alternative Concept - Closed-Form Logarithmic Annuity Formula
 * Formula: n = -log(1 - r * P / E) / log(1 + r)
 * Standard: C11 (Compile with -lm)
 */

#include <stdio.h>
#include <math.h>

int main(void) {
    double P = 10000.0;
    double r = 0.02;
    double test_emis[] = {2000.0, 1000.0, 500.0, 300.0, 250.0, 220.0, 205.0, 200.0, 180.0};
    int n_tests = (int)(sizeof(test_emis) / sizeof(test_emis[0]));

    printf("=========================================================================\n");
    printf("TASK 6: CLOSED-FORM FORMULA ALTERNATIVE: n = -log(1 - r*P/E) / log(1 + r)\n");
    printf("=========================================================================\n");
    printf("Monthly EMI | Exact Real n | Ceil(n) Months | Formula Total Interest | Domain Status\n");
    printf("------------+--------------+----------------+------------------------+--------------\n");

    for (int i = 0; i < n_tests; i++) {
        double E = test_emis[i];
        double ratio = (r * P) / E;
        if (ratio >= 1.0) {
            printf("Rs %8.2f |    UNDEFINED |            N/A |                    N/A | Invalid (E <= r*P)\n", E);
        } else {
            double n_real = -log(1.0 - ratio) / log(1.0 + r);
            int n_months = (int)ceil(n_real - 1e-12);
            /* Exact total interest under equal installments over n_real periods */
            double approx_interest = (n_real * E) - P;
            printf("Rs %8.2f | %12.6f | %14d | Rs %19.2f | Valid\n",
                   E, n_real, n_months, approx_interest);
        }
    }

    return 0;
}
