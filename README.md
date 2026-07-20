# Assembly Notes

Coursework and study notes for CS 410, comparing C++ source with the assembly a
compiler generates. Everything targets **x86-64 in GNU / AT&T syntax**, and the
notes are written in plain English so each instruction explains whether it works
with an **address** or a **value**, and whether it touches **memory** or a
**register**.

## Table of Contents

- [Overview](#overview)
- [Repository Structure](#repository-structure)
- [Conventions](#conventions)
- [Notes](#notes)
- [1-2 Activity: C++ to Assembly](#1-2-activity-c-to-assembly)
- [2-1 Activity: C++ to Assembly With Loops](#2-1-activity-c-to-assembly-with-loops)
- [2-2 Activity: Assembly to C++](#2-2-activity-assembly-to-c)
- [Generating Assembly](#generating-assembly)
- [Building](#building)
- [Requirements](#requirements)

## Overview

This repo is a personal learning space for understanding how simple C++
constructs (integer variables, addition and subtraction, input and output,
arrays, and loops) map down to assembly. Each activity pairs a piece of C++ with
its assembly, and the notes break that assembly down line by line.

Folders are named after the course's own activity numbering, so
`module-2/2-1-activity-cpp-to-assembly-with-loops/` is *2-1 Activity: C++ to
Assembly With Loops*. Every activity folder holds an `assignment/` (the
submitted document, plus a Markdown copy with the same wording) and a `src/`
(the code it is about).

## Repository Structure

```text
assembly-notes/
├── README.md                                           # You are here
├── CMakeLists.txt                                      # Build config for the activity programs
├── module-1/
│   └── 1-2-activity-cpp-to-assembly/                   # 1-2 Activity: C++ to Assembly
│       ├── src/
│       │   ├── assignment1_1.cpp                       # A simple C++ program
│       │   └── assignment1_1.s                         # The assembly generated for it
│       ├── assignment/
│       │   └── CS 410 C++ to Assembly Activity Template.docx
│       └── notes/
│           ├── README.md                               # Index of the study notes
│           ├── assembly-skeleton-basics.md             # Skeleton, variables, I/O, math
│           ├── assembly-basics.md                      # Reading integers with cin
│           ├── assembly-practice-add-subtract.md       # Worked a + b - c example
│           ├── assembly-arrays-basics.md               # How arrays sit in memory
│           ├── assembly-conditionals-and-loops.md      # if/else and for loops
│           └── assembly-generate-reverse-and-security.md
└── module-2/
    ├── 2-1-activity-cpp-to-assembly-with-loops/        # 2-1 Activity: C++ to Assembly With Loops
    │   ├── src/
    │   │   ├── assignment2_1.cpp                       # The given factorial program
    │   │   └── assignment2_1.s                         # The assembly generated for it
    │   └── assignment/
    │       ├── CS 410 C++ to Assembly With Loops Activity Template.docx
    │       └── cpp-to-assembly-with-loops-activity.md  # Same wording, in Markdown
    └── 2-2-activity-assembly-to-cpp/                   # 2-2 Activity: Assembly to C++
        ├── src/
        │   ├── assignment2_2_1.s                       # Given assembly, block 1
        │   ├── assignment2_2_1.cpp                     # The C++ it converts to
        │   ├── assignment2_2_2.s                       # Given assembly, block 2
        │   ├── assignment2_2_2.cpp                     # The C++ it converts to
        │   ├── assignment2_2_3.s                       # Given assembly, block 3
        │   └── assignment2_2_3.cpp                     # The C++ it converts to
        └── assignment/
            ├── CS 410 Assembly to C++ Activity Template.docx
            └── assembly-to-cpp-activity.md             # Same wording, in Markdown
```

## Conventions

- **Architecture / syntax:** x86-64, GNU / AT&T assembly.
- **Operand order:** source first, destination second, so `movl $2, -12(%rbp)`
  stores `2` into the slot.
- **Local variables** live in **stack slots** written as negative offsets from
  the frame pointer, e.g. `-4(%rbp)`. Each `int` is 4 bytes.
- **Registers** such as `%eax` and `%edx` hold values while arithmetic happens.
- **`mov` means copy**, not move. The source is left unchanged.

## Notes

The [`module-1/1-2-activity-cpp-to-assembly/notes/`](module-1/1-2-activity-cpp-to-assembly/notes)
folder contains the detailed, line-by-line study notes. See
[`notes/README.md`](module-1/1-2-activity-cpp-to-assembly/notes/README.md) for the
full index and a suggested reading order. In short:

| Note | Topic |
| --- | --- |
| [assembly-skeleton-basics.md](module-1/1-2-activity-cpp-to-assembly/notes/assembly-skeleton-basics.md) | The core reference: function skeleton, variables, strings, input/output, and math |
| [assembly-basics.md](module-1/1-2-activity-cpp-to-assembly/notes/assembly-basics.md) | Reading integers from input with `cin` and `leaq` |
| [assembly-practice-add-subtract.md](module-1/1-2-activity-cpp-to-assembly/notes/assembly-practice-add-subtract.md) | A complete worked `result = a + b - c` example |
| [assembly-arrays-basics.md](module-1/1-2-activity-cpp-to-assembly/notes/assembly-arrays-basics.md) | How a small `int` array is laid out in memory |
| [assembly-conditionals-and-loops.md](module-1/1-2-activity-cpp-to-assembly/notes/assembly-conditionals-and-loops.md) | `if`/`else` and `for` loops as compares, jumps, and labels |
| [assembly-generate-reverse-and-security.md](module-1/1-2-activity-cpp-to-assembly/notes/assembly-generate-reverse-and-security.md) | Generating assembly (`g++ -S`), reversing it to C++, and code security |

## 1-2 Activity: C++ to Assembly

A simple program that multiplies two integers and prints the result.

- [`src/assignment1_1.cpp`](module-1/1-2-activity-cpp-to-assembly/src/assignment1_1.cpp)
  contains the C++ program.
- [`src/assignment1_1.s`](module-1/1-2-activity-cpp-to-assembly/src/assignment1_1.s)
  contains the assembly generated for it (unmodified compiler output).
- [`assignment/`](module-1/1-2-activity-cpp-to-assembly/assignment) holds the
  Module 1 assignment (`CS 410 C++ to Assembly Activity Template.docx`).

## 2-1 Activity: C++ to Assembly With Loops

A factorial program: it reads a number, multiplies down from it in a `for` loop,
and prints the result. This is the lesson where the loop shows up in assembly as
a compare, a conditional jump, and a backward `jmp` to a label (`.L3` / `.L2`).

- [`src/assignment2_1.cpp`](module-2/2-1-activity-cpp-to-assembly-with-loops/src/assignment2_1.cpp)
  is the program as given, kept **exactly as provided** so the assembly matches it.
- [`src/assignment2_1.s`](module-2/2-1-activity-cpp-to-assembly-with-loops/src/assignment2_1.s)
  is the assembly generated for it (unmodified compiler output).
- [`assignment/cpp-to-assembly-with-loops-activity.md`](module-2/2-1-activity-cpp-to-assembly-with-loops/assignment/cpp-to-assembly-with-loops-activity.md)
  is the completed activity in Markdown: all four steps, with each C++ line
  aligned to its block of assembly and explained.

**On `return 1;`**. The value returned from `main` becomes the program's exit
status. By convention `0` means success and any nonzero value means failure, so
the given program reports failure even though it completes normally. It shows up
in the assembly as a single instruction, `movl $1, %eax`, right before `ret`.

## 2-2 Activity: Assembly to C++

Module 2's second assignment, and the reverse of the first two activities: instead of
compiling C++ down to assembly, this one starts from three blocks of assembly and
works back up to the C++ that would produce them.

All three blocks share the same shape. Each reads an `int` from the stack slot
`-8(%rbp)`, does arithmetic in registers, and stores the result into `-4(%rbp)`,
so each one reduces to a single assignment statement.

- [`assignment/CS 410 Assembly to C++ Activity Template.docx`](module-2/2-2-activity-assembly-to-cpp/assignment/CS%20410%20Assembly%20to%20C++%20Activity%20Template.docx)
  is the completed activity as submitted.
- [`assignment/assembly-to-cpp-activity.md`](module-2/2-2-activity-assembly-to-cpp/assignment/assembly-to-cpp-activity.md)
  is that same document, word for word, in Markdown, with every instruction next
  to its C++ line and explanation.
- [`src/`](module-2/2-2-activity-assembly-to-cpp/src) has a **pair** of files per
  block, the mirror image of how the other two activities are laid out. There the
  `.cpp` came first and the `.s` was generated from it. Here the `.s` is what was
  given and the `.cpp` is what it converts back to.

| Block | Given assembly | Converted C++ | Reduces to |
| --- | --- | --- | --- |
| 1 | [`assignment2_2_1.s`](module-2/2-2-activity-assembly-to-cpp/src/assignment2_2_1.s) | [`assignment2_2_1.cpp`](module-2/2-2-activity-assembly-to-cpp/src/assignment2_2_1.cpp) | `y = (x * 8) - 3;` |
| 2 | [`assignment2_2_2.s`](module-2/2-2-activity-assembly-to-cpp/src/assignment2_2_2.s) | [`assignment2_2_2.cpp`](module-2/2-2-activity-assembly-to-cpp/src/assignment2_2_2.cpp) | `y = ((x * 4) - 1) / 8;` |
| 3 | [`assignment2_2_3.s`](module-2/2-2-activity-assembly-to-cpp/src/assignment2_2_3.s) | [`assignment2_2_3.cpp`](module-2/2-2-activity-assembly-to-cpp/src/assignment2_2_3.cpp) | `y = (x / 8) + (x * 4);` |

Each `.cpp` is runnable. It keeps every assembly step as its own C++ line with the
matching instruction in a trailing comment, then states the one-line form the
whole block reduces to. The `.s` files hold the assembly exactly as the activity
gave it. They are reference material, not something that assembles on its own,
since the blocks have no function skeleton around them.

The `sall` / `sarl` shifts and the `leal` + `testl` + `cmovs` sequence are the
things to work out here. That last sequence is signed division by 8. `sarl`
alone rounds toward negative infinity, but C++ integer division rounds toward
zero, so the compiler adds 7 to a copy and uses that copy only when the value is
negative. See
[assembly-skeleton-basics.md](module-1/1-2-activity-cpp-to-assembly/notes/assembly-skeleton-basics.md)
for the arithmetic reference.

## Generating Assembly

The committed `.s` files are **x86-64 GNU / AT&T** assembly, produced by `g++` on
x86-64 Linux:

```sh
g++ -std=c++20 -O0 -S module-2/2-1-activity-cpp-to-assembly-with-loops/src/assignment2_1.cpp \
  -o module-2/2-1-activity-cpp-to-assembly-with-loops/src/assignment2_1.s
```

`-O0` keeps optimizations off so the assembly stays close to the source and is
easier to follow.

> **Note:** running this on an Apple Silicon Mac will **not** reproduce the
> committed files. Clang there targets ARM64, so you get `sub sp, sp, #32` and
> `x29` instead of `pushq %rbp` and `%rbp`. To regenerate the x86-64 assembly in
> this repo, use an x86-64 Linux machine, a container, or an online compiler.

## Building

The activity programs can be compiled to runnable executables with CMake:

```sh
cmake -S . -B build
cmake --build build
```

That produces five executables:

| Executable | Source |
| --- | --- |
| `./build/assembly_notes` | 1-2 Activity, multiply and print |
| `./build/assignment2_1` | 2-1 Activity, factorial |
| `./build/assignment2_2_1` | 2-2 Activity, block 1 |
| `./build/assignment2_2_2` | 2-2 Activity, block 2 |
| `./build/assignment2_2_3` | 2-2 Activity, block 3 |

All five targets build and run.

## Requirements

- A C++ compiler that supports C++20 (e.g. `clang++` or `g++`).
- CMake 3.30 or newer (only needed for the [Building](#building) step).
