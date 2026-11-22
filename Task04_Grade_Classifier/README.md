# Task 4 — else–if Ladder or switch? (6 Marks)

## Files in This Folder
- `Q4_Switch.c`: Completed starter code using `switch (marks / 10)`, full boundary suite, and missing-`break` fall-through demonstration.
- `Q4_Else_If.c`: Grade classifier implemented with an `else-if` ladder.
- `Q4_Lookup_Table.c`: `O(1)` lookup table (`char grades[11]`) grade classifier.
- `Q4_Scholarship.c`: University scholarship classifier combining grade and family income band via a 2D decision matrix.
- `boundary_tests.csv`: Boundary test matrix across all 14 boundary/invalid inputs.
- `output/`: Actual stdout captures from GCC 12.2.0.

## Compile & Run Commands
```bash
gcc -std=c11 -Wall -Wextra -pedantic Q4_Switch.c -o Q4_Switch && ./Q4_Switch
gcc -std=c11 -Wall -Wextra -pedantic Q4_Else_If.c -o Q4_Else_If && ./Q4_Else_If
gcc -std=c11 -Wall -Wextra -pedantic Q4_Lookup_Table.c -o Q4_Lookup_Table && ./Q4_Lookup_Table
gcc -std=c11 -Wall -Wextra -pedantic Q4_Scholarship.c -o Q4_Scholarship && ./Q4_Scholarship
```
