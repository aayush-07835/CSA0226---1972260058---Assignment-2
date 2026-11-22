# Comprehensive Viva-Voce Preparation Guide — CSA02 Assignment 2 (CO2)

This guide covers all 12 core syllabus topics with concise, technically accurate answers structured for oral faculty evaluation.

---

## Topic 1: Operator Precedence and Associativity (Q1)

1. **Q: What is the difference between operator precedence and operator associativity?**
   **A:** Precedence determines which operator binds tighter when two different operators share an operand (e.g., `*` has higher precedence than `+`). Associativity determines the grouping order when two operators of the *same* precedence appear adjacent to each other (e.g., `*`, `/`, and `%` associate left-to-right, while `=` and `?:` associate right-to-left).
2. **Q: In `price * qty * 15 / 100`, why does `15 / 100` not evaluate to `0`?**
   **A:** Because `*` and `/` share the same precedence level and associate left-to-right. Therefore, `((price * qty) * 15) / 100` is evaluated first, multiplying by `15` before dividing by `100`.
3. **Q: Why did the original Jan Aushadhi billing formula produce wrong results even with left-to-right associativity?**
   **A:** Three reasons: (1) integer division truncated fractional rupees (e.g., `2025 / 100 = 20` instead of `20.25`), (2) 5% GST was calculated on the full pre-discount gross amount instead of the discounted taxable value, and (3) `price * qty * 15` risks signed `int` overflow for large bills.
4. **Q: What is the associativity of the conditional ternary operator `?:`?**
   **A:** Right-to-left. In `a ? b : c ? d : e`, it groups as `a ? b : (c ? d : e)`.
5. **Q: Does C guarantee the evaluation order of operands in `f() + g()`?**
   **A:** No. Precedence controls grouping, not temporal evaluation order. In `f() + g()`, the compiler may call `f()` or `g()` first (unspecified behaviour).
6. **Q: How do intermediate variables improve code quality without hurting performance?**
   **A:** Named intermediate variables (`gross`, `discount`, `taxable`, `gst`) make tax rules explicit and self-documenting, while modern optimizing compilers map them into CPU registers with zero extra memory or runtime cost.
7. **Q: What happens if you write `double x = 15 / 100;` in C?**
   **A:** Both `15` and `100` are `int` literals, so integer division yields `0`, which is then converted to `0.0`. Writing `15.0 / 100.0` forces floating-point division (`0.15`).
8. **Q: What is the precedence relationship between bitwise `&` and equality `==`?**
   **A:** Equality `==` has *higher* precedence than bitwise `&`. Thus `reg & 1 == 0` parses as `reg & (1 == 0)` (`reg & 0`), which is a classic C bug; parentheses `(reg & 1) == 0` are mandatory.

---

## Topic 2: Undefined Behaviour and Sequence Points (Q1)

1. **Q: Why is `count = count++ + 1;` Undefined Behaviour (UB) in C?**
   **A:** Under ISO C11 (§6.5/2), if a side effect on a scalar object (`count++`) is unsequenced relative to either another side effect on the same object (`count = ...`) or a value computation using the value of the same object, the behaviour is undefined.
2. **Q: What does "Undefined Behaviour" actually mean according to the C standard?**
   **A:** The C standard imposes no requirements whatsoever. The program may produce any value, crash, behave differently under `-O0` vs `-O2`, or appear to work on one compiler and fail on another.
3. **Q: What warning does GCC `-Wall` emit for `count = count++ + 1;`?**
   **A:** GCC enables `-Wsequence-point` under `-Wall` and typically warns: `warning: operation on 'count' may be undefined [-Wsequence-point]`. However, compilers are not required by the standard to diagnose all UB.
4. **Q: How do you fix `count = count++ + 1;` cleanly?**
   **A:** Write `count = count + 1;`, `count += 1;`, or simply `count++;` as a standalone statement.
5. **Q: Is `i++` inside `arr[i++]` undefined behaviour?**
   **A:** No, because `i` is modified once and its value is read only to determine the value to be stored (`arr[i]` uses the prior value). However, `arr[i] = i++;` IS undefined behaviour because `i` is read on the LHS unsequenced relative to `i++` on the RHS.
6. **Q: Which operators in C introduce explicit sequence points (or sequenced-before guarantees in C11)?**
   **A:** Logical AND (`&&`), logical OR (`||`), conditional ternary (`?:`), and the comma operator (`,`), as well as the end of every full expression (`;`).
7. **Q: Why is signed integer overflow (`INT_MAX + 1`) dangerous in C?**
   **A:** Signed overflow is Undefined Behaviour in C, allowing compilers to optimize away overflow checks, whereas unsigned overflow is strictly defined modulo $2^N$.
8. **Q: Why must we never rely on testing a UB snippet to "prove" what it outputs?**
   **A:** Because any observed output is merely an artifact of one compiler version, architecture, and optimization flag—not a language guarantee.

---

## Topic 3: Short-Circuit Evaluation (Q2)

1. **Q: Define short-circuit evaluation in C.**
   **A:** For `A && B`, if `A` evaluates to `0` (false), `B` is never evaluated because the conjunction is guaranteed false. For `A || B`, if `A` evaluates to non-zero (true), `B` is never evaluated because the disjunction is guaranteed true.
2. **Q: In `(is_senior && is_eligible_class) || verify_disability_card()`, how many calls were saved in our 1,000-passenger experiment?**
   **A:** Out of 1,000 passengers (seed 42), `115` were both senior citizens and in an eligible class, so `verify_disability_card()` was skipped 115 times (`885` calls instead of `1,000`).
3. **Q: When should the cheapest or most-likely-false condition be placed first in an `&&` chain?**
   **A:** Always when conditions are pure (side-effect-free), because rejecting a candidate early on a fast or high-rejection-rate check avoids executing expensive downstream checks.
4. **Q: When does condition ordering become irrelevant for performance?**
   **A:** When all operands are simple in-memory variables of identical $O(1)$ cost and no short-circuiting skips an expensive function call, or when the first condition almost always triggers evaluation of the second (e.g., 99.9% pass rate on `A` in `A && B`).
5. **Q: How did adding an audit log inside `verify_disability_card()` change our recommended ordering?**
   **A:** Short-circuiting skipped `verify_disability_card()` for 115 passengers, leaving the audit log incomplete (`885/1000` entries). When a function has a required side effect (logging, state mutation), it must be placed first (`verify() || ...`) or called unconditionally before branching.
6. **Q: What is the difference between `&` and `&&` when used on boolean conditions?**
   **A:** `&` is a bitwise operator that ALWAYS evaluates both operands (no short-circuiting) and performs bit-by-bit AND. `&&` is a logical operator with short-circuiting that treats any non-zero value as `1` (true).
7. **Q: Give an example where `a & b` gives the wrong boolean answer even when both `a` and `b` are true.**
   **A:** If `a = 2` (`0010`) and `b = 4` (`0100`), both are non-zero (true in C), so `a && b` evaluates to `1`, whereas `a & b` evaluates to `0` (false).
8. **Q: How does a nested `if` structure compare to `A && B || C`?**
   **A:** Nested `if` statements produce the exact same execution trace and function-call counts as short-circuit logical operators, often with clearer control flow when branches require distinct actions.

---

## Topic 4: Bitwise Operators and Bit Masks (Q3)

1. **Q: Write the four fundamental bitwise idioms for bit position `k` in an `unsigned char reg`.**
   **A:** Set bit: `reg |= (1u << k)`; Clear bit: `reg &= ~(1u << k)`; Toggle bit: `reg ^= (1u << k)`; Read bit: `(reg >> k) & 1u`.
2. **Q: Why do `reg & 1 << dev` and `(reg & 1) << dev` produce different results?**
   **A:** Shift (`<<`) has higher precedence than bitwise AND (`&`). Thus `reg & 1 << dev` parses as `reg & (1 << dev)`, which isolates bit `dev` of `reg` (yielding $2^{\text{dev}}$ or $0$). In contrast, `(reg & 1) << dev` extracts bit `0` (LSB) of `reg` and shifts it left by `dev` positions.
3. **Q: What goes wrong if `signed char` is used instead of `unsigned char` when bit 7 is set?**
   **A:** On two's-complement systems, bit 7 is the sign bit, so setting bit 7 makes the value negative (`-128` to `-1`). Shifting a negative signed integer left (`reg << 1`) is Undefined Behaviour in C11, and right-shifting (`reg >> bit`) performs an arithmetic sign-extending shift on most compilers, filling upper bits with `1`s instead of `0`s.
4. **Q: Why should we write `1u << dev` instead of `1 << dev`?**
   **A:** `1u` is an `unsigned int`, preventing accidental undefined behaviour if shifting into the sign bit of a signed `int`.
5. **Q: How much memory does the bitwise representation save over `char state[8]` for 1,000,000 smart homes?**
   **A:** `unsigned char` uses `1 byte` per home (`1,000,000 bytes` ≈ `0.95 MB`), whereas `char state[8]` uses `8 bytes` per home (`8,000,000 bytes` ≈ `7.63 MB`) — an `8x` (`87.5%`) memory saving.
6. **Q: What is the time complexity of setting a device ON in both representations?**
   **A:** $O(1)$ constant time in both.
7. **Q: How can you count the number of ON bits in `reg` faster than checking all 8 bits?**
   **A:** Using Brian Kernighan's algorithm: `while (reg) { reg &= (reg - 1); count++; }`, which loops only as many times as there are `1` bits, or via a 256-byte precomputed popcount lookup table in $O(1)$.
8. **Q: Trace `reg` after `switch_on(0)`, `switch_on(2)`, `toggle(1)`, `switch_off(0)`.**
   **A:** `00000000` -> `00000001` (`1`) -> `00000101` (`5`) -> `00000111` (`7`) -> `00000110` (`6`).

---

## Topic 5: `switch`, `else-if`, and Fall-Through (Q4)

1. **Q: Why must `marks < 0 || marks > 100` be checked BEFORE `switch (marks / 10)`?**
   **A:** Because in C, integer division truncates toward zero: `-5 / 10` evaluates to `0`, which would falsely match `case 0` (`'F'`) instead of returning `'?'`.
2. **Q: Why does `marks = 100` require `case 10:` in `switch (marks / 10)`?**
   **A:** Because `100 / 10 == 10`, whereas `90..99` divide by `10` to give `9`. Combining `case 10: case 9: return 'S';` handles the full `90–100` range cleanly.
3. **Q: What happens when a `break` or `return` is omitted inside a `switch` case?**
   **A:** Control "falls through" sequentially into the next `case` block regardless of whether its label matches, executing its statements until a `break`, `return`, or the closing brace `}` is reached.
4. **Q: Why can't standard C `switch` directly match non-uniform ranges like `75–84`?**
   **A:** Standard C `case` labels require compile-time integer constant expressions (`case 75: case 76: ...`), and `marks / 10` only groups multiples of 10 (`70–79`, `80–89`). For `75–84`, an `else-if` ladder (`marks >= 75 && marks <= 84`) or a 101-element lookup table `grade[marks]` is far cleaner.
5. **Q: How does a lookup table `char grades[11]` compare in time and space to an `else-if` ladder?**
   **A:** Lookup table runs in $O(1)$ constant time (1 array index, zero branch mispredictions) using `11 bytes` of static read-only memory, whereas an `else-if` ladder performs up to $k$ sequential comparisons ($O(k)$, up to 7 checks for `'F'`).
6. **Q: Why is a 2D lookup table (`SCHOLARSHIP_MATRIX[6][4]`) superior to deeply nested `if` statements for scholarship rules?**
   **A:** A 2D table separates policy data from control logic: adding or modifying a scholarship slab requires editing a table cell rather than untangling 24 nested `if-else` branches, and execution is strictly $O(1)$.
7. **Q: Which structure is easier to modify if grade boundaries change to `92, 82, 72, 62, 52`?**
   **A:** An `else-if` ladder (or a 101-element lookup table indexed directly by `marks`), because `marks / 10` only aligns with decade boundaries (`90, 80, 70, 60, 50`).
8. **Q: Can `switch` work on `float` or `double` variables in C?**
   **A:** No. The controlling expression of `switch` must have an integer type (`char`, `short`, `int`, `long`, `enum`).

---

## Topic 6: Loop Termination & Loop Variants (Q5 & Q6)

1. **Q: Why is `i * i <= n` mathematically sufficient for primality testing?**
   **A:** If $n$ is composite ($n = a \cdot b$ with $a, b > 1$), then both $a$ and $b$ cannot exceed $\sqrt{n}$ (otherwise $a \cdot b > n$). Hence at least one factor satisfies $i \le \sqrt{n} \iff i^2 \le n$.
2. **Q: Why did `do-while` fail on `n = 2` and `n = 3` without special guards?**
   **A:** Because `do-while` is an exit-controlled loop that executes its body *before* checking `i * i <= n`. For `n = 2` and `i = 2`, it executes `2 % 2 == 0` on the first pass and falsely returns `0` (not prime).
3. **Q: Why can `i * i <= n` overflow for large `unsigned long` inputs?**
   **A:** If `n` is close to `ULONG_MAX` (e.g., $2^{64} - 59$), when `i` reaches $\lfloor\sqrt{n}\rfloor + 1$, `i * i` wraps around modulo $2^{64}$ to a small number $\le n$, causing an infinite loop. Writing `i <= n / i` avoids overflow completely.
4. **Q: Why is `while (balance > 0.0)` or `while (balance != 0.0)` dangerous in floating-point loan simulations?**
   **A:** Binary floating-point arithmetic (IEEE-754) cannot represent most decimal fractions (like `0.02`) exactly, leaving tiny residuals like `1e-13` or `-1e-14` that prevent exact equality with `0.0`. Using a tolerance `while (balance > 1e-6)` guarantees clean termination.
5. **Q: Why is `while` preferred over `for` and `do-while` for loan repayment simulation?**
   **A:** The exact number of months is unknown prior to execution (data-dependent termination), making `while` more natural than `for`, and `while` checks `balance > EPSILON` at entry so a zero-principal loan executes `0` iterations (unlike `do-while`).
6. **Q: What happens in the loan simulator when `EMI <= Principal * monthly_rate`?**
   **A:** Each month's interest equals or exceeds the repayment, so the principal never decreases (`EMI == interest`) or grows exponentially (`EMI < interest`). Without the `360`-month `break` safety guard, the loop would run forever.
7. **Q: Why did the manual schedule take 6 months while the closed-form formula gave `n = 5.320532`?**
   **A:** The formula $n = -\ln(1 - rP/E)/\ln(1+r)$ solves for continuous real installments; in practice, discrete monthly payments require $\lceil 5.320532 \rceil = 6$ months, with Month 6 paying only the remaining balance plus interest (`Rs 645.38` instead of `Rs 2,000.00`).
8. **Q: When is `goto` acceptable in C programming?**
   **A:** Only for structured forward error cleanup (releasing multiple resources/locks at a single exit label) or breaking out of deeply nested loops where a single `break` only exits the innermost loop.

---

## Topic 7: Sieve of Eratosthenes, Big-O Analysis & Redesign (Q5 & Q7)

1. **Q: Compare trial division and Sieve of Eratosthenes in time and space.**
   **A:** Trial division uses $O(1)$ space and $O(\sqrt{n})$ time per query. Sieve of Eratosthenes uses $O(N)$ space (`1 MB` for $N = 10^6+3$) and $O(N \log \log N)$ preprocessing time, answering subsequent primality queries in $O(1)$ time.
2. **Q: Why does the inner loop of the Sieve start at `p * p` rather than `2 * p`?**
   **A:** Every composite multiple $k \cdot p$ with $k < p$ has a prime factor $\le k < p$, so it has already been marked during an earlier iteration.
3. **Q: How did our Task 7 redesign reduce divisor checks for `1,000,003` from `1,000,001` to `500`?**
   **A:** First, restricting divisors to $\sqrt{n}$ reduced checks from `1,000,001` to `999`. Second, checking divisibility by `2` once and then stepping only through odd divisors (`i = 3, 5, 7, ..., 999`) halved the remaining candidates (`1 + 499 = 500` checks).
4. **Q: Why did we count `checks++` only before `n % i == 0` and not on `n < 2`?**
   **A:** Because the problem specifically measures *modulo division* operations (`%`), which are the costly arithmetic operations inside the loop, whereas `n < 2` is a single comparison.
5. **Q: What does Big-O notation measure, and what does it ignore?**
   **A:** Big-O describes the asymptotic upper bound on how operation count or memory scales as input size $n \to \infty$, ignoring constant factors and lower-order terms. In Task 7, both `sqrt(n)` and `sqrt(n)/2` are $O(\sqrt{n})$, yet the constant factor of $0.5$ cuts actual CPU work in half.
6. **Q: Why is a redesign that doesn't improve speed still valuable if properly analyzed?**
   **A:** Engineering evaluation requires honest evidence: if a redesign introduces memory overhead, branch mispredictions, or cache misses that outweigh theoretical operation savings, documenting that trade-off prevents deploying a worse system.
7. **Q: When would the original brute-force prime checker still be acceptable?**
   **A:** For tiny inputs ($n < 50$) executed infrequently in teaching contexts where code simplicity is prioritized over asymptotic efficiency.
8. **Q: How could Task 7 be extended further using wheel factorization?**
   **A:** By checking divisibility by `2` and `3` upfront and testing only candidates of the form $6k \pm 1$ (`5, 7, 11, 13, ...`), reducing checks to $\approx \sqrt{n}/3$ (`~333` divisions for `1,000,003`).
