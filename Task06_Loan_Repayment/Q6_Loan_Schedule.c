/*
 * Course: CSA02 - C Programming (Assignment 2 - CO2)
 * Task 6: Loops That Must Terminate - Self-Help Group Micro-Loan Repayment
 * Standard: C11
 */

#include <stdio.h>

#define MAX_MONTHS 360
#define EPSILON    1e-6

typedef struct {
    int months;
    double total_interest;
    double total_paid;
    double final_balance;
    int hit_safety_limit;
    int non_amortizing;
} LoanResult;

LoanResult simulate_loan(double principal, double monthly_rate, double fixed_repayment,
                         int print_schedule, FILE *csv_out) {
    LoanResult res = {0, 0.0, 0.0, principal, 0, 0};
    double balance = principal;

    if (print_schedule) {
        printf("Month | Opening Bal | Interest   | Repayment  | Closing Bal\n");
        printf("------+-------------+------------+------------+------------\n");
    }
    if (csv_out != NULL) {
        fprintf(csv_out, "month,opening_balance,interest,repayment,closing_balance\n");
    }

    /* Check upfront if repayment cannot even cover the first month's interest */
    double first_interest = balance * monthly_rate;
    if (fixed_repayment <= first_interest + EPSILON) {
        res.non_amortizing = 1;
    }

    while (balance > EPSILON) {
        if (res.months >= MAX_MONTHS) {
            res.hit_safety_limit = 1;
            break;
        }

        res.months++;
        double opening = balance;
        double interest = opening * monthly_rate;
        double due = opening + interest;
        double payment = fixed_repayment;

        /* Final month cap: never overpay beyond remaining balance + interest */
        if (payment >= due - EPSILON) {
            payment = due;
            balance = 0.0;
        } else {
            balance = due - payment;
        }

        res.total_interest += interest;
        res.total_paid += payment;

        if (print_schedule) {
            printf("%5d | %11.2f | %10.2f | %10.2f | %11.2f\n",
                   res.months, opening, interest, payment, balance);
        }
        if (csv_out != NULL) {
            fprintf(csv_out, "%d,%.4f,%.4f,%.4f,%.4f\n",
                    res.months, opening, interest, payment, balance);
        }
    }

    res.final_balance = balance;
    return res;
}

int main(void) {
    double principal = 10000.0;
    double rate = 0.02; /* 2% per month */
    double repayment = 2000.0;

    printf("=========================================================================\n");
    printf("TASK 6: SELF-HELP GROUP MICRO-LOAN REPAYMENT SCHEDULE\n");
    printf("Principal = Rs %.2f | Monthly Interest = %.2f%% | EMI = Rs %.2f\n",
           principal, rate * 100.0, repayment);
    printf("=========================================================================\n\n");

    FILE *fp_sched = fopen("loan_schedule.csv", "w");
    LoanResult base = simulate_loan(principal, rate, repayment, 1, fp_sched);
    if (fp_sched != NULL) fclose(fp_sched);

    printf("\nSummary (Base Case):\n");
    printf("  Total Months   : %d\n", base.months);
    printf("  Total Interest : Rs %.2f\n", base.total_interest);
    printf("  Total Repaid   : Rs %.2f\n", base.total_paid);

    /* Growth Investigation: vary repayment as it approaches monthly interest (Rs 200) */
    double test_emis[] = {2000.0, 1000.0, 500.0, 300.0, 250.0, 220.0, 205.0, 200.0, 180.0};
    int n_tests = (int)(sizeof(test_emis) / sizeof(test_emis[0]));

    printf("\n=========================================================================\n");
    printf("GROWTH INVESTIGATION: ITERATIONS AS REPAYMENT APPROACHES INTEREST (Rs 200)\n");
    printf("=========================================================================\n");
    printf("Monthly EMI | Months | Total Interest | Status\n");
    printf("------------+--------+----------------+----------------------------------\n");

    FILE *fp_iter = fopen("iteration_analysis.csv", "w");
    if (fp_iter != NULL) {
        fprintf(fp_iter, "monthly_repayment,months,total_interest,closing_balance,status\n");
    }

    for (int i = 0; i < n_tests; i++) {
        double emi = test_emis[i];
        LoanResult r = simulate_loan(principal, rate, emi, 0, NULL);
        const char *status = "Repaid Normally";
        if (r.non_amortizing && emi < principal * rate) {
            status = "DIVERGES (EMI < Interest; Safety Break at 360)";
        } else if (r.non_amortizing) {
            status = "STAGNANT (EMI == Interest; Safety Break at 360)";
        } else if (r.hit_safety_limit) {
            status = "SAFETY LIMIT REACHED (360 Months Break)";
        }

        printf("Rs %8.2f | %6d | Rs %11.2f | %s\n",
               emi, r.months, r.total_interest, status);

        if (fp_iter != NULL) {
            fprintf(fp_iter, "%.2f,%d,%.2f,%.2f,\"%s\"\n",
                    emi, r.months, r.total_interest, r.final_balance, status);
        }
    }

    if (fp_iter != NULL) fclose(fp_iter);
    return 0;
}
