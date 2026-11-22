# Executive Summary — CSA02 Assignment 2 (CO2)

- **Student:** Aayush Nambiar T (`1972260058`)
- **Course:** CSA02 – C Programming (CO2)
- **Total Marks:** 50 (7 Tasks)
- **Verification Status:** All 22 C programs compiled with `gcc -std=c11 -Wall -Wextra -pedantic` (zero warnings) and executed to produce genuine operation counts and CSV logs.

## Key Engineering Takeaways Across Q1–Q7

1. **Q1 (Precedence & Integer Arithmetic):** Unparenthesized integer formulas silently truncate fractional rupees (`45 * 3 * 15 / 100 = 20` instead of `20.25`) and compute GST before deducting the senior discount. Modifying and reading a variable without an intervening sequence point (`count = count++ + 1`) triggers Undefined Behaviour under ISO C11 §6.5/2.
2. **Q2 (Short-Circuit Evaluation):** Placing cheap, selective conditions before an expensive verification call saved `115` server calls (`885` vs `1000`) across `1,000` deterministic passengers. However, when the function carries a mandatory audit-logging side effect, short-circuiting becomes a compliance bug and the logging call must execute first.
3. **Q3 (Bitwise Hardware Register):** Packing 8 boolean device states into one `unsigned char` reduces memory usage for `1,000,000` smart homes from `8 MB` (`char state[8]`) to `1 MB` (`87.5%` reduction) while maintaining `O(1)` bit-mask operations.
4. **Q4 (Multi-Way Branching & Lookup Tables):** Integer division `marks / 10` maps `[0..100]` into 11 discrete buckets (`0..10`), requiring explicit handling of `case 10` (`marks == 100`) and strict range guards (`0 <= marks <= 100`) to avoid `-5 / 10 == 0` mapping to `'F'`. A static lookup table achieves `O(1)` branching-free dispatch in 11 bytes.
5. **Q5 (Loop Bounds & Operation Counting):** Restricting trial divisors to `i * i <= n` cuts divisor checks for `n = 1,000,003` from `1,000,001` to `999` (`99.90%` reduction). `do-while` loops require explicit entry guards for `n = 2` and `n = 3` because the loop body runs before the termination condition.
6. **Q6 (Numerical Loop Termination):** Using `while (balance > 1e-6)` prevents infinite loops caused by IEEE-754 floating-point rounding drift, capping the final installment avoids overpayment (`Rs 645.38` in Month 6 for the `Rs 10,000` loan), and a `360`-month `break` guard halts non-amortizing loans where `EMI <= monthly_interest`.
7. **Q7 (Day-4 Redesign Challenge):** Exploiting parity (`2` is the sole even prime) alongside the `sqrt(n)` bound (`i <= n / i`, `i += 2`) cuts divisions for `1,000,003` from `1,000,001` down to `500` (`99.95%` reduction) and reduces batch runtime over `[2..25000]` from `350.204 ms` to `3.884 ms` (`90.17x` wall-clock speedup).
