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
# b lives in -12(%rbp)
movl $4, -12(%rbp

# Move the value 2 into  c's memory slot.
movl $2, -8(%rbp)

movl -16(%rbp), %eax
movl -12(%rbp), %edx
addl %edx, %eax

movl -8(%rbp), %edx
subl %edx, %eax

movl %eax, -4(%rbp)

movl -4(%rbp), %eax
movl %eax, %esi
movl $0, %eax
call cout
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
