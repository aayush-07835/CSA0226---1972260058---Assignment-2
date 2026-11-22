# Structured Pseudocode — CSA02 Assignment 2 (CO2)

## Q1: Corrected Pharmacy Billing
```text
FUNCTION ComputeNetBill(unit_price, quantity, is_senior)
    IF unit_price < 0 OR quantity <= 0 THEN
        RETURN 0.0
    END IF
    gross <- unit_price * quantity
    IF is_senior != 0 THEN
        discount <- gross * 0.15
    ELSE
        discount <- 0.0
    END IF
    taxable <- gross - discount
    gst <- taxable * 0.05
    total <- taxable + gst
    IF total > 1000.0 THEN
        net <- total - 50.0
    ELSE
        net <- total
    END IF
    RETURN net
END FUNCTION
```

## Q2: Short-Circuit Railway Concession
```text
FUNCTION CheckConcession(passenger, audit_mode)
    IF audit_mode == TRUE THEN
        // Must call verify first so audit log is never skipped
        RETURN VerifyDisabilityCard(passenger) OR (passenger.is_senior AND passenger.is_eligible_class)
    ELSE
        // Place cheap memory checks before slow network call
        RETURN (passenger.is_senior AND passenger.is_eligible_class) OR VerifyDisabilityCard(passenger)
    END IF
END FUNCTION
```

## Q3: Bitwise Register Operations
```text
FUNCTION SwitchOn(reg, dev)   -> RETURN reg BITWISE_OR (1 << dev)
FUNCTION SwitchOff(reg, dev)  -> RETURN reg BITWISE_AND (BITWISE_NOT (1 << dev))
FUNCTION Toggle(reg, dev)     -> RETURN reg BITWISE_XOR (1 << dev)
FUNCTION IsOn(reg, dev)       -> RETURN (reg >> dev) BITWISE_AND 1
```

## Q4: Grade & Scholarship Classifier
```text
FUNCTION GetGrade(marks)
    IF marks < 0 OR marks > 100 THEN
        RETURN '?'
    END IF
    SWITCH (marks DIV 10)
        CASE 10, 9: RETURN 'S'
        CASE 8:     RETURN 'A'
        CASE 7:     RETURN 'B'
        CASE 6:     RETURN 'C'
        CASE 5:     RETURN 'D'
        DEFAULT:    RETURN 'F'
    END SWITCH
END FUNCTION
```

## Q5: Prime Verification (do-while with Edge Guards)
```text
FUNCTION IsPrimeDoWhile(n)
    checks <- 0
    IF n < 2 THEN RETURN FALSE
    IF n == 2 OR n == 3 THEN RETURN TRUE
    i <- 2
    DO
        checks <- checks + 1
        IF (n MOD i) == 0 THEN
            RETURN FALSE
        END IF
        i <- i + 1
    WHILE (i * i <= n)
    RETURN TRUE
END FUNCTION
```

## Q6: Micro-Loan Amortization Loop
```text
FUNCTION SimulateLoan(principal, monthly_rate, fixed_emi)
    balance <- principal
    months <- 0
    total_interest <- 0.0
    WHILE balance > 1e-6 DO
        IF months >= 360 THEN
            PRINT "Safety limit (360 months) reached. Loan non-amortizing or excessive tenure."
            BREAK
        END IF
        months <- months + 1
        interest <- balance * monthly_rate
        due <- balance + interest
        IF fixed_emi >= due - 1e-6 THEN
            payment <- due
            balance <- 0.0
        ELSE
            payment <- fixed_emi
            balance <- due - payment
        END IF
        total_interest <- total_interest + interest
    END WHILE
    RETURN (months, total_interest)
END FUNCTION
```

## Q7: Redesigned Prime Verification
```text
FUNCTION IsPrimeRedesigned(n)
    checks <- 0
    IF n < 2 THEN RETURN FALSE
    IF n == 2 THEN RETURN TRUE
    checks <- checks + 1
    IF (n MOD 2) == 0 THEN RETURN FALSE
    i <- 3
    WHILE i <= (n DIV i) DO
        checks <- checks + 1
        IF (n MOD i) == 0 THEN
            RETURN FALSE
        END IF
        i <- i + 2
    END WHILE
    RETURN TRUE
END FUNCTION
```
