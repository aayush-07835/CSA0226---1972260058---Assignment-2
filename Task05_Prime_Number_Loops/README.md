# Task 5 — Count the Work Done by a Loop (7 Marks)

## Files in This Folder
- `Q5_Optimized_For.c`: Completed starter code (`TODO 1` with `i * i <= n`) verifying exact assignment output (`97->8`, `100->1`, `7919->87`, `1000003->999`) plus `0, 1, 2, 3`.
- `Q5_Brute_Force_For.c`: Unoptimized trial division (`2` to `n - 1`).
- `Q5_Optimized_While.c`: `while` loop variant of `i * i <= n`.
- `Q5_Optimized_Do_While.c`: `do-while` loop variant with explicit `n == 2 || n == 3` entry guards.
- `Q5_Sieve_Alternative.c`: Sieve of Eratosthenes preprocessing up to `N = 1,000,003` for `O(1)` queries.
- `division_counts.csv`: Division count comparison across all loop variants.
- `output/`: Actual stdout captures from GCC 12.2.0.

## Compile & Run Commands
```bash
gcc -std=c11 -Wall -Wextra -pedantic Q5_Optimized_For.c -o Q5_Optimized_For && ./Q5_Optimized_For
gcc -std=c11 -Wall -Wextra -pedantic Q5_Brute_Force_For.c -o Q5_Brute_Force_For && ./Q5_Brute_Force_For
gcc -std=c11 -Wall -Wextra -pedantic Q5_Optimized_While.c -o Q5_Optimized_While && ./Q5_Optimized_While
gcc -std=c11 -Wall -Wextra -pedantic Q5_Optimized_Do_While.c -o Q5_Optimized_Do_While && ./Q5_Optimized_Do_While
gcc -std=c11 -Wall -Wextra -pedantic Q5_Sieve_Alternative.c -o Q5_Sieve_Alternative && ./Q5_Sieve_Alternative
```
