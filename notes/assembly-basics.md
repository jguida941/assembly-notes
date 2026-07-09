# Assembly Notes: Read Two Integers, Subtract, Print Result

- I rewrote the example in my own words so each assembly instruction explains whether it is working with an address or a value.

## C++ Code

```cpp
int i, j, k;

cin >> i >> j;

k = i - j;

cout << k;
```

## Assembly

```
# Read i

# Get i's memory address.
# rax now holds the location where i is stored, not i's value.
# leaq is the instruction that gets the memory address.
leaq -12(%rbp), %rax

# Put i's address where cin expects the input destination: %rsi.
# rsi now also holds the address of i.
movq %rax, %rsi

# Read user input and store it into the address in rsi.
# Since rsi holds i's address, this writes the input into i.
call cin


# Read j

# Get j's memory address.
# rax now holds the location where j is stored, not j's value.
# leaq is the instruction that gets the memory address.
leaq -8(%rbp), %rax

# Put j's address where cin expects the input destination: %rsi.
# rsi now also holds the address of j.
movq %rax, %rsi

# Read user input and store it into the address in rsi.
# Since rsi holds j's address, this writes the input into j.
call cin
```

