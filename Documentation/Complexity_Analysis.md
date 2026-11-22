# Asymptotic Time & Space Complexity Comparison (Q1–Q7)

| Question | Primary Approach | Alternative Approach | Time Complexity (Primary vs Alt) | Space Complexity (Primary vs Alt) |
| :--- | :--- | :--- | :--- | :--- |
| **Q1** | Single-expression billing (`Q1_Corrected`) | Step-by-step intermediate variables (`Q1_Alternative`) | $O(1)$ vs $O(1)$ (identical arithmetic op count; compiler registers eliminate extra reads) | $O(1)$ vs $O(1)$ (+40 bytes stack struct in unoptimized `-O0`) |
| **Q2** | Short-circuit `&&` / `||` & Nested `if` | Non-short-circuit bitwise `&` / `|` | $\Theta(n)$ with $n(1 - p_s p_c)$ slow calls vs $\Theta(n)$ with $n$ slow calls ($100\%$) | $O(1)$ auxiliary vs $O(1)$ auxiliary |
| **Q3** | Bit-packed `unsigned char` (1 byte) | Byte array `char state[8]` (8 bytes) | Bit op: $O(1)$; Count ON: $O(w)$ ($w=8$ bits) vs Array op: $O(1)$; Count ON: $O(8)$ | $1\text{ B/home}$ ($1\text{ MB}$ for $10^6$ homes) vs $8\text{ B/home}$ ($8\text{ MB}$ for $10^6$ homes) |
| **Q4** | `else-if` ladder / `switch(marks/10)` | Lookup table `grades[11]` | `else-if`: $O(k)$ ($k=7$ checks); `switch`: $O(1)$ jump table; Lookup: $O(1)$ | $O(1)$ vs $11\text{ bytes}$ static `.rodata` |
| **Q5** | Trial division up to $\sqrt{n}$ | Sieve of Eratosthenes up to $N$ | Trial: $O(\sqrt{n})$ per query vs Sieve: $O(N \log \log N)$ precompute + $O(1)$ per query | $O(1)$ vs $O(N)$ ($1,000,004\text{ bytes}$ for $N=10^6+3$) |
| **Q6** | Iterative monthly simulation | Closed-form annuity log formula | Simulation: $O(M)$ ($M$ months, bounded by $360$) vs Formula: $O(1)$ (`log()` calls) | $O(1)$ vs $O(1)$ |
| **Q7** | Brute-force trial division ($2 \dots n-1$) | Parity-filtered odd-only $\sqrt{n}$ checker | Original: $O(n)$ ($1,000,001$ divs) vs Redesigned: $O(\sqrt{n}/2)$ ($500$ divs for $n=10^6+3$) | $O(1)$ vs $O(1)$ |
