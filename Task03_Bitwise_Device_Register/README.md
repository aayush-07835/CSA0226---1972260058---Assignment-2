# Task 3 — Engineer a Device-Status Register with Bitwise Operators (6 Marks)

## Files in This Folder
- `Q3_Main.c`: Completed starter code (`TODO 1` to `TODO 4`) using bitwise operators (`|`, `&`, `~`, `^`, `<<`, `>>`), binary printer, ON-device counter, and precedence verification.
- `Q3_Array_Alternative.c`: Alternative implementation using `char state[8]` with memory and complexity comparison for 1,000,000 homes.
- `register_predictions.csv`: Step-by-step pre-execution register predictions vs observed binary states.
- `output/`: Actual stdout captures from GCC 12.2.0.

## Compile & Run Commands
```bash
gcc -std=c11 -Wall -Wextra -pedantic Q3_Main.c -o Q3_Main && ./Q3_Main
gcc -std=c11 -Wall -Wextra -pedantic Q3_Array_Alternative.c -o Q3_Array_Alternative && ./Q3_Array_Alternative
```
