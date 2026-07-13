# CS 410 C++ to Assembly With Loops Activity Template

## Table of Contents

- [Step 1: Explain the functionality of the C++ code.](#step-1-explain-the-functionality-of-the-c-code)
- [Step 2: Convert the C++ file into assembly code.](#step-2-convert-the-c-file-into-assembly-code)
- [Step 3: Align each line of C++ code with the corresponding blocks of assembly code.](#step-3-align-each-line-of-c-code-with-the-corresponding-blocks-of-assembly-code)
- [Step 4: Explain how the blocks of assembly code perform the same tasks as the C++ code.](#step-4-explain-how-the-blocks-of-assembly-code-perform-the-same-tasks-as-the-c-code)

## Step 1: Explain the functionality of the C++ code.

### C++ Code Functionality

```cpp
#include<iostream>
```

Standard library. Allows the program to use input/output/newlines. (cout, cin, endl)

```cpp
using namespace std;
```

Allows usage of the standard library names without having to use std::

```cpp
int main()
```

Where the main function is defined. Program begins its execution here.

```cpp
int num, i;
```

Declares two integers: num, and i

i is for the loop and num stores the number that the user provides to program.

```cpp
int product =1;
```

Declares the integer product. Starts it at 1. This is where the factorial is calculated and stored.

```cpp
cout<<"Enter a number:\n"<< endl;
```

Displays message to user in the terminal. For some reason uses both \n and endl;

This gives two-line breaks.

```cpp
cin>>num;
```

Reads an integer entered by the user in the terminal and stores it in the variable num.

```cpp
for(i=num;i>0; i--)
```

The variable i is initialized with the value stored in num. While i is greater than 0, the loop executes and decreases i by 1 after each iteration.

```cpp
product = product * i;
```

Multiplies the current value of product by i (the current loop-counter value) and stores the result back in product. Repeating this operation calculates the factorial.

```cpp
cout<<"The factorial for " << num << "is: \n"<< product;
```

Prints "The factorial for ", followed by the number entered by the user and "is:". It then starts a new line and displays the calculated factorial stored in product.

```cpp
return 1;
```

Returns an exit status of 1 to the operating system. A nonzero exit status conventionally indicates that the program encountered an error. Because this program reaches this statement after successfully calculating the factorial, return 0; would normally be used to indicate successful completion.

## Step 2: Convert the C++ file into assembly code.

## Step 3: Align each line of C++ code with the corresponding blocks of assembly code.

### C++ to Assembly Alignment

```cpp
#include<iostream>
```

No single direct assembly instruction.

```cpp
using namespace std;
```

No direct assembly instruction.
This is a C++ source-level naming shortcut.

```cpp
int main()
```

```asm
	.text
	.globl	main
	.type	main, @function
main:
.LFB1493:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
```

```cpp
int num, i;
```

No distinct assembly instructions are generated because num and i are declared without initial values. Their stack space is allocated by:

```asm
	subq	$32, %rsp
```

```cpp
int product =1;
```

```asm
	movl	$1, -12(%rbp)
```

```cpp
cout<<"Enter a number:\n"<< endl;
```

```asm
	leaq	.LC0(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
```

```cpp
cin>>num;
```

```asm
	leaq	-20(%rbp), %rax
	movq	%rax, %rsi
	leaq	_ZSt3cin(%rip), %rdi
	call	_ZNSirsERi@PLT
```

```cpp
for(i=num;i>0; i--)
```

```asm
	movl	-20(%rbp), %eax
	movl	%eax, -16(%rbp)
.L3:
	cmpl	$0, -16(%rbp)
	jle	.L2
```

```cpp
product = product * i;
```

```asm
	movl	-12(%rbp), %eax
	imull	-16(%rbp), %eax
	movl	%eax, -12(%rbp)
	subl	$1, -16(%rbp)
	jmp	.L3
```

```cpp
cout<<"The factorial for " << num << "is: \n"<< product;
```

```asm
.L2:
	leaq	.LC1(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	movq	%rdx, %rdi
	call	_ZNSolsEi@PLT
	leaq	.LC2(%rip), %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movq	%rdx, %rdi
	call	_ZNSolsEi@PLT
```

```cpp
return 1;
```

```asm
	movl	$1, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L5
	call	__stack_chk_fail@PLT
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1493:
	.size	main, .-main
```

## Step 4: Explain how the blocks of assembly code perform the same tasks as the C++ code.

### Assembly Functionality

```asm
	.text
	.globl	main
	.type	main, @function
main:
.LFB1493:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
```

This starts the main function. Saves the previous stack frame, creates a new stack frame, reserves 32 bytes for local data, saves a stack-protection value, and sets %eax to zero.

```asm
	subq	$32, %rsp
```

Subtracts 32 from the stack pointer %rsp, reserving 32 bytes of stack space for the local variables.

```asm
	movl	$1, -12(%rbp)
```

Stores the value 1 at -12(%rbp), which is the stack location used for the product variable in the C++ code.

This initializes product to 1.

```asm
	leaq	.LC0(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
```

I determined that .LC0 contains "Enter a number:\n" because it is defined earlier as .string "Enter a number:\n". This instruction loads the address of that string into %rsi.

I identified _ZSt4cout as cout because the name cout appears inside the symbol. This instruction loads the address of cout into %rdi.

I identified this as the string-output operation because it is called immediately after the program loads .LC0 and cout. Therefore, this call prints "Enter a number:\n" through cout.

This saves the returned cout stream from %rax into %rdx so it can be used by the next output operation.

I identified this as endl because _ZSt4endl appears near the beginning of the symbol. The long char_traits and basic_ostream text is compiler-generated C++ type information. GOTPCREL(%rip) tells the processor how to locate the external endl function.

The previous instruction loaded the address of endl into %rax. This instruction copies that address from %rax into %rsi, which is the register used to pass the second argument to the next function call.

The earlier output call returned a reference to the cout stream in %rax, and that value was saved in %rdx. This instruction copies the saved stream reference from %rdx into %rdi, which is the register used to pass the first argument to the next function call.

This call performs cout << endl. It inserts the second newline and flushes the output stream. The first newline was already printed as part of the string "Enter a number:\n", so the complete C++ statement produces two newlines.

```asm
	leaq	-20(%rbp), %rax
	movq	%rax, %rsi
	leaq	_ZSt3cin(%rip), %rdi
	call	_ZNSirsERi@PLT
```

leaq -20(%rbp), %rax loads the address of num into %rax. movq %rax, %rsi moves that address into %rsi so it can be passed to the input function. I identified this as input because _ZSt3cin contains cin.

Its address is loaded into %rdi, and the final call reads an integer from the user and stores it at -20(%rbp).

```asm
	movl	-20(%rbp), %eax
	movl	%eax, -16(%rbp)
.L3:
	cmpl	$0, -16(%rbp)
	jle	.L2
```

movl -20(%rbp), %eax loads the value of num into %eax. I know -20(%rbp) is num because cin stored the user input at -20(%rbp).

movl %eax, -16(%rbp) copies that value into -16(%rbp). This makes i equal to num, matching i = num in the for loop.

.L3 is a label that marks the top of the loop. The program jumps back to this label after each loop cycle. cmpl $0, -16(%rbp) compares i to 0. I know -16(%rbp) is i because the previous instruction stored num there for the loop counter.

jle .L2 means jump to .L2 if i is less than or equal to 0. This is how the assembly exits the loop when i > 0 is no longer true.

```asm
	movl	-12(%rbp), %eax
	imull	-16(%rbp), %eax
	movl	%eax, -12(%rbp)
	subl	$1, -16(%rbp)
	jmp	.L3
```

movl -12(%rbp), %eax loads product into %eax. I know -12(%rbp) is product because product was initialized earlier with movl $1, -12(%rbp).

imull -16(%rbp), %eax multiplies %eax by i. Since %eax currently holds product and -16(%rbp) holds i, this performs product * i.

movl %eax, -12(%rbp) stores the multiplication result back into product. This matches product = product * i.

subl $1, -16(%rbp) subtracts 1 from i. This matches i-- in the for loop.

jmp .L3 jumps back to the top of the loop so the condition can be checked again.

```asm
.L2:
	leaq	.LC1(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	movq	%rdx, %rdi
	call	_ZNSolsEi@PLT
	leaq	.LC2(%rip), %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movl	-12(%rbp), %eax
	movl	%eax, %esi
	movq	%rdx, %rdi
	call	_ZNSolsEi@PLT
```

.L2 is where the program goes after the loop finishes.

leaq .LC1(%rip), %rsi loads the string "The factorial for ".

leaq _ZSt4cout(%rip), %rdi loads cout.

The call after that prints "The factorial for ".

movq %rax, %rdx saves cout so the program can keep printing on the same line.

movl -20(%rbp), %eax loads num. I know -20(%rbp) is num because cin stored the user input there.

movl %eax, %esi prepares num to be printed

movq %rdx, %rdi restores cout.

call _ZNSolsEi@PLT prints num.

leaq .LC2(%rip), %rsi loads the string "is: \n".

movq %rax, %rdi keeps using cout.

The next call prints "is: \n".

movq %rax, %rdx saves cout again.

movl -12(%rbp), %eax loads product. I know -12(%rbp) is product because product was initialized there earlier.

movl %eax, %esi prepares product to be printed.

movq %rdx, %rdi restores cout.

call _ZNSolsEi@PLT prints product, which is the factorial answer.

```asm
	movl	$1, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L5
	call	__stack_chk_fail@PLT
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1493:
	.size	main, .-main
```

movl $1, %eax sets the program’s return value to 1.

movq -8(%rbp), %rcx loads the saved stack-check value.

xorq %fs:40, %rcx checks if the stack-check value changed.

je .L5 jumps to .L5 if the stack check passed.

call __stack_chk_fail@PLT runs only if the stack check failed.

.L5 is the normal ending path.

leave removes the stack frame.

ret returns from main.

The final .cfi, .LFE, and .size lines are compiler metadata marking the end of main.
