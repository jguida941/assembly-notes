# Assembly Notes: Conditionals and Loops

I rewrote this section in my own words so each assembly instruction explains what it is doing.

The main things I care about:

- Conditionals compare values and jump based on the result.
- Loops are built from labels, comparisons, jumps, and increments.
- Labels like `.L2` and `.L3` are places in the code that assembly can jump to.
- `cmp` compares values.
- `jle`, `jg`, `je`, etc. decide where to jump after a comparison.

## Table of Contents

- [1. Big Idea](#1-big-idea)
- [2. Relational Operators](#2-relational-operators)
- [3. Conditional Example](#3-conditional-example)
- [4. String Labels](#4-string-labels)
- [5. Variable Layout](#5-variable-layout)
- [6. Assembly Breakdown: Read `a`](#6-assembly-breakdown-read-a)
- [7. Assembly Breakdown: Read `b`](#7-assembly-breakdown-read-b)
- [8. Load Values for Comparison](#8-load-values-for-comparison)
- [9. Compare `a` and `b`](#9-compare-a-and-b)
- [10. Conditional Jump](#10-conditional-jump)
- [11. If Block: Print First Message](#11-if-block-print-first-message)
- [12. Else Label](#12-else-label)
- [13. Else Block: Print Second Message](#13-else-block-print-second-message)
- [14. End Label](#14-end-label)
- [15. Full Conditional Assembly With Comments](#15-full-conditional-assembly-with-comments)
- [16. Conditional Summary](#16-conditional-summary)
- [17. Why Check `a <= b` If C++ Says `a > b`?](#17-why-check-a--b-if-c-says-a--b)
- [18. Loops Big Idea](#18-loops-big-idea)
- [19. Loop C++ Code](#19-loop-c-code)
- [20. Loop Variable Layout](#20-loop-variable-layout)
- [21. Loop Assembly](#21-loop-assembly)
- [22. Loop Breakdown](#22-loop-breakdown)
- [23. Loop State Walkthrough](#23-loop-state-walkthrough)
- [24. Loop Summary](#24-loop-summary)
- [25. Conditionals and Loops Main Summary](#25-conditionals-and-loops-main-summary)

---

# 1. Big Idea

In C++, conditionals look like this:

```cpp
if (a > b)
{
    cout << "First number larger than second number";
}
else
{
    cout << "Second number larger than first number";
}
```

In assembly, this becomes:

```text
read a
read b
compare a and b
jump to a label if the condition says to
print one string
jump over the else block
print the other string if needed
end
```

Assembly does not have an `if` block the same way C++ does.

Instead, assembly uses:

```text
comparison + jump
```

---

# 2. Relational Operators

These are common conditional jumps:

```text
C++ operator     Assembly jump      Meaning

==               je                 jump if equal
>                jg                 jump if greater
<                jl                 jump if less
>=               jge                jump if greater or equal
<=               jle                jump if less or equal
!=               jne                jump if not equal
```

Important:

```text
The jump happens after a comparison.
```

So this pattern:

```asm
cmpl %eax, %edx
jle .L2
```

means:

```text
Compare edx and eax.
If edx is less than or equal to eax, jump to label .L2.
```

For this class, I am reading:

```asm
cmpl %eax, %edx
```

as:

```text
compare edx against eax
```

And:

```asm
jle .L2
```

as:

```text
if edx <= eax, jump to .L2
```

---

# 3. Conditional Example

## C++ Code

```cpp
int a, b;

cin >> a;
cin >> b;

if (a > b)
{
    cout << "First number larger than second number";
}
else
{
    cout << "Second number larger than first number";
}
```

---

# 4. String Labels

The program has two messages.

```asm
.LC1:
.string "First Number larger than second number"

.LC2:
.string "Second number larger than first number"
```

Plain English:

```text
.LC1 is the first message.
.LC2 is the second message.
```

So:

```text
.LC1 = "First Number larger than second number"
.LC2 = "Second number larger than first number"
```

---

# 5. Variable Layout

For this example:

```text
-8(%rbp) = a
-4(%rbp) = b
```

So:

```text
a lives at -8(%rbp)
b lives at -4(%rbp)
```

---

# 6. Assembly Breakdown: Read `a`

```asm
# Get a's memory address.
# rax now holds the location where a is stored, not a's value.
leaq -8(%rbp), %rax

# Put a's address where cin expects the input destination: rsi.
# rsi now also holds the address of a.
movq %rax, %rsi

# Put the input format/string address where cin expects it.
# For this class example, LC0 is used by the input call.
movl $.LC0, %edi

# Set eax to 0 for this function-call pattern.
# This is not part of the input value.
movl $0, %eax

# Read user input and store it into the address in rsi.
# Since rsi holds a's address, this writes into a.
call __isoc99_cin
```

Plain English:

```text
cin >> a;
```

---

# 7. Assembly Breakdown: Read `b`

```asm
# Get b's memory address.
# rax now holds the location where b is stored, not b's value.
leaq -4(%rbp), %rax

# Put b's address where cin expects the input destination: rsi.
# rsi now also holds the address of b.
movq %rax, %rsi

# Put the input format/string address where cin expects it.
movl $.LC0, %edi

# Set eax to 0 for this function-call pattern.
movl $0, %eax

# Read user input and store it into the address in rsi.
# Since rsi holds b's address, this writes into b.
call __isoc99_cin
```

Plain English:

```text
cin >> b;
```

---

# 8. Load Values for Comparison

```asm
# Copy a's value into edx.
# a lives at -8(%rbp).
# edx now holds a.
movl -8(%rbp), %edx

# Copy b's value into eax.
# b lives at -4(%rbp).
# eax now holds b.
movl -4(%rbp), %eax
```

At this point:

```text
edx = a
eax = b
```

---

# 9. Compare `a` and `b`

```asm
# Compare a and b.
# edx holds a.
# eax holds b.
# This comparison is used by the next jump.
cmpl %eax, %edx
```

For this class example:

```text
cmpl %eax, %edx
```

means:

```text
compare edx against eax
compare a against b
```

So the next jump can decide:

```text
is a <= b?
```

---

# 10. Conditional Jump

```asm
# If a <= b, jump to .L2.
# .L2 is the else block.
# This means if a is NOT greater than b, go print the second message.
jle .L2
```

This is the key idea:

```cpp
if (a > b)
```

Assembly can implement this by checking the opposite:

```text
if a <= b, jump to else
```

So:

```asm
jle .L2
```

means:

```text
if a <= b, skip the first-message block and go to the else block
```

---

# 11. If Block: Print First Message

This code runs only if the jump did **not** happen.

That means:

```text
a > b
```

So this is the `if` block.

```asm
# Put the address of the first message into edi.
# puts expects the string address in edi.
movl $.LC1, %edi

# Print the first message.
call puts
```

Plain English:

```text
cout << "First Number larger than second number";
```

Then:

```asm
# Jump to .L3 so we skip the else block.
# Without this jump, the program would continue into .L2 and print both messages.
jmp .L3
```

Plain English:

```text
After printing the if-message, skip the else-message.
```

---

# 12. Else Label

```asm
.L2:
```

Plain English:

```text
This is the else block.
The program jumps here when a <= b.
```

---

# 13. Else Block: Print Second Message

```asm
# Put the address of the second message into edi.
# puts expects the string address in edi.
movl $.LC2, %edi

# Print the second message.
call puts
```

Plain English:

```text
cout << "Second number larger than first number";
```

---

# 14. End Label

```asm
.L3:
```

Plain English:

```text
This is the end of the if/else statement.
Both branches meet here.
```

Then:

```asm
# Set eax to 1 for this class's return pattern.
movl $1, %eax

# Clean up the function stack frame.
leave

# Return from main.
ret
```

---

# 15. Full Conditional Assembly With Comments

```asm
.section .rodata

.LC0:
.string "%d"

.LC1:
.string "First Number larger than second number"

.LC2:
.string "Second number larger than first number"


# Read a

# Get a's memory address.
# rax now holds a's address.
leaq -8(%rbp), %rax

# Put a's address where cin expects the input destination.
movq %rax, %rsi

# Put input format/string address where the input call expects it.
movl $.LC0, %edi

# Function-call setup.
movl $0, %eax

# Read input into a.
call __isoc99_cin


# Read b

# Get b's memory address.
# rax now holds b's address.
leaq -4(%rbp), %rax

# Put b's address where cin expects the input destination.
movq %rax, %rsi

# Put input format/string address where the input call expects it.
movl $.LC0, %edi

# Function-call setup.
movl $0, %eax

# Read input into b.
call __isoc99_cin


# Compare a and b

# Copy a's value into edx.
# edx = a.
movl -8(%rbp), %edx

# Copy b's value into eax.
# eax = b.
movl -4(%rbp), %eax

# Compare a and b.
# This sets up the next jump.
cmpl %eax, %edx

# If a <= b, jump to the else block.
jle .L2


# If block: a > b

# Print the first message.
movl $.LC1, %edi
call puts

# Skip the else block after printing the first message.
jmp .L3


# Else block: a <= b
.L2:

# Print the second message.
movl $.LC2, %edi
call puts


# End of if/else.
.L3:

# Return/cleanup pattern.
movl $1, %eax
leave
ret
```

---

# 16. Conditional Summary

```text
a lives at -8(%rbp)
b lives at -4(%rbp)

edx = a
eax = b

cmpl %eax, %edx
compare a against b

jle .L2
if a <= b, jump to else

if no jump happened:
a > b
print first message
jump to end

.L2:
print second message

.L3:
end
```

---

# 17. Why Check `a <= b` If C++ Says `a > b`?

C++ says:

```cpp
if (a > b)
```

But assembly does:

```asm
jle .L2
```

That means:

```text
if a <= b, jump to else
```

This is the opposite condition.

That makes sense because the assembly is saying:

```text
If the if-condition is false, jump to the else block.
```

So:

```text
a > b is the if condition
a <= b is the false case
```

---

# 18. Loops Big Idea

C++ loop:

```cpp
for (i = 0; i < 10; i++)
{
    cout << i;
}
```

Plain English:

```text
Set i to 0.
Check if i is still inside the loop range.
If yes, print i.
Add 1 to i.
Go back and check again.
Stop when i is too large.
```

Assembly does this with:

```text
labels
jumps
comparison
increment
```

---

# 19. Loop C++ Code

```cpp
int i;

for (i = 0; i < 10; i++)
{
    cout << i;
}
```

Expected output:

```text
0123456789
```

---

# 20. Loop Variable Layout

```text
-4(%rbp) = i
```

---

# 21. Loop Assembly

```asm
# Initialize i to 0.
# i lives at -4(%rbp).
movl $0, -4(%rbp)

# Jump to the condition check first.
# This makes sure the loop checks the boundary before printing.
jmp .L2


# Loop body.
.L3:

# Copy i's value into eax.
# eax now holds i.
movl -4(%rbp), %eax

# Put i's value where cout expects the value to print: esi.
# esi now holds i.
movl %eax, %esi

# Put output format/string address where the output call expects it.
movl $.LC0, %edi

# Function-call setup.
movl $0, %eax

# Print i.
call cout

# Increment i by 1.
# i = i + 1.
addl $1, -4(%rbp)


# Condition check.
.L2:

# Compare i with 9.
# This asks whether i is still <= 9.
cmpl $9, -4(%rbp)

# If i <= 9, jump back to the loop body.
jle .L3
```

---

# 22. Loop Breakdown

```asm
movl $0, -4(%rbp)
```

Means:

```text
i = 0
```

---

```asm
jmp .L2
```

Means:

```text
jump to the condition check before running the loop body
```

This is why the program checks the loop condition before printing.

---

```asm
.L3:
```

Means:

```text
this is the loop body label
```

If the loop condition passes, the program jumps here.

---

```asm
movl -4(%rbp), %eax
```

Means:

```text
eax = i
```

---

```asm
movl %eax, %esi
```

Means:

```text
esi = i
```

`cout` uses `esi` as the integer value to print.

---

```asm
movl $.LC0, %edi
```

Means:

```text
put the output format/string address into edi
```

---

```asm
movl $0, %eax
```

Means:

```text
function-call setup
```

This is not part of the loop math.

---

```asm
call cout
```

Means:

```text
print i
```

---

```asm
addl $1, -4(%rbp)
```

Means:

```text
i = i + 1
```

This adds 1 directly to the memory slot for `i`.

---

```asm
.L2:
```

Means:

```text
this is the condition-check label
```

---

```asm
cmpl $9, -4(%rbp)
```

Means:

```text
compare i with 9
```

For this loop, it is checking:

```text
is i <= 9?
```

This is how the compiler represents:

```cpp
i < 10
```

as:

```text
i <= 9
```

Same meaning for integers.

---

```asm
jle .L3
```

Means:

```text
if i <= 9, jump back to the loop body
```

If the jump happens, the loop continues.

If the jump does not happen, the loop ends.

---

# 23. Loop State Walkthrough

Start:

```text
i = 0
```

Check:

```text
is i <= 9?
```

If yes:

```text
print i
i = i + 1
go check again
```

The loop runs like this:

```text
i = 0 → print 0 → i becomes 1
i = 1 → print 1 → i becomes 2
i = 2 → print 2 → i becomes 3
i = 3 → print 3 → i becomes 4
i = 4 → print 4 → i becomes 5
i = 5 → print 5 → i becomes 6
i = 6 → print 6 → i becomes 7
i = 7 → print 7 → i becomes 8
i = 8 → print 8 → i becomes 9
i = 9 → print 9 → i becomes 10
i = 10 → condition fails because 10 <= 9 is false
```

So output is:

```text
0123456789
```

---

# 24. Loop Summary

```text
-4(%rbp) = i

movl $0, -4(%rbp)
i = 0

jmp .L2
go check the loop condition first

.L3
loop body starts here

movl -4(%rbp), %eax
eax = i

movl %eax, %esi
esi = i, ready for printing

call cout
print i

addl $1, -4(%rbp)
i = i + 1

.L2
condition check starts here

cmpl $9, -4(%rbp)
compare i with 9

jle .L3
if i <= 9, jump back to the loop body
```

---

# 25. Conditionals and Loops Main Summary

```text
Conditionals use comparison and jumps.

cmpl compares values.

Jump instructions like jle, jg, je, jne decide where to go next.

Labels like .L2 and .L3 mark places in the code.

For if/else:
- compare values
- jump to else if the if-condition is false
- print/run the if block over the else block
- both branches meet at the end label

For loops:
- initialize the counter
- jump to the condition check
- if condition passes, jump to the loop body
- run the body
- increment the counter
- check again
- stop when the condition fails
```
