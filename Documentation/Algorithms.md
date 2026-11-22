# Algorithms Specification — CSA02 Assignment 2 (CO2)

## Algorithm 1: Jan Aushadhi Pharmacy Billing (`Q1_Corrected`)
1. **Input:** `unit_price` (real), `quantity` (integer), `is_senior` (boolean flag).
2. **Validate:** If `unit_price < 0` or `quantity <= 0`, return `0.0`.
3. **Compute Gross:** `gross = unit_price * quantity`.
4. **Apply Senior Discount:** If `is_senior != 0`, `discount = 0.15 * gross`; else `discount = 0.0`.
5. **Compute Taxable Value & GST:** `taxable = gross - discount`; `gst = 0.05 * taxable`; `total = taxable + gst`.
6. **Apply Promotional Threshold:** If `total > 1000.0`, `net = total - 50.0`; else `net = total`.
7. **Output:** `total` and `net`.

## Algorithm 2: Short-Circuit Railway Concession Check (`Q2_Main`)
1. **Input:** Passenger record `(is_senior, is_eligible_class, has_disability)`, `audit_required`.
2. **Mode A (Throughput-Optimal, No Mandatory Audit):**
   - Evaluate `(is_senior && is_eligible_class) || verify_disability_card(p)`.
   - If `is_senior` is false, skip `is_eligible_class`. If both are true, skip `verify_disability_card(p)`.
3. **Mode B (Audit-Complete):**
   - Evaluate `verify_disability_card(p) || (is_senior && is_eligible_class)` so the audit log records every passenger before any short-circuit occurs.

## Algorithm 3: Bitwise Smart-Home Device Register (`Q3_Main`)
- **Set bit `dev` (`switch_on`):** `reg = reg | (1u << dev)`
- **Clear bit `dev` (`switch_off`):** `reg = reg & ~(1u << dev)`
- **Flip bit `dev` (`toggle`):** `reg = reg ^ (1u << dev)`
- **Query bit `dev` (`is_on`):** `return (reg >> dev) & 1u`
- **Count active devices:** Iterate `bit = 0..7`, accumulate `(reg >> bit) & 1u`.

## Algorithm 4: Bucketed Grade & 2D Scholarship Classifier (`Q4_Switch`, `Q4_Scholarship`)
1. **Validate Marks:** If `marks < 0 || marks > 100`, return `'?'`.
2. **Bucket Index:** Compute `bucket = marks / 10` (`0..10`).
3. **Map Grade:** `10, 9 -> 'S'`, `8 -> 'A'`, `7 -> 'B'`, `6 -> 'C'`, `5 -> 'D'`, `0..4 -> 'F'`.
4. **Scholarship Lookup:** Map grade to row `0..5` and family income to column `0..3`, returning `SCHOLARSHIP_MATRIX[row][col]` in $O(1)$ time.

## Algorithm 5: Square-Root Trial Division & Sieve of Eratosthenes (`Q5`)
- **Trial Division:** Reject $n < 2$. For $i = 2$ while $i^2 \le n$: increment `checks`; if $n \bmod i = 0$, return `0`. Return `1`.
- **Sieve of Eratosthenes:** Allocate boolean array `is_prime[0..N]` initialized to `1` (`0` and `1` set to `0`). For $p = 2 \dots \lfloor\sqrt{N}\rfloor$, if `is_prime[p]` is `1`, mark multiples $p^2, p^2 + p, \dots \le N$ as `0`.

## Algorithm 6: Safe Micro-Loan Amortization Simulator (`Q6_Loan_Schedule`)
1. **Initialize:** `balance = principal`, `months = 0`, `total_interest = 0.0`.
2. **Loop:** While `balance > 1e-6`:
   - If `months >= 360`, set `hit_safety_limit = 1` and `break`.
   - Increment `months`; `interest = balance * monthly_rate`; `due = balance + interest`.
   - `payment = (fixed_repayment >= due - 1e-6) ? due : fixed_repayment`.
   - `balance = due - payment`; `total_interest += interest`.
3. **Output:** Schedule rows, `months`, and `total_interest`.

## Algorithm 7: Parity-Filtered Odd-Only Prime Checker (`Q7_Redesigned`)
1. If $n < 2$, return `0`. If $n = 2$, return `1`.
2. Increment `checks`; if $n \bmod 2 = 0$, return `0`.
3. For $i = 3$ while $i \le \lfloor n / i \rfloor$ stepping by $2$: increment `checks`; if $n \bmod i = 0$, return `0`.
4. Return `1`.
