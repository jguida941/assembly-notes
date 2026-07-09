# Assembly Notes: Read Two Integers, Subtract, Print Result

## C++ Code

```cpp
int i, j, k;

cin >> i >> j;

k = i - j;

cout << k;


# Read i
leaq -12(%rbp), %rax
movq %rax, %rsi
call cin

# Read j
leaq -8(%rbp), %rax
movq %rax, %rsi
call cin

# Compute k = i - j
movl -12(%rbp), %edx
movl -8(%rbp), %eax
subl %eax, %edx

# Store result into k
movl %edx, %eax
movl %eax, -4(%rbp)

# Print k
movl -4(%rbp), %eax
movl %eax, %esi
call cout
