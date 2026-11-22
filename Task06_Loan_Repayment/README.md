# Task 6 — Loops That Must Terminate: Loan Repayment Schedule (8 Marks)

## Files in This Folder
- `Q6_Loan_Schedule.c`: Month-by-month repayment simulator with epsilon termination (`balance > 1e-6`), final-installment capping, non-amortizing detection, 360-month safety `break`, and EMI sensitivity sweep.
- `Q6_Formula_Alternative.c`: Closed-form annuity formula `n = -log(1 - r*P/E) / log(1 + r)` comparison.
- `loan_schedule.csv`: Month-by-month amortization schedule for `P = Rs 10,000`, `r = 2%`, `EMI = Rs 2,000`.
- `iteration_analysis.csv`: Iteration growth table as repayment approaches monthly interest (`Rs 200`).
- `output/`: Actual stdout captures from GCC 12.2.0.

## Compile & Run Commands
```bash
gcc -std=c11 -Wall -Wextra -pedantic Q6_Loan_Schedule.c -o Q6_Loan_Schedule && ./Q6_Loan_Schedule
gcc -std=c11 -Wall -Wextra -pedantic Q6_Formula_Alternative.c -o Q6_Formula_Alternative -lm && ./Q6_Formula_Alternative
```
