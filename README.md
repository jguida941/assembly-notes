# Assembly Notes

Small lessons and study notes for comparing C++ source with the assembly a
compiler generates. Everything targets **x86-64 in GNU / AT&T syntax**, and the
notes are written in plain English so each instruction explains whether it works
with an **address** or a **value**, and whether it touches **memory** or a
**register**.

## Table of Contents

- [Overview](#overview)
- [Repository Structure](#repository-structure)
- [Conventions](#conventions)
- [Notes](#notes)
- [Lesson 01: C++ to Assembly](#lesson-01-c-to-assembly)
- [Building](#building)
- [Requirements](#requirements)

## Overview

This repo is a personal learning space for understanding how simple C++
constructs — integer variables, addition and subtraction, input and output, and
arrays — map down to assembly. Each lesson pairs a piece of C++ with its
generated assembly, and the notes folder breaks that assembly down line by line.

## Repository Structure

```text
assembly-notes/
├── README.md                       # You are here
├── CMakeLists.txt                  # Build config for the lesson program
└── module-1/
    └── lesson-01-cpp-to-assembly/  # All Module 1 material
        ├── src/
        │   ├── assignment1_1.cpp   # A simple C++ program
        │   └── assignment1_1.s     # The assembly generated for it
        ├── assignment/
        │   └── CS 410 C++ to Assembly Activity Template.docx  # Module 1 assignment
        └── notes/
            ├── README.md                   # Index of the study notes
            ├── assembly-skeleton-basics.md # Core reference: skeleton, variables, strings, I/O, math
            ├── assembly-basics.md          # Reading integers with cin
            ├── assembly-practice-add-subtract.md  # Worked a + b - c example
            ├── assembly-arrays-basics.md   # How arrays sit in memory
            ├── assembly-conditionals-and-loops.md  # if/else and for loops
            └── assembly-generate-reverse-and-security.md  # g++ -S, reversing to C++, security
```

## Conventions

- **Architecture / syntax:** x86-64, GNU / AT&T assembly.
- **Operand order:** source first, destination second — `movl $2, -12(%rbp)`
  stores `2` into the slot.
- **Local variables** live in **stack slots** written as negative offsets from
  the frame pointer, e.g. `-4(%rbp)`. Each `int` is 4 bytes.
- **Registers** such as `%eax` and `%edx` hold values while arithmetic happens.
- **`mov` means copy**, not move — the source is left unchanged.

## Notes

The [`module-1/lesson-01-cpp-to-assembly/notes/`](module-1/lesson-01-cpp-to-assembly/notes)
folder contains the detailed, line-by-line study notes, and
[`module-1/lesson-01-cpp-to-assembly/assignment/`](module-1/lesson-01-cpp-to-assembly/assignment)
holds the Module 1 assignment (`CS 410 C++ to Assembly Activity Template.docx`).
See [`notes/README.md`](module-1/lesson-01-cpp-to-assembly/notes/README.md) for the
full index and a suggested reading order. In short:

| Note | Topic |
| --- | --- |
| [assembly-skeleton-basics.md](module-1/lesson-01-cpp-to-assembly/notes/assembly-skeleton-basics.md) | The core reference: function skeleton, variables, strings, input/output, and math |
| [assembly-basics.md](module-1/lesson-01-cpp-to-assembly/notes/assembly-basics.md) | Reading integers from input with `cin` and `leaq` |
| [assembly-practice-add-subtract.md](module-1/lesson-01-cpp-to-assembly/notes/assembly-practice-add-subtract.md) | A complete worked `result = a + b - c` example |
| [assembly-arrays-basics.md](module-1/lesson-01-cpp-to-assembly/notes/assembly-arrays-basics.md) | How a small `int` array is laid out in memory |
| [assembly-conditionals-and-loops.md](module-1/lesson-01-cpp-to-assembly/notes/assembly-conditionals-and-loops.md) | `if`/`else` and `for` loops as compares, jumps, and labels |
| [assembly-generate-reverse-and-security.md](module-1/lesson-01-cpp-to-assembly/notes/assembly-generate-reverse-and-security.md) | Generating assembly (`g++ -S`), reversing it to C++, and code security |

## Lesson 01: C++ to Assembly

- [`src/assignment1_1.cpp`](module-1/lesson-01-cpp-to-assembly/src/assignment1_1.cpp)
  contains a simple C++ program.
- [`src/assignment1_1.s`](module-1/lesson-01-cpp-to-assembly/src/assignment1_1.s)
  contains the generated assembly for that program, annotated with the C++ each
  block corresponds to.

Regenerate the assembly on this machine with:

```sh
clang++ -std=c++20 -O0 -S module-1/lesson-01-cpp-to-assembly/src/assignment1_1.cpp -o module-1/lesson-01-cpp-to-assembly/src/assignment1_1.s
```

`-O0` keeps optimizations off so the assembly stays close to the source and is
easier to follow.

## Building

The lesson program can also be compiled to a runnable executable with CMake:

```sh
cmake -S . -B build
cmake --build build
./build/assembly_notes
```

## Requirements

- A C++ compiler that supports C++20 (e.g. `clang++` or `g++`).
- CMake 3.30 or newer (only needed for the [Building](#building) step).
