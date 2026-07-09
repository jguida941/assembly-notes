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

1. **[assembly-skeleton-basics.md](assembly-skeleton-basics.md)** — the core
   reference. Read this first; the other notes are focused practice on ideas it
   introduces.
2. **[assembly-basics.md](assembly-basics.md)** — reading integers with `cin`.
3. **[assembly-practice-add-subtract.md](assembly-practice-add-subtract.md)** —
   a worked `a + b - c` example.
4. **[assembly-arrays-basics.md](assembly-arrays-basics.md)** — how arrays sit
   in memory.

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

## Recurring Ideas

- **Address vs value** — `leaq` computes an address; `movl` usually copies a value.
- **`mov` means copy**, not move — the source is left unchanged.
- **AT&T order is source, destination** — `movl $2, -12(%rbp)` stores `2` into the slot.
- **Stack slots** — locals live at negative offsets from `%rbp`; `int`s are 4 bytes apart.
- **Registers do the math** — values are loaded into registers, combined, then stored back.
