# Assembly Notes: Add and Subtract Practice

## Table of Contents

- [C++ Code](#c-code)
- [Variable Layout](#variable-layout)
- [Assembly To Break Down](#assembly-to-break-down)
- [Assembly Summary](#assembly-summary)
- [Expected Output](#expected-output)

## C++ Code

```cpp
int a, b, c, result;

a = 10;
b = 4;
c = 2;

result = a + b - c;

cout << result;
```


## Variable Layout

```text
-16(%rbp) = a
-12(%rbp) = b
-8(%rbp)  = c
-4(%rbp)  = result
```



## Assembly To Break Down

```asm
# Store the value 10 into a's memory slot.
# a lives at -16(%rbp).
movl $10, -16(%rbp)

# Store the value 4 into b's memory slot.
# b lives at -12(%rbp).
movl $4, -12(%rbp)

# Store the value 2 into c's memory slot.
movl $2, -8(%rbp)


# Copy a's value into eax.
# a lives at -16(%rbp), and a currently equals 10.
# eax now holds 10.
movl -16(%rbp), %eax

# Copy b's value into edx.
# b lives at -12(%rbp), and b currently equals 4.
# edx now holds 4.
movl -12(%rbp), %edx

# Add edx into eax.
# eax = eax + edx.
# Since eax = 10 and edx = 4, eax now holds 14.
addl %edx, %eax

# Copy c's value into edx.
# c lives at -8(%rbp), and c currently equals 2.
# edx now holds 2.
movl -8(%rbp), %edx

# Subtract edx from eax.
# eax = eax - edx.
# Since eax = 14 and edx = 2:
# eax = 14 - 2
# eax = 12
subl %edx, %eax

# Store eax into result's memory slot.
# eax currently holds 12.
# result lives at -4(%rbp), so result now equals 12.
movl %eax, -4(%rbp)

# Copy result's value from -4(%rbp) into eax.
# result currently equals 12, so eax now holds 12.
movl -4(%rbp), %eax

# Copy eax into esi.
# eax currently holds 12.
# esi now holds 12.
# cout uses esi as the value to print.
movl %eax, %esi

# Set eax to 0 for this function-call pattern.
# This is not part of the math.
# This does not erase result.
# result is still 12 in memory at -4(%rbp).
# esi still holds 12 for cout to print.
# Still a little confused here need to study the WHY here.
movl $0, %eax

# Print the value in esi.
call cout
```


## Assembly Summary

```asm
eax = a = 10
edx = b = 4
eax = eax + edx = 14
edx = c = 2
eax = eax - edx = 12
result = eax = 12
esi = result = 12
cout prints 12
```

## Expected Output

```text
12
```

Because:

```text
a = 10
b = 4
c = 2

result = a + b - c
result = 10 + 4 - 2
result = 12
```
