# Testing & Verification Strategy — CSA02 Assignment 2

## 1. Compiler Strictness & Static Hygiene
Every C source file was compiled using GCC 12.2.0 with strict ISO C11 diagnostics:
```bash
gcc -std=c11 -Wall -Wextra -pedantic <file.c> -o <file>
```
- Zero compiler warnings or errors across all 22 source files.
- Undefined behaviour (`count = count++ + 1`) in Task 1 was isolated and analyzed analytically rather than embedded into production execution paths.

## 2. Equivalence Partitioning & Boundary Value Analysis
- **Task 1 (Billing):** Tested normal senior bills (`250 * 3`), fractional rupee truncation cases (`45 * 3`), promotional threshold boundary (`350 * 3` dropping below `1000` after discount), and non-senior bills exceeding `Rs 1000` (`400 * 3`).
- **Task 2 (Short-Circuit):** Used a deterministic Linear Congruential Generator (`seed = 42`) over `N = 1,000` passengers to guarantee 100% reproducible call counts (`885` vs `1000`) and verified invariant concession counts (`255`) across all orderings.
- **Task 3 (Bitwise Register):** Verified bit transitions (`00000000 -> 00000001 -> 00000101 -> 00000111 -> 00000110`) against manual binary predictions and exact assignment output strings.
- **Task 4 (Grade Classifier):** Tested 14 boundary values (`101, 100, 90, 89, 80, 79, 70, 69, 60, 59, 50, 49, 0, -1`) across `else-if`, `switch`, and lookup-table implementations, specifically verifying `100` (`marks/10 == 10`) and `-1` (`-1/10 == 0` truncation trap).
- **Task 5 (Prime Verification):** Tested small edge cases (`0, 1, 2, 3`), composite early-exit (`100 -> 1 division`), and primes (`97 -> 8`, `7919 -> 87`, `1000003 -> 999`), confirming identical results across `for`, `while`, `do-while`, and Sieve implementations.
- **Task 6 (Loan Repayment):** Cross-checked monthly balances against hand-calculated amortization (`Rs 10,000` at `2%`, `Rs 2,000` EMI -> `6 months`, `Rs 645.38` interest) and tested boundary EMIs (`Rs 205`, `Rs 200`, `Rs 180`) to validate the 360-month safety `break`.
- **Task 7 (Redesign Benchmark):** Verified 100% classification agreement (`2,762` primes in `[2..25,000]`) between `Original_Implementation` and `Redesigned_Implementation` while measuring exact modulo division counts and `CLOCK_MONOTONIC` elapsed times.
