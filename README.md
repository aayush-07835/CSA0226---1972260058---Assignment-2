# CSA02 – C Programming | Assignment 2 (CO2)

## Student & Course Metadata
- **Institution:** Saveetha Institute of Medical and Technical Sciences (SIMATS)
- **Programme:** B.E. / B.Tech – Computer Science and Engineering
- **Course Code & Name:** CSA02 – C Programming
- **Assignment:** Assignment 2 – CO2 (Operators, Decision-Making, Looping & Program Redesign)
- **Student Name:** Aayush Nambiar T
- **Register Number:** 1972260058
- **Target GitHub Repository Name:** `CSA02-1972260058-Assignment2`
- **Language & Standard:** C (`-std=c11`)
- **Verified Compiler:** `gcc (Debian 12.2.0-14+deb12u1) 12.2.0`
- **Maximum Marks:** 50

---

## Repository Structure

```text
CSA02_CO2_Assignment_2/
├── README.md
├── SUMMARY.md
├── Assignment_Report.docx
├── Assignment_Report.pdf
├── Task01_Precedence_Associativity/
│   ├── Q1_Main.c
│   ├── Q1_Corrected.c
│   ├── Q1_Alternative.c
│   ├── README.md
│   ├── predictions.csv
│   ├── test_cases.csv
│   ├── output/
│   └── screenshots/
├── Task02_Short_Circuit_Evaluation/
│   ├── Q2_Main.c
│   ├── Q2_Nested_If.c
│   ├── Q2_Bitwise_Comparison.c
│   ├── README.md
│   ├── passenger_data.csv
│   ├── call_counts.csv
│   ├── output/
│   └── screenshots/
├── Task03_Bitwise_Device_Register/
│   ├── Q3_Main.c
│   ├── Q3_Array_Alternative.c
│   ├── README.md
│   ├── register_predictions.csv
│   ├── output/
│   └── screenshots/
├── Task04_Grade_Classifier/
│   ├── Q4_Else_If.c
│   ├── Q4_Switch.c
│   ├── Q4_Lookup_Table.c
│   ├── Q4_Scholarship.c
│   ├── README.md
│   ├── boundary_tests.csv
│   ├── output/
│   └── screenshots/
├── Task05_Prime_Number_Loops/
│   ├── Q5_Brute_Force_For.c
│   ├── Q5_Optimized_For.c
│   ├── Q5_Optimized_While.c
│   ├── Q5_Optimized_Do_While.c
│   ├── Q5_Sieve_Alternative.c
│   ├── README.md
│   ├── division_counts.csv
│   ├── output/
│   └── screenshots/
├── Task06_Loan_Repayment/
│   ├── Q6_Loan_Schedule.c
│   ├── Q6_Formula_Alternative.c
│   ├── README.md
│   ├── loan_schedule.csv
│   ├── iteration_analysis.csv
│   ├── output/
│   └── screenshots/
├── Task07_Redesign_Challenge/
│   ├── Original_Implementation.c
│   ├── Redesigned_Implementation.c
│   ├── Benchmark.c
│   ├── README.md
│   ├── redesign_flowchart.png
│   ├── comparison.csv
│   ├── performance_analysis.md
│   ├── output/
│   └── screenshots/
└── Documentation/
    ├── Algorithms.md
    ├── Pseudocode.md
    ├── Complexity_Analysis.md
    ├── Testing_Strategy.md
    └── Viva_Preparation.md
```

---

## Compilation & Execution Instructions

All C source files adhere strictly to ISO C11 and compile cleanly with zero warnings under `-Wall -Wextra -pedantic`:

```bash
gcc -std=c11 -Wall -Wextra -pedantic <source_file.c> -o <executable_name>
./<executable_name>
```

> **Note for Task 6 (`Q6_Formula_Alternative.c`):** Link the C math library with `-lm`:
> ```bash
> gcc -std=c11 -Wall -Wextra -pedantic Q6_Formula_Alternative.c -o Q6_Formula_Alternative -lm
> ./Q6_Formula_Alternative
> ```

---

## Overview of Tasks & Verified Results

| Task | Folder | Marks | Core Concept | Key Verified Outcome |
| :--- | :--- | :---: | :--- | :--- |
| **Q1** | `Task01_Precedence_Associativity` | 6 | Operator Precedence, Integer Division, UB | Exposed integer truncation and pre-discount GST bug; corrected with `double` & intermediate variables |
| **Q2** | `Task02_Short_Circuit_Evaluation` | 4 | Short-Circuit `&&`/`||` vs `&`/`|`, Audit Side-Effects | Reduced slow server calls from `1000` to `885` on `N=1000` (seed 42); proved audit log requires `verify()` first |
| **Q3** | `Task03_Bitwise_Device_Register` | 6 | Bit Masks (`|`, `&`, `^`, `~`, `<<`, `>>`) | Verified exact output `00000101`, `00000110`, `AC is ON, PUMP is OFF`; 8x memory reduction vs `char[8]` |
| **Q4** | `Task04_Grade_Classifier` | 6 | `else-if`, `switch(marks/10)`, Lookup Table | Verified `100:S 95:S 83:A 50:D 49:F -5:?`, fall-through demo (`83 -> B`), and 2D scholarship table |
| **Q5** | `Task05_Prime_Number_Loops` | 7 | `for`, `while`, `do-while`, `sqrt(n)`, Sieve | Verified divisions: `97->8`, `100->1`, `7919->87`, `1000003->999` vs brute-force `1000001` |
| **Q6** | `Task06_Loan_Repayment` | 8 | Loop Termination, `EPSILON`, Safety `break` | Verified 6-month schedule (`Rs 645.38` interest), 360-month safety break, and log formula ceiling |
| **Q7** | `Task07_Redesign_Challenge` | 13 | Bottleneck Diagnosis, Odd-Only `sqrt(n)` Redesign | Cut divisions for `1000003` from `1000001` to `500` (`99.95%` reduction; `2000x` fewer checks) |

---

## Evidence Files & Data Integrity Policy

- **`output/` directories:** Contain verbatim compiler metadata and actual stdout captures produced by executing each C binary under GCC 12.2.0.
- **`.csv` datasets:** Generated directly by the compiled C programs (`passenger_data.csv`, `call_counts.csv`, `loan_schedule.csv`, `iteration_analysis.csv`, `comparison.csv`) or verified against program outputs (`predictions.csv`, `test_cases.csv`, `register_predictions.csv`, `boundary_tests.csv`, `division_counts.csv`).
- **`screenshots/` directories:** Contain `CAPTURE_INSTRUCTIONS.txt` rather than synthetic images. Per academic integrity rules, capture your own terminal screenshots locally before pushing to GitHub.

---

## Progressive GitHub Submission Workflow

Per the assignment instructions, commit each task progressively rather than uploading all files in a single commit:

```bash
git init
git remote add origin https://github.com/<your-username>/CSA02-1972260058-Assignment2.git

git add README.md SUMMARY.md Documentation/
git commit -m "Initialize repository structure and technical documentation"

git add Task01_Precedence_Associativity/
git commit -m "Complete Task 1: Precedence, associativity, and pharmacy billing analysis"

git add Task02_Short_Circuit_Evaluation/
git commit -m "Complete Task 2: Short-circuit evaluation and audit-log ordering experiment"

git add Task03_Bitwise_Device_Register/
git commit -m "Complete Task 3: Bitwise device-status register and array comparison"

git add Task04_Grade_Classifier/
git commit -m "Complete Task 4: Grade classifier (else-if, switch, lookup) and scholarship matrix"

git add Task05_Prime_Number_Loops/
git commit -m "Complete Task 5: Prime loop variants, operation counts, and Sieve analysis"

git add Task06_Loan_Repayment/
git commit -m "Complete Task 6: Micro-loan repayment simulator, safety limit, and formula comparison"

git add Task07_Redesign_Challenge/ Assignment_Report.docx Assignment_Report.pdf
git commit -m "Complete Task 7: Day-4 Redesign Challenge and final assignment report"

git push -u origin main
```
