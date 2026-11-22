/*
 * Course: CSA02 - C Programming (Assignment 2 - CO2)
 * Task 1: Corrected Jan Aushadhi Pharmacy Billing Implementation
 * Standard: C11
 */

#include <stdio.h>

double compute_net_bill(double unit_price, int quantity, int is_senior, double *out_total) {
    if (unit_price < 0.0 || quantity <= 0) {
        if (out_total != NULL) {
            *out_total = 0.0;
        }
        return 0.0;
    }

    const double SENIOR_DISCOUNT_RATE = 0.15;
    const double GST_RATE             = 0.05;
    const double PROMO_THRESHOLD      = 1000.0;
    const double PROMO_FLAT_OFF       = 50.0;

    double gross = unit_price * (double)quantity;
    double discount = (is_senior != 0) ? (gross * SENIOR_DISCOUNT_RATE) : 0.0;
    double taxable_amount = gross - discount;
    double gst = taxable_amount * GST_RATE;
    double total = taxable_amount + gst;

    if (out_total != NULL) {
        *out_total = total;
    }

    double net = (total > PROMO_THRESHOLD) ? (total - PROMO_FLAT_OFF) : total;
    return net;
}

int main(void) {
    struct {
        const char *name;
        double price;
        int qty;
        int senior;
    } bills[4] = {
        {"Bill 1 (Senior, Moderate)",     250.0, 3, 1},
        {"Bill 2 (Senior, Fractional)",    45.0, 3, 1},
        {"Bill 3 (Senior, Near 1000)",    350.0, 3, 1},
        {"Bill 4 (Non-Senior, > 1000)",   400.0, 3, 0}
    };

    int processed_count = 0;

    printf("=========================================================================\n");
    printf("TASK 1: CORRECTED PHARMACY BILLING (FLOATING-POINT + CLEAR PRECEDENCE)\n");
    printf("=========================================================================\n");

    for (int i = 0; i < 4; i++) {
        double total = 0.0;
        double net = compute_net_bill(bills[i].price, bills[i].qty, bills[i].senior, &total);
        processed_count++; /* Well-defined increment replacing UB expression */

        printf("\n[%d] %s\n", processed_count, bills[i].name);
        printf("    Unit Price : Rs %.2f | Qty : %d | Senior : %s\n",
               bills[i].price, bills[i].qty, bills[i].senior ? "Yes" : "No");
        printf("    Total (incl. 5%% GST) : Rs %.2f\n", total);
        printf("    Net Payable          : Rs %.2f\n", net);
    }

    return 0;
}
