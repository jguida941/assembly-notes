# Assembly Notes: Arrays Basics

I rewrote this section in my own words so each array instruction explains what it is doing.
Seperating concept from the Syntax.

The main things I care about:

- An array stores multiple values of the same type.
- Each array element has its own memory location.
- For `int` arrays, each element takes 4 bytes.
- Array indexes start at 0.
- In this class example, the array elements are stored near `%rbp`.

## 1. Big Idea

An array is one variable that holds multiple values.

Example:

```cpp
int values[3];
```

This creates space for three integers:

```text
values[0]
values[1]
values[2]
```

Each one is an `int`.

Since an `int` takes 4 bytes, each array element is 4 bytes apart in memory.


## 2. C++ Code

```cpp
int values[3];

values[0] = 10;
values[1] = 20;
values[2] = 30;
```

Plain English:

```text
Create an integer array with 3 spots.

Put 10 in the first spot.
Put 20 in the second spot.
Put 30 in the third spot.
```


## 3. Variable Layout

For this example, the array uses these stack slots:

```text
-16(%rbp) = values[0]
-12(%rbp) = values[1]
-8(%rbp)  = values[2]
```

Each element is 4 bytes apart:

```text
values[0] = -16(%rbp)
values[1] = -12(%rbp)
values[2] = -8(%rbp)
```

## 4. Assembly

```asm
# Store the value 10 into the first array element.
# values[0] lives at -16(%rbp).
movl $10, -16(%rbp)

# Store the value 20 into the second array element.
# values[1] lives at -12(%rbp).
movl $20, -12(%rbp)

# Store the value 30 into the third array element.
# values[2] lives at -8(%rbp).
movl $30, -8(%rbp)
```

## 5. Line-by-Line Breakdown

```asm
movl $10, -16(%rbp)
```

Means:

```text
values[0] = 10
```

Explanation:

```text
Copy the value 10 into the first array element.
The first array element is values[0].
In this layout, values[0] lives at -16(%rbp).
```

```asm
movl $20, -12(%rbp)
```

Means:

```text
values[1] = 20
```

Explanation:

```text
Copy the value 20 into the second array element.
The second array element is values[1].
In this layout, values[1] lives at -12(%rbp).
```

```asm
movl $30, -8(%rbp)
```

Means:

```text
values[2] = 30
```

Explanation:

```text
Copy the value 30 into the third array element.
The third array element is values[2].
In this layout, values[2] lives at -8(%rbp).
```


## 6. Memory Picture

```text
Address Slot     Array Element     Value

-16(%rbp)        values[0]         10
-12(%rbp)        values[1]         20
-8(%rbp)         values[2]         30
```

Another way to see it:

```text
values[0]  →  10
values[1]  →  20
values[2]  →  30
```

## 7. Why the Slots Move by 4

Each `int` takes 4 bytes.

So the array elements move by 4 bytes:

```text
-16 to -12 is 4 bytes
-12 to -8 is 4 bytes
```

That is why this:

```cpp
values[0] = 10;
values[1] = 20;
values[2] = 30;
```

can become:

```asm
movl $10, -16(%rbp)
movl $20, -12(%rbp)
movl $30, -8(%rbp)
```

## 8. Array Indexes

Array indexes start at 0.

So for:

```cpp
int values[3];
```

the valid indexes are:

```text
values[0]
values[1]
values[2]
```

Not:

```text
values[1]
values[2]
values[3]
```

So:

```cpp
values[0] = 10;
```

means:

```text
Put 10 in the first array slot.
```

```cpp
values[1] = 20;
```

means:

```text
Put 20 in the second array slot.
```

```cpp
values[2] = 30;
```

means:

```text
Put 30 in the third array slot.
```

## 9. Array vs Separate Variables

Separate variables:

```cpp
int a, b, c;
```

might use:

```text
-16(%rbp) = a
-12(%rbp) = b
-8(%rbp)  = c
```

An array:

```cpp
int values[3];
```

might use:

```text
-16(%rbp) = values[0]
-12(%rbp) = values[1]
-8(%rbp)  = values[2]
```

The assembly can look similar because both use memory slots.

The difference is the meaning:

```text
a, b, c are separate variables.

values[0], values[1], and values[2] are elements inside one array.
```

## 10. Important Pattern

For this class-level example:

```text
array element = base array slot + index movement
```

Since each `int` is 4 bytes:

```text
values[0] = first slot
values[1] = first slot + 4 bytes
values[2] = first slot + 8 bytes
```

In this specific stack layout:

```text
values[0] = -16(%rbp)
values[1] = -12(%rbp)
values[2] = -8(%rbp)
```


# 11. What to Remember

```text
An array stores multiple values of the same type.

Each array element has its own memory slot.

For int arrays, each element is 4 bytes.

Array indexes start at 0.

values[0] is the first element.

values[1] is the second element.

values[2] is the third element.

movl $10, -16(%rbp) stores 10 into values[0].

movl $20, -12(%rbp) stores 20 into values[1].

movl $30, -8(%rbp) stores 30 into values[2].
```

# 12. Main Summary

```text
Arrays are stored as nearby memory slots.

For an int array, each slot is 4 bytes apart.

The array name represents the start of the array.

values[0] is the first slot.

values[1] is the next slot.

values[2] is the next slot after that.

In this example:

-16(%rbp) = values[0] = 10
-12(%rbp) = values[1] = 20
-8(%rbp)  = values[2] = 30
```
