# Assembly Notes: Generate Assembly, Write C++ From Assembly, and Code Security

I rewrote this section in my own words so the process is easier to follow.

The main things I care about:

- How to generate assembly from C++ using `g++ -S`.
- How to read assembly and translate it back into C++.
- How to track register state line by line.
- How code security connects to reverse engineering.
- How unsafe code can create crashes, leaks, or vulnerabilities.

## Table of Contents

- [1. Generating Assembly From C++ Code](#1-generating-assembly-from-c-code)
- [2. Example C++ Code](#2-example-c-code)
- [3. Example Assembly Output](#3-example-assembly-output)
- [4. What I Actually Need to Understand](#4-what-i-actually-need-to-understand)
- [5. String Storage](#5-string-storage)
- [6. Printing the String](#6-printing-the-string)
- [7. Generate Assembly Command Summary](#7-generate-assembly-command-summary)
- [8. Writing C++ From Assembly](#8-writing-c-from-assembly)
- [9. Variable Layout](#9-variable-layout)
- [10. Assembly to C++ Breakdown](#10-assembly-to-c-breakdown)
- [11. Assembly State Summary](#11-assembly-state-summary)
- [12. C++ Meaning](#12-c-meaning)
- [13. Important Assembly Patterns](#13-important-assembly-patterns)
- [14. Reverse-Engineering Rule](#14-reverse-engineering-rule)
- [15. Code Security Big Idea](#15-code-security-big-idea)
- [16. Common Security Issue: Buffer Overflow](#16-common-security-issue-buffer-overflow)
- [17. Common Security Issue: Uninitialized Variables](#17-common-security-issue-uninitialized-variables)
- [18. Common Security Issue: Ignoring Errors](#18-common-security-issue-ignoring-errors)
- [19. Common Security Issue: Dangling Pointers](#19-common-security-issue-dangling-pointers)
- [20. Security Practices](#20-security-practices)
- [21. Secure Coding Checklist](#21-secure-coding-checklist)
- [22. Clean Room Reverse Engineering](#22-clean-room-reverse-engineering)
- [23. Corporate Security Big Idea](#23-corporate-security-big-idea)
- [24. Security by Design](#24-security-by-design)
- [25. Code Testing and Maintenance](#25-code-testing-and-maintenance)
- [26. Deployment / Pushing Code](#26-deployment--pushing-code)
- [27. Main Summary](#27-main-summary)

---

# 1. Generating Assembly From C++ Code

The compiler can turn C++ source code into assembly.

The command is:

```bash
g++ -S Hello.cpp
```

Important:

```text
-S must be uppercase.
There is a dash before S.
There must be a space between g++ and -S.
```

This command creates an assembly file:

```text
Hello.s
```

So the flow is:

```text
Hello.cpp  ->  g++ -S Hello.cpp  ->  Hello.s
```

Plain English:

```text
Take the C++ file and generate assembly output instead of a normal executable.
```

---

# 2. Example C++ Code

```cpp
#include <iostream>
using namespace std;

int main()
{
    cout << "Welcome to my world";
    return 0;
}
```

Plain English:

```text
Print the string "Welcome to my world".
Return from main.
```

---

# 3. Example Assembly Output

```asm
.file "Hello.c"

.section .rodata
.LC0:
.string "Welcome to my world"

.text
.globl main
.type main, @function

main:
.LFB2:
.cfi_startproc

pushq %rbp
.cfi_def_cfa_offset 16
.cfi_offset 6, -16
movq %rsp, %rbp
.cfi_def_cfa_register 6

movl $.LC0, %edi
call puts

movl $1, %eax
popq %rbp
.cfi_def_cfa 7, 8
ret

.cfi_endproc
.LFE2:
.size main, .-main
.ident "g++ : (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
.section .note.GNU-stack,"",@progbits
```

---

# 4. What I Actually Need to Understand

Most of the assembly file is compiler skeleton.

The important program logic is:

```asm
.LC0:
.string "Welcome to my world"

movl $.LC0, %edi
call puts
```

Plain English:

```text
Create a string named .LC0.
Put the address of .LC0 into edi.
Call puts to print the string.
```

---

# 5. String Storage

```asm
.section .rodata
```

Means:

```text
Start the read-only data section.
This is where constant strings are stored.
```

---

```asm
.LC0:
```

Means:

```text
Create a label named .LC0.
```

A label is like a name for a memory location.

---

```asm
.string "Welcome to my world"
```

Means:

```text
Store the string "Welcome to my world" at label .LC0.
```

So this block:

```asm
.LC0:
.string "Welcome to my world"
```

means:

```text
.LC0 = "Welcome to my world"
```

---

# 6. Printing the String

```asm
movl $.LC0, %edi
```

Means:

```text
Put the address of the string .LC0 into edi.
```

Why?

```text
puts expects the string address in edi.
```

Then:

```asm
call puts
```

Means:

```text
Print the string whose address is in edi.
```

So:

```asm
movl $.LC0, %edi
call puts
```

means:

```cpp
cout << "Welcome to my world";
```

At this class level, I read it as:

```text
Give puts the string location.
Call puts to print it.
```

---

# 7. Generate Assembly Command Summary

```bash
g++ -S Hello.cpp
```

Means:

```text
Generate assembly from Hello.cpp.
```

Output:

```text
Hello.s
```

If I open `Hello.s`, I should see assembly code.

Important command pieces:

```text
g++       = C++ compiler
-S        = generate assembly
Hello.cpp = source file
Hello.s   = output assembly file
```

---

# 8. Writing C++ From Assembly

When writing C++ from assembly, there is not always a one-to-one match.

One C++ line can become many assembly lines.

Example assembly:

```asm
movl -8(%rbp), %eax
sall $2, %eax
subl $1, %eax
leal 7(%rax), %edx
testl %eax, %eax
cmovs %edx, %eax
sarl $3, %eax
movl %eax, -4(%rbp)
```

Possible C++ meaning:

```cpp
int input;
int output = (((input * 4) - 1) / 8);
```

The important thing is to track how the value changes line by line.

---

# 9. Variable Layout

For this example:

```text
-8(%rbp) = input
-4(%rbp) = output
```

So:

```text
input lives at -8(%rbp)
output lives at -4(%rbp)
```

---

# 10. Assembly to C++ Breakdown

```asm
movl -8(%rbp), %eax
```

Comment:

```asm
# Copy input's value into eax.
# input lives at -8(%rbp).
# eax now holds input.
movl -8(%rbp), %eax
```

Plain English:

```text
eax = input
```

---

```asm
sall $2, %eax
```

Comment:

```asm
# Shift eax left by 2 bits.
# Shifting left by 2 is the same as multiplying by 4.
# eax now holds input * 4.
sall $2, %eax
```

Plain English:

```text
eax = input * 4
```

---

```asm
subl $1, %eax
```

Comment:

```asm
# Subtract 1 from eax.
# eax now holds (input * 4) - 1.
subl $1, %eax
```

Plain English:

```text
eax = (input * 4) - 1
```

---

```asm
leal 7(%rax), %edx
```

Comment:

```asm
# Calculate eax + 7 and store that calculated value in edx.
# edx now holds eax + 7.
leal 7(%rax), %edx
```

Plain English:

```text
edx = eax + 7
```

Important note:

```text
leal can calculate address-style expressions.
Here, it is being used as math.
```

So:

```asm
leal 7(%rax), %edx
```

means:

```text
edx = rax + 7
```

---

```asm
testl %eax, %eax
```

Comment:

```asm
# Test eax against itself.
# This sets CPU flags based on eax.
# It does not change eax.
testl %eax, %eax
```

Plain English:

```text
Check whether eax is negative, zero, or positive.
```

This prepares for the next conditional instruction.

---

```asm
cmovs %edx, %eax
```

Comment:

```asm
# Conditional move if signed negative.
# If the previous test says eax is negative, copy edx into eax.
# If eax is not negative, leave eax alone.
cmovs %edx, %eax
```

Plain English:

```text
if eax is negative:
    eax = edx
else:
    eax stays the same
```

This is extra compiler logic for signed integer division behavior.

---

```asm
sarl $3, %eax
```

Comment:

```asm
# Shift eax right by 3 bits.
# Shifting right by 3 is like dividing by 8.
# eax now holds the final result.
sarl $3, %eax
```

Plain English:

```text
eax = eax / 8
```

---

```asm
movl %eax, -4(%rbp)
```

Comment:

```asm
# Store eax into output's memory slot.
# output lives at -4(%rbp).
# output now holds the final result.
movl %eax, -4(%rbp)
```

Plain English:

```text
output = eax
```

---

# 11. Assembly State Summary

```text
input lives at -8(%rbp)
output lives at -4(%rbp)

eax = input
eax = input * 4
eax = (input * 4) - 1

edx = eax + 7

test eax
if eax is negative:
    eax = edx

eax = eax / 8

output = eax
```

---

# 12. C++ Meaning

High-level C++ idea:

```cpp
int input;
int output = (((input * 4) - 1) / 8);
```

The core logic is:

```text
Take input.
Multiply it by 4.
Subtract 1.
Divide by 8.
Store the answer in output.
```

The assembly has extra lines:

```asm
leal 7(%rax), %edx
testl %eax, %eax
cmovs %edx, %eax
```

Those are compiler-generated details for signed division behavior.

For beginner understanding:

```text
Do not panic if one C++ expression becomes many assembly lines.
Track the register state line by line.
```

---

# 13. Important Assembly Patterns

## `sall`

```asm
sall $2, %eax
```

Means:

```text
shift eax left by 2 bits
```

For integer math:

```text
left shift by 1 = multiply by 2
left shift by 2 = multiply by 4
left shift by 3 = multiply by 8
```

So:

```asm
sall $2, %eax
```

means:

```text
eax = eax * 4
```

---

## `sarl`

```asm
sarl $3, %eax
```

Means:

```text
shift eax right by 3 bits
```

For integer math:

```text
right shift by 1 = divide by 2
right shift by 2 = divide by 4
right shift by 3 = divide by 8
```

So:

```asm
sarl $3, %eax
```

means:

```text
eax = eax / 8
```

---

## `testl`

```asm
testl %eax, %eax
```

Means:

```text
test eax against itself
```

This does not store a result.

It sets CPU flags for later instructions.

For this example, it helps decide whether `eax` is negative.

---

## `cmovs`

```asm
cmovs %edx, %eax
```

Means:

```text
conditional move if signed negative
```

Plain English:

```text
if the previous test says the value is negative:
    eax = edx
else:
    eax stays the same
```

---

# 14. Reverse-Engineering Rule

When writing C++ from assembly, use this method:

```text
1. Make a variable layout table.
2. Track each register after every line.
3. Translate each instruction into plain English.
4. Combine the plain-English steps into C++.
```

Example tracking table:

```text
Instruction              Register State

movl -8(%rbp), %eax      eax = input
sall $2, %eax            eax = input * 4
subl $1, %eax            eax = (input * 4) - 1
leal 7(%rax), %edx       edx = eax + 7
testl %eax, %eax         flags set from eax
cmovs %edx, %eax         if eax negative, eax = edx
sarl $3, %eax            eax = eax / 8
movl %eax, -4(%rbp)      output = eax
```

---

# 15. Code Security Big Idea

Code security means writing code so bad input, invalid memory, or unsafe assumptions do not break the program.

Security problems happen when code assumes:

```text
the user enters valid input
memory is always safe
pointers always point somewhere valid
errors can be ignored
```

Those assumptions are dangerous.

---

# 16. Common Security Issue: Buffer Overflow

A buffer overflow happens when code accesses memory outside the valid range.

Example:

```cpp
int numbers[5];

cout << numbers[5];
```

Problem:

```text
numbers[5] is outside the valid range.
```

For an array with 5 elements, valid indexes are:

```text
numbers[0]
numbers[1]
numbers[2]
numbers[3]
numbers[4]
```

Invalid:

```text
numbers[5]
```

Why?

```text
Array indexes start at 0.
A 5-element array ends at index 4.
```

Security risk:

```text
Reading or writing outside the array can crash the program or expose memory.
```

---

# 17. Common Security Issue: Uninitialized Variables

An uninitialized variable is a variable that is declared but never given a safe starting value.

Example:

```cpp
char *p;
free(p);
```

Problem:

```text
p was never initialized.
It may point to random memory.
free(p) may try to free an invalid address.
```

Better idea:

```cpp
char *p = nullptr;
```

Main rule:

```text
Do not assume a variable starts as 0, blank, or NULL.
Initialize variables before using them.
```

---

# 18. Common Security Issue: Ignoring Errors

Ignoring errors means the program catches or detects a problem but does nothing useful with it.

Example:

```cpp
try
{
    cin >> num1 >> num2;
    num1 = num1 / num2;
}
catch (...)
{
    // errors ignored
}
```

Problem:

```text
If num2 is 0, division by zero happens.
The catch block hides the error instead of handling it.
```

Security risk:

```text
The program may continue in a bad state.
The real problem is hidden.
Attackers may use ignored errors to trigger broken behavior.
```

Better idea:

```text
Check num2 before dividing.
Report or handle the error.
Do not silently ignore it.
```

---

# 19. Common Security Issue: Dangling Pointers

A dangling pointer is a pointer that does not point to valid memory anymore.

Example:

```cpp
class Car
{
};

int main()
{
    Car *c = new Car();
}
```

Problem:

```text
Memory was allocated with new.
The program ended without deleting it.
```

This is a memory leak.

Another dangling pointer case:

```cpp
Car *c = new Car();
delete c;
// c still contains the old address, but that memory is no longer valid.
```

Better:

```cpp
delete c;
c = nullptr;
```

Main rule:

```text
If memory is deleted or freed, do not keep using the old pointer.
```

Rust note:

```text
Rust prevents many dangling-pointer and use-after-free problems through ownership and borrowing rules.
```

---

# 20. Security Practices

## Encapsulation

Encapsulation means hiding internal details from outside code.

Plain English:

```text
Do not expose more data or behavior than needed.
```

Why it helps:

```text
Less exposed state means fewer ways to misuse or attack the program.
```

---

## Check User Input

Do not assume user input is valid.

Examples:

```text
If asking for a date, verify that the date is real.
If asking for a number, verify that the input is a number.
If dividing, verify that the divisor is not zero.
```

Main rule:

```text
Validate input before using it.
```

---

## Limit User Input

Limit input to a specific format when possible.

Example:

```text
Phone number format:
(XXX) XXX-XXXX
```

Why it helps:

```text
The more controlled the input is, the harder it is to pass dangerous or unexpected data.
```

---

## Defensive Programming

Defensive programming means assuming things can go wrong.

Plain English:

```text
Do not write code as if every caller and every user behaves correctly.
```

Examples:

```text
Check inputs.
Check bounds.
Check return values.
Use assertions where useful.
Fail safely.
```

---

## Test Code Limits

Testing should include edge cases.

Examples:

```text
empty input
very large input
negative numbers
zero
array boundary indexes
invalid types
missing files
permission errors
```

Main rule:

```text
Test what happens when the program receives bad or unexpected input.
```

---

# 21. Secure Coding Checklist

Important secure coding rules:

```text
Validate input.

Pay attention to compiler warnings.

Keep the design simple.

Default to denying unsafe behavior.

Use least privilege.

Sanitize data before sending it to another system.

Use multiple layers of defense.

Test thoroughly.

Use secure coding standards.

Do not ignore errors.
```

---

# 22. Clean Room Reverse Engineering

Clean room reverse engineering is a way to recreate functionality without directly copying protected code.

The idea:

```text
Team 1 studies the original system and writes a behavior/specification document.

Team 2 never sees the original code.

Team 2 builds a new implementation from the behavior/specification only.
```

Why this matters:

```text
The goal is to create similar functionality without copying proprietary code.
```

Plain English:

```text
Understand behavior, then rebuild independently.
```

---

# 23. Corporate Security Big Idea

Security is not only an individual programmer issue.

Companies need policies and processes that make insecure code less likely.

Important areas:

```text
secure design
code review
testing
deployment rules
least privilege
input validation
auditing
automated checks
```

---

# 24. Security by Design

Security by design means security is planned from the beginning.

Plain English:

```text
Do not add security at the end.
Build the system assuming code can fail and users may act maliciously.
```

Examples:

```text
automated security checks
continuous testing
audit logs
access controls
safe defaults
```

---

# 25. Code Testing and Maintenance

Testing should not only check:

```text
does the code run?
```

It should also check:

```text
does it handle bad input?
does it handle edge cases?
does it fail safely?
does it meet business requirements?
does it perform correctly?
```

Good testing includes:

```text
developer perspective
system analyst perspective
user perspective
security perspective
```

---

# 26. Deployment / Pushing Code

Pushing code means making a new version available to users.

Security risk:

```text
If developers can push directly to production without review, broken or unsafe code can reach users.
```

Better process:

```text
code review
testing
approval gates
automated checks
controlled deployment
rollback plan
```

Main rule:

```text
Do not let unreviewed code go directly to production.
```

---

# 27. Main Summary

```text
g++ -S generates assembly from C++.

The output file usually ends in .s.

Writing C++ from assembly means tracking register and memory state line by line.

One C++ expression can become many assembly instructions.

Shifts can represent multiplication or division by powers of 2.

testl sets flags for later conditional instructions.

cmovs conditionally copies one register into another.

Security problems often come from invalid memory, unchecked input, ignored errors, and unsafe pointer behavior.

Secure code validates input, checks errors, limits exposure, and fails safely.

Security is both a code-level problem and an organization-level process problem.
```
