# Task 1 — Precedence, Associativity and the Discount Bug (6 Marks)

## Files in This Folder
- `Q1_Main.c`: Evaluates the original unparenthesized integer expression across 3 test cases and compares against exact floating-point billing.
- `Q1_Corrected.c`: Corrected C11 implementation using `double`, explicit parentheses, post-discount GST calculation, and well-defined counter increment.
- `Q1_Alternative.c`: Step-by-step decomposition using named intermediate variables (`gross`, `discount`, `taxable`, `tax`, `total`, `promo_deduction`, `final_amount`).
- `predictions.csv`: Pre-execution manual predictions vs actual observed results.
- `test_cases.csv`: Complete breakdown of all verified billing test cases.
- `output/`: Actual stdout captures from GCC 12.2.0.

## Compile & Run Commands
```bash
gcc -std=c11 -Wall -Wextra -pedantic Q1_Main.c -o Q1_Main && ./Q1_Main
gcc -std=c11 -Wall -Wextra -pedantic Q1_Corrected.c -o Q1_Corrected && ./Q1_Corrected
gcc -std=c11 -Wall -Wextra -pedantic Q1_Alternative.c -o Q1_Alternative && ./Q1_Alternative
```
