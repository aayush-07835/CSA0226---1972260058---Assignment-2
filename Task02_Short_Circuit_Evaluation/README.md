# Task 2 — When Does Short-Circuit Evaluation Matter? (4 Marks)

## Files in This Folder
- `Q2_Main.c`: Generates 1,000 deterministic passengers (LCG seed = 42), compares condition orderings with `&&` and `||`, and evaluates the audit-log side-effect requirement.
- `Q2_Nested_If.c`: Equivalent branching implementation using nested `if / else if` statements.
- `Q2_Bitwise_Comparison.c`: Demonstrates non-short-circuit `&` and `|` behavior (1,000 calls always executed) and the bitwise truthiness pitfall (`2 & 4 == 0`).
- `passenger_data.csv`: Generated dataset of 1,000 passengers.
- `call_counts.csv`: Measured slow-function calls and audit log counts across orderings.
- `output/`: Actual stdout captures from GCC 12.2.0.

## Compile & Run Commands
```bash
gcc -std=c11 -Wall -Wextra -pedantic Q2_Main.c -o Q2_Main && ./Q2_Main
gcc -std=c11 -Wall -Wextra -pedantic Q2_Nested_If.c -o Q2_Nested_If && ./Q2_Nested_If
gcc -std=c11 -Wall -Wextra -pedantic Q2_Bitwise_Comparison.c -o Q2_Bitwise_Comparison && ./Q2_Bitwise_Comparison
```
