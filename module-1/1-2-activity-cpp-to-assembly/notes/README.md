# Notes

Hand-written study notes on x86-64 assembly (GNU / AT&T syntax), rewritten in
plain English so that every instruction says whether it is working with an
**address** or a **value**, and whether it touches **memory** or a **register**.

These notes map small pieces of C++ onto the assembly a compiler produces, and
then break that assembly down line by line.

## Table of Contents

- [How to Read These Notes](#how-to-read-these-notes)
- [Suggested Reading Order](#suggested-reading-order)
- [The Notes](#the-notes)
  - [assembly-skeleton-basics.md](#assembly-skeleton-basicsmd)
  - [assembly-basics.md](#assembly-basicsmd)
  - [assembly-practice-add-subtract.md](#assembly-practice-add-subtractmd)
  - [assembly-arrays-basics.md](#assembly-arrays-basicsmd)
  - [assembly-conditionals-and-loops.md](#assembly-conditionals-and-loopsmd)
  - [assembly-generate-reverse-and-security.md](#assembly-generate-reverse-and-securitymd)
- [Recurring Ideas](#recurring-ideas)

## How to Read These Notes

For every assembly line, the notes try to answer three questions:

1. Is the instruction working with an **address** or a **value**?
2. Is the instruction using **memory** or a **register**?
3. Is the line part of the fixed **skeleton** or the actual **program logic**?

Local variables live in **stack slots** written as negative offsets from the
frame pointer, for example `-4(%rbp)`. Registers such as `%eax` and `%edx` hold
values while the program does arithmetic.

## Suggested Reading Order

1. **[assembly-skeleton-basics.md](assembly-skeleton-basics.md)** is the core
   reference. Read this first; the other notes are focused practice on ideas it
   introduces.
2. **[assembly-basics.md](assembly-basics.md)** covers reading integers with `cin`.
3. **[assembly-practice-add-subtract.md](assembly-practice-add-subtract.md)** is
   a worked `a + b - c` example.
4. **[assembly-arrays-basics.md](assembly-arrays-basics.md)** covers how arrays
   sit in memory.
5. **[assembly-conditionals-and-loops.md](assembly-conditionals-and-loops.md)**
   covers `if`/`else` and `for` loops as compares, jumps, and labels.
6. **[assembly-generate-reverse-and-security.md](assembly-generate-reverse-and-security.md)**
   covers generating assembly with `g++ -S`, reversing assembly back to C++, and
   code security.

## The Notes

### [assembly-skeleton-basics.md](assembly-skeleton-basics.md)

The main reference note. Covers the full path from C++ to assembly for simple
programs.

- Key rules: address vs value, registers, `mov` means copy, AT&T syntax order
- The fixed function skeleton (`pushq %rbp` / `movq %rsp, %rbp` / `ret`)
- Integer variable assignment (one and two integers)
- Adding two integers, with memory layout
- Reading one integer with `cin` and printing it
- Reading two integers, subtracting, and printing the result
- Printing one and two strings (`.LC0`, `.LC1`, `puts`)
- A final cheat sheet for variables, strings, input vs output, and math

### [assembly-basics.md](assembly-basics.md)

Focused practice on **reading integers from input**. Uses `leaq` to get a
variable's address, moves that address into `%rsi`, and calls `cin` to store
the typed value into the variable.

- `leaq` loads an **address**, not a value
- Why `cin` needs the destination's address in `%rsi`
- Reading two integers (`i` and `j`)

### [assembly-practice-add-subtract.md](assembly-practice-add-subtract.md)

A complete worked example for `result = a + b - c`.

- Variable-to-stack-slot layout
- Line-by-line assembly with running register values
- An assembly summary and the expected output (`12`)

### [assembly-arrays-basics.md](assembly-arrays-basics.md)

How a small `int` array is laid out in memory.

- Each `int` element is 4 bytes, so slots move by 4
- Indexes start at 0 (`values[0]`, `values[1]`, `values[2]`)
- A memory picture of the array
- How arrays compare to separate variables

### [assembly-conditionals-and-loops.md](assembly-conditionals-and-loops.md)

How `if`/`else` and `for` loops are built from comparisons, jumps, and labels.

- Relational operators and their assembly jumps (`je`, `jg`, `jl`, `jge`, `jle`, `jne`)
- `cmp` sets up the comparison; the jump acts on it
- A full `if`/`else` example, including why the compiler tests the *opposite* condition
- Labels like `.L2` / `.L3` as jump targets
- A `for` loop broken down: init, condition-first jump, body, increment, re-check
- A step-by-step state walkthrough of the loop counter

### [assembly-generate-reverse-and-security.md](assembly-generate-reverse-and-security.md)

Going the other direction: producing assembly, reversing it back to C++, and the
security thinking that surrounds it.

- Generating assembly from C++ with `g++ -S` (`Hello.cpp` → `Hello.s`)
- Reading generated assembly and separating logic from compiler skeleton
- Reverse-engineering assembly to C++ by tracking register state line by line
- Shift/test/conditional-move patterns (`sall`, `sarl`, `testl`, `cmovs`)
- Common security issues: buffer overflow, uninitialized variables, ignored
  errors, dangling pointers
- Secure-coding practices, a checklist, clean-room reverse engineering, and
  security-by-design / deployment process

## Recurring Ideas

- **Address vs value.** `leaq` computes an address; `movl` usually copies a value.
- **`mov` means copy**, not move. The source is left unchanged.
- **AT&T order is source, destination.** `movl $2, -12(%rbp)` stores `2` into the slot.
- **Stack slots.** Locals live at negative offsets from `%rbp`; `int`s are 4 bytes apart.
- **Registers do the math.** Values are loaded into registers, combined, then stored back.
