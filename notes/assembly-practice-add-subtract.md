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
movl $4, -12(%rbp)

# Store the value 2 into c's memory slot.
movl $2, -8(%rbp)

# movl -16(%rbp) which is a and holds 10, to the eax %register
# eax now holds 10
movl -16(%rbp), %eax

# movl -12(%rbp) which is b and holds 4, to the edx %register
# edx now holds 4 
movl -12(%rbp), %edx

# Add edx into eax.
# eax = eax + edx.
# Since eax = 10 and edx = 4, eax now holds 14.
addl %edx, %eax

# Move C which holds value 2 to edx register
# edx now holds 2
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
