/*
 * Course: CSA02 - C Programming (Assignment 2 - CO2)
 * Task 1: Precedence, Associativity and the Discount Bug (Original Buggy Model)
 * Context: Jan Aushadhi Pharmacy Billing
 * Standard: C11
 */

#include <stdio.h>

typedef struct {
    const char *label;
    int price;
    int qty;
    int senior;
} BillCase;

int main(void) {
    BillCase cases[3] = {
        {"Case 1 (Standard Senior Bill)", 250, 3, 1},
        {"Case 2 (Fractional Rupee Loss)", 45,  3, 1},
        {"Case 3 (Threshold Boundary)",   350, 3, 1}
    };

    printf("=========================================================================\n");
    printf("TASK 1: ORIGINAL JAN AUSHADHI BILLING EXPRESSION (INTEGER ARITHMETIC)\n");
    printf("=========================================================================\n\n");

    for (int i = 0; i < 3; i++) {
        int price = cases[i].price;
        int qty = cases[i].qty;
        int senior = cases[i].senior;

        /* Original unparenthesized integer expression from problem statement */
        int total = price * qty - price * qty * 15 / 100 * senior + price * qty * 5 / 100;
        int net   = total > 1000 ? total - 50 : total;

        /* Exact floating-point reference where 5% GST applies on discounted value */
        double gross_exact    = (double)price * qty;
        double disc_exact     = senior ? gross_exact * 0.15 : 0.0;
        double taxable_exact  = gross_exact - disc_exact;
        double gst_exact      = taxable_exact * 0.05;
        double total_intended = taxable_exact + gst_exact;
        double net_intended   = (total_intended > 1000.0) ? (total_intended - 50.0) : total_intended;

        printf("%s\n", cases[i].label);
        printf("  Inputs         : price = Rs %d, qty = %d, senior = %d\n", price, qty, senior);
        printf("  Original total : Rs %d\n", total);
        printf("  Original net   : Rs %d\n", net);
        printf("  Intended total : Rs %.2f (GST on discounted taxable amount)\n", total_intended);
        printf("  Intended net   : Rs %.2f\n", net_intended);
        printf("  Discrepancy    : Rs %.2f\n\n", net_intended - (double)net);
    }

    /* Safe demonstration of valid increment (avoiding undefined behaviour: count = count++ + 1) */
    int count = 3;
    count = count + 1;
    printf("Valid bill counter update (count = count + 1): count = %d\n", count);
    printf("Note: 'count = count++ + 1;' is omitted from executable logic because\n");
    printf("modifying and reading 'count' without a sequence point is Undefined Behaviour.\n");

    return 0;
}
