# Assembly Notes: Skeleton Code, Variables, Strings, Input, Math, and Output

I rewrote these notes in my own words so each assembly instruction explains what it is doing.

The main things I care about:

- Is the instruction working with an **address** or a **value**?
- Is the instruction using **memory** or a **register**?
- Is this line part of the fixed skeleton or the actual program logic?

## Table of Contents

- [1. Key Rules](#1-key-rules)
- [2. Skeleton Code](#2-skeleton-code)
- [3. Integer Variable Assignment](#3-integer-variable-assignment)
- [4. Adding Two Integers](#4-adding-two-integers)
- [5. Reading One Integer and Printing It](#5-reading-one-integer-and-printing-it)
- [6. Read Two Integers, Subtract, Print Result](#6-read-two-integers-subtract-print-result)
- [7. Printing Strings](#7-printing-strings)
- [8. Printing Two Strings](#8-printing-two-strings)
- [9. What I Should Not Overthink](#9-what-i-should-not-overthink)
- [10. Final Cheat Sheet](#10-final-cheat-sheet)


# 1. Key Rules

## Address vs Value

An **address** is where something lives in memory.

A **value** is the actual data stored there.

Example:

```asm
leaq -12(%rbp), %rax
```

Means:

```text
rax = address of the variable at -12(%rbp)
```

But:

```asm
movl -12(%rbp), %eax
```

Means:

```text
eax = value stored at -12(%rbp)
```

So:

```text
leaq gets an address.
movl gets or stores a value.
```



## Registers

Registers are temporary storage boxes inside the CPU.

Common ones in these examples:

```text
rbp = base pointer for the current function's stack frame
rsp = stack pointer
rax = 64-bit temporary register
eax = lower 32-bit part of rax, often used for int values
rdx = 64-bit register
edx = lower 32-bit part of rdx, often used for int values
rsi = 64-bit argument register
esi = lower 32-bit part of rsi, often used for int arguments
rdi = 64-bit argument register
edi = lower 32-bit part of rdi
```

For now:

```text
eax, edx, esi = usually integer values
rax, rsi, rdi = usually addresses or 64-bit values
```



## `mov` Means Copy

`mov` does not remove the original value.

It copies from source to destination.

Example:

```asm
movl %eax, %esi
```

Means:

```text
esi = eax
```

After this, both can hold the same value.


## AT&T Syntax Order

These examples use AT&T syntax.

The order is:

```asm
instruction source, destination
```

Example:

```asm
movl %eax, %esi
```

Means:

```text
copy eax into esi
```

Example:

```asm
subl %eax, %edx
```

Means:

```text
edx = edx - eax
```



# 2. Skeleton Code

Most of the assembly file is fixed skeleton code created by the compiler.

For this course, I mostly care about the lines inside `main` that perform the actual program logic.

The skeleton handles:

- starting the function
- setting up stack memory
- cleaning up before returning
- metadata/debugging information

My code handles:

- assigning values
- reading input
- doing math
- printing output


## Example C++ Code

```cpp
#include <iostream>

int main()
{
    int i;
    i = 12;
    return 0;
}
```



## Full Assembly Skeleton

```asm
.file "test.cpp"
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

movl $12, -4(%rbp)

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



## What I Actually Need to Understand

```asm
movl $12, -4(%rbp)
```

Commented:

```asm
# Store the value 12 into i's memory slot.
# -4(%rbp) is where the local integer variable i is stored.
movl $12, -4(%rbp)
```

Plain English:

```text
i = 12
```



## Skeleton Lines Explained

```asm
.file "test.cpp"
```

Names the original source file.

```asm
.text
```

Starts the code section.

```asm
.globl main
.type main, @function
main:
```

Defines the `main` function.

```asm
pushq %rbp
movq %rsp, %rbp
```

Sets up the stack frame.

Plain English:

```text
Set up the function so local variables can be stored using rbp offsets.
```

This is why local variables can use:

```asm
-4(%rbp)
-8(%rbp)
-12(%rbp)
```

```asm
.cfi_...
```

Compiler/debugging metadata. For this course, I do not edit these.

```asm
movl $1, %eax
popq %rbp
ret
```

Function cleanup and return.

For this course, I usually do not edit these unless instructed.



# 3. Integer Variable Assignment

## One Integer

C++:

```cpp
int i;
i = 12;
```

Assembly:

```asm
# Store the value 12 into i.
# i lives at -4(%rbp).
movl $12, -4(%rbp)
```

Memory:

```text
-4(%rbp) = i = 12
```



## Two Integers

If one integer uses:

```asm
-4(%rbp)
```

then another integer needs another 4-byte slot:

```asm
-8(%rbp)
```

Example:

```asm
# Store 12 into i.
# i lives at -4(%rbp).
movl $12, -4(%rbp)

# Store 13 into j.
# j lives at -8(%rbp).
movl $13, -8(%rbp)
```

Memory layout:

```text
-4(%rbp) = i = 12
-8(%rbp) = j = 13
```

Important:

```text
Do not reuse -4(%rbp) for j if i is already stored there.
Use a different stack slot.
```

---

# 4. Adding Two Integers

## C++ Code

```cpp
int i, j, k;

i = 2;
j = 3;
k = i + j;

cout << k;
```


## Assembly

```asm
# Store 2 into i.
# i lives at -12(%rbp).
movl $2, -12(%rbp)

# Store 3 into j.
# j lives at -8(%rbp).
movl $3, -8(%rbp)

# Copy the value of j into eax.
# eax now holds j's value, which is 3.
movl -8(%rbp), %eax

# Copy the value of i into edx.
# edx now holds i's value, which is 2.
movl -12(%rbp), %edx

# Add edx into eax.
# eax = eax + edx.
# eax = 3 + 2.
# eax now holds 5.
addl %edx, %eax

# Store the result into k.
# k lives at -4(%rbp).
# k now equals 5.
movl %eax, -4(%rbp)

# Copy k's value back into eax.
# eax now holds k's value, which is 5.
movl -4(%rbp), %eax

# Put k's value where cout expects the value to print: esi.
# esi now holds 5.
movl %eax, %esi

# Set eax to 0 for function-call setup.
# This does not erase k.
# The value 5 is still in esi and still stored in k's memory slot.
movl $0, %eax

# Print the value in esi.
call cout
```



## Memory Layout

```text
-12(%rbp) = i = 2
-8(%rbp)  = j = 3
-4(%rbp)  = k = 5
```



## Important Addition Rule

```asm
addl %edx, %eax
```

Means:

```text
eax = eax + edx
```

If:

```text
eax = 3
edx = 2
```

Then:

```text
eax = 5
edx = 2
```

The result is in `eax`, not both registers.

That is why this line stores only `eax` into `k`:

```asm
movl %eax, -4(%rbp)
```



# 5. Reading One Integer and Printing It

## C++ Code

```cpp
int i;

cin >> i;

cout << i;
```



## Assembly

```asm
# Get i's memory address.
# rax now holds the location where i is stored, not i's value.
# leaq is the instruction that calculates a memory address.
leaq -4(%rbp), %rax

# Put i's address where cin expects the input destination: rsi.
# rsi now also holds the address of i.
movq %rax, %rsi

# Read user input and store it into the address in rsi.
# Since rsi holds i's address, this writes the input into i.
call cin

# Copy the value of i into eax.
# eax now holds i's value, not i's address.
movl -4(%rbp), %eax

# Put i's value where cout expects the value to print: esi.
# esi now holds i's value.
movl %eax, %esi

# Print the value in esi.
call cout
```



## Key Rule

```text
cin needs an address because it writes into a variable.
cout needs a value because it prints a variable.
```

So:

```asm
leaq -4(%rbp), %rax
```

Means:

```text
rax = address of i
```

But:

```asm
movl -4(%rbp), %eax
```

Means:

```text
eax = value of i
```



# 6. Read Two Integers, Subtract, Print Result

## C++ Code

```cpp
int i, j, k;

cin >> i >> j;

k = i - j;

cout << k;
```


## Assembly

```asm
# Read i

# Get i's memory address.
# rax now holds the location where i is stored, not i's value.
# leaq is the instruction that calculates a memory address.
leaq -12(%rbp), %rax

# Put i's address where cin expects the input destination: rsi.
# rsi now also holds the address of i.
movq %rax, %rsi

# Read user input and store it into the address in rsi.
# Since rsi holds i's address, this writes the input into i.
call cin


# Read j

# Get j's memory address.
# rax now holds the location where j is stored, not j's value.
# leaq is the instruction that calculates a memory address.
leaq -8(%rbp), %rax

# Put j's address where cin expects the input destination: rsi.
# rsi now also holds the address of j.
movq %rax, %rsi

# Read user input and store it into the address in rsi.
# Since rsi holds j's address, this writes the input into j.
call cin


# Subtract i - j

# Copy the value of i into edx.
# edx now holds i's value, not i's address.
movl -12(%rbp), %edx

# Copy the value of j into eax.
# eax now holds j's value, not j's address.
movl -8(%rbp), %eax

# Subtract eax from edx.
# Since edx = i and eax = j, this does: edx = i - j.
subl %eax, %edx

# Copy the result into eax.
# eax now also holds i - j.
movl %edx, %eax

# Store the result into k's memory slot.
# k now equals i - j.
movl %eax, -4(%rbp)


# Print k

# Copy the value of k into eax.
# eax now holds k's value, not k's address.
movl -4(%rbp), %eax

# Put k's value where cout expects the value to print: esi.
# esi now holds k's value.
movl %eax, %esi

# Print the value in esi.
call cout
```


## Memory Layout

```text
-12(%rbp) = i
-8(%rbp)  = j
-4(%rbp)  = k
```

---

## Subtraction Rule

```asm
subl %eax, %edx
```

Means:

```text
edx = edx - eax
```

If:

```text
edx = i
eax = j
```

Then:

```text
edx = i - j
```

Example:

```text
i = 10
j = 3

edx = 10
eax = 3

subl %eax, %edx

edx = 10 - 3
edx = 7
```



# 7. Printing Strings

## C++ Code

```cpp
#include <iostream>
using namespace std;

int main()
{
    cout << "Hello World" << endl;
    return 0;
}
```



## Assembly

```asm
.file "test.cpp"

.section .rodata
.LC0:
.string "Hello World"

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



## String Storage

```asm
.section .rodata
```

Starts the read-only data section.

Plain English:

```text
This is where constant strings are stored.
```

```asm
.LC0:
```

Creates a label for the string.

Plain English:

```text
.LC0 is the name/location of this string.
```

```asm
.string "Hello World"
```

Stores the actual string.

Plain English:

```text
The label .LC0 points to the string "Hello World".
```

So this:

```asm
.LC0:
.string "Hello World"
```

Means:

```text
Create a string named .LC0 that contains "Hello World".
```


## Printing the String

```asm
movl $.LC0, %edi
```

Line-by-line comment:

```asm
# Put the address of the string .LC0 into edi.
# puts expects the string address in edi.
movl $.LC0, %edi
```

Plain English:

```text
Give puts the location of "Hello World".
```

Then:

```asm
call puts
```

Line-by-line comment:

```asm
# Print the string whose address is in edi.
call puts
```

Plain English:

```text
Print "Hello World".
```



# 8. Printing Two Strings

## C++ Code

```cpp
#include <iostream>
using namespace std;

int main()
{
    cout << "Hello World" << endl;
    cout << "I am here..." << endl;
    return 0;
}
```



## Assembly

```asm
.file "test.cpp"

.section .rodata
.LC0:
.string "Hello World"
.LC1:
.string "I am here..."

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

movl $.LC1, %edi
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



## String Labels

```asm
.LC0:
.string "Hello World"
```

Creates the first string.

```text
.LC0 = "Hello World"
```

```asm
.LC1:
.string "I am here..."
```

Creates the second string.

```text
.LC1 = "I am here..."
```



## Print First String

```asm
# Put the address of the first string into edi.
# puts expects the string address in edi.
movl $.LC0, %edi

# Print the string at .LC0.
call puts
```

Plain English:

```text
Print "Hello World".
```



## Print Second String

```asm
# Put the address of the second string into edi.
# puts expects the string address in edi.
movl $.LC1, %edi

# Print the string at .LC1.
call puts
```

Plain English:

```text
Print "I am here...".
```


# 9. What I Should Not Overthink

I do not need to deeply understand these for the current assignment:

```asm
.file
.text
.globl
.type
.LFB2
.cfi_startproc
.cfi_def_cfa_offset
.cfi_offset
.cfi_def_cfa_register
.cfi_endproc
.LFE2
.size
.ident
.section .note.GNU-stack
```

For now, these are compiler skeleton/debugging/metadata lines.

The lines I actually need to write or understand are usually:

```asm
movl $12, -4(%rbp)
movl $13, -8(%rbp)
movl $.LC0, %edi
call puts
leaq -4(%rbp), %rax
movq %rax, %rsi
call cin
movl -4(%rbp), %eax
movl %eax, %esi
call cout
```



# 10. Final Cheat Sheet

## Integer Variables

```text
Local int variables are stored near rbp.

First int:
-4(%rbp)

Second int:
-8(%rbp)

Third int:
-12(%rbp)
```

Example:

```asm
movl $12, -4(%rbp)
```

Means:

```text
Store 12 into the first local int slot.
```



## Strings

```text
Strings are stored in .rodata.
Each string gets a label like .LC0 or .LC1.
```

Example:

```asm
.LC0:
.string "Hello World"
```

Means:

```text
Create a string named .LC0 containing "Hello World".
```



## Printing Strings

```asm
movl $.LC0, %edi
call puts
```

Means:

```text
Put the string address into edi.
Call puts to print it.
```



## Input vs Output

```text
cin needs an address because it writes into a variable.
cout needs a value because it prints a variable.
```

Input pattern:

```asm
leaq -4(%rbp), %rax
movq %rax, %rsi
call cin
```

Means:

```text
Get i's address.
Put i's address where cin expects it.
cin writes into i.
```

Output pattern:

```asm
movl -4(%rbp), %eax
movl %eax, %esi
call cout
```

Means:

```text
Get i's value.
Put i's value where cout expects it.
cout prints i.
```



## Math Pattern

Addition:

```asm
addl %edx, %eax
```

Means:

```text
eax = eax + edx
```

Subtraction:

```asm
subl %eax, %edx
```

Means:

```text
edx = edx - eax
```



## Main Summary

```text
Integer variables use stack slots like -4(%rbp).
String constants use labels like .LC0.
leaq calculates an address.
mov copies values or addresses.
cin needs an address.
cout needs a value.
puts needs a string address.
Math happens in registers.
Results are stored back into memory slots.
```
