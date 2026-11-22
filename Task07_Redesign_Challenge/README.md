# Task 7 — Day-4 Design Challenge: Diagnose, Redesign and Validate (13 Marks)

## Files in This Folder
- `Original_Implementation.c`: Brute-force prime checker (`O(n)` worst-case divisions).
- `Redesigned_Implementation.c`: Parity-filtered odd-only square-root prime checker (`O(sqrt(n)/2)` divisions with overflow-safe bound `i <= n / i`).
- `Benchmark.c`: Head-to-head operation count and wall-clock benchmark across single tickets and batch range `[2..25000]`.
- `redesign_flowchart.png`: Control-flow diagram of the redesigned algorithm.
- `comparison.csv`: Exact division counts, savings, and speedup ratios.
- `performance_analysis.md`: Detailed engineering analysis covering Sections A–F.
- `output/`: Actual stdout captures from GCC 12.2.0.

## Compile & Run Commands
```bash
gcc -std=c11 -Wall -Wextra -pedantic Original_Implementation.c -o Original_Implementation && ./Original_Implementation
gcc -std=c11 -Wall -Wextra -pedantic Redesigned_Implementation.c -o Redesigned_Implementation && ./Redesigned_Implementation
gcc -std=c11 -Wall -Wextra -pedantic Benchmark.c -o Benchmark && ./Benchmark
```
