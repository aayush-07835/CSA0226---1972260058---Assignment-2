# Day-4 Design Challenge — Performance & Trade-off Analysis

## A. Bottleneck Diagnosis
In `Original_Implementation.c`, primality verification tests every integer divisor $i \in [2, n - 1]$ via `n % i == 0`.
- **Primary Bottleneck:** The modulo division instruction (`n % i == 0`) inside the loop body.
- **Growth Rate:** For any prime $n$, the loop executes $n - 2$ modulo divisions ($\Theta(n)$ linear scaling). For $n = 1,000,003$, it executes **1,000,001 divisions**.
- **Redundant Work:**
  1. Checking divisors $i > \lfloor\sqrt{n}\rfloor$ is mathematically redundant because factors occur in complementary pairs $(a, b)$ with $a \cdot b = n \implies \min(a, b) \le \sqrt{n}$.
  2. Testing even divisors $4, 6, 8, \dots$ after testing $2$ is redundant because any multiple of an even integer is already divisible by $2$.

## B. Design Objective
- **Target:** Reduce worst-case divisor checks from $n - 2$ to at most $\lfloor(\sqrt{n} - 1)/2\rfloor + 1$ (a $>99.9\%$ reduction for $n \ge 10^6$ and a $50\%$ reduction relative to standard $\sqrt{n}$ trial division), while eliminating signed/unsigned multiplication overflow in `i * i <= n`.
- **Success Metric:** Measured modulo division counter (`checks`) and wall-clock execution time (`clock_gettime`) across identical test inputs and a batch workload $[2..25,000]$.

## C. Revised Solution & Trade-offs
1. Handle $n < 2$ (return `0`) and $n = 2$ (return `1`) in $O(1)$ without divisions.
2. Perform a single parity test (`checks++`, `if (n % 2 == 0) return 0;`), immediately rejecting $50\%$ of all composite inputs in 1 division.
3. Loop over odd candidates only (`for (unsigned long i = 3; i <= n / i; i += 2)`), using integer division `i <= n / i` rather than `i * i <= n` so `i * i` can never overflow `ULONG_MAX`.
- **Space Requirement:** $O(1)$ auxiliary memory (identical to original; zero heap allocation).
- **Trade-off:** Slightly higher code complexity (3 extra edge-case branches) and an integer division `n / i` in the loop guard (which modern x86-64/ARM compilers often fuse with `n % i` into a single `DIV` instruction).

## D. Pre-Implementation Prediction
For $n = 1,000,003$ ($\lfloor\sqrt{1,000,003}\rfloor = 1000$):
- Parity test (`n % 2`) = $1$ check.
- Odd integers in $[3, 999]$ = $(999 - 3)/2 + 1 = 499$ checks.
- **Predicted Total Divisions:** $1 + 499 = 500$ checks (down from $1,000,001$, a **$99.9500\%$** reduction).

## E. Empirical Validation Results
- `n = 97`: `95 -> 5` divisions (`94.74%` reduction)
- `n = 7,919`: `7,917 -> 44` divisions (`99.44%` reduction)
- `n = 104,729`: `104,727 -> 162` divisions (`99.85%` reduction)
- `n = 1,000,003`: `1,000,001 -> 500` divisions (`99.95%` reduction — exact match to prediction!)
- Batch `[2..25,000]`: `32,534,310 -> 222,377` divisions (`99.32%` reduction; `350.204 ms -> 3.884 ms`).

## F. Final Design Defense
The objective was completely achieved with zero additional memory overhead. The original brute-force loop remains acceptable only for tiny inputs ($n < 50$) in introductory pedagogical demonstrations where readability outweighs performance. For batch queries over dense intervals $[1..N]$ where $O(N)$ memory is acceptable, a Sieve of Eratosthenes further improves amortized per-query time to $O(1)$.
