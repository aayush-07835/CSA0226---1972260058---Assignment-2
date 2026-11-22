/*
 * Course: CSA02 - C Programming (Assignment 2 - CO2)
 * Task 1: Alternative Concept - Step-by-Step Intermediate Variables
 * Standard: C11
 */

#include <stdio.h>

typedef struct {
    double gross;
    double discount;
    double taxable;
    double tax;
    double total;
    double promo_deduction;
    double final_amount;
} InvoiceBreakdown;

InvoiceBreakdown generate_invoice(double price, int qty, int is_senior) {
    InvoiceBreakdown inv = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    /* Step 1: Gross amount */
    inv.gross = price * (double)qty;

    /* Step 2: Senior citizen discount (15% if eligible) */
    if (is_senior) {
        inv.discount = inv.gross * 0.15;
    } else {
        inv.discount = 0.0;
    }

    /* Step 3: Taxable amount after trade/senior discount */
    inv.taxable = inv.gross - inv.discount;

    /* Step 4: 5% GST on taxable value */
    inv.tax = inv.taxable * 0.05;

    /* Step 5: Total after tax */
    inv.total = inv.taxable + inv.tax;

    /* Step 6: Promotional deduction of Rs 50 if total exceeds Rs 1000 */
    if (inv.total > 1000.0) {
        inv.promo_deduction = 50.0;
    } else {
        inv.promo_deduction = 0.0;
    }

    /* Step 7: Final payable amount */
    inv.final_amount = inv.total - inv.promo_deduction;

    return inv;
}

int main(void) {
    double prices[3] = {250.0, 45.0, 350.0};
    int qtys[3]      = {3, 3, 3};
    int seniors[3]   = {1, 1, 1};

    printf("=========================================================================\n");
    printf("TASK 1: ALTERNATIVE STEP-BY-STEP INTERMEDIATE VARIABLE IMPLEMENTATION\n");
    printf("=========================================================================\n");

    for (int i = 0; i < 3; i++) {
        InvoiceBreakdown inv = generate_invoice(prices[i], qtys[i], seniors[i]);
        printf("\nTest Case %d (Price=%.2f, Qty=%d, Senior=%d):\n",
               i + 1, prices[i], qtys[i], seniors[i]);
        printf("  Gross Amount     : Rs %8.2f\n", inv.gross);
        printf("  Senior Discount  : Rs %8.2f\n", inv.discount);
        printf("  Taxable Value    : Rs %8.2f\n", inv.taxable);
        printf("  GST (5%%)         : Rs %8.2f\n", inv.tax);
        printf("  Total Bill       : Rs %8.2f\n", inv.total);
        printf("  Promo Deduction  : Rs %8.2f\n", inv.promo_deduction);
        printf("  Final Payable    : Rs %8.2f\n", inv.final_amount);
    }

    return 0;
}
