// Block 3, the assembly exactly as given in the 2-2 Activity: Assembly to C++.
//
//   -8(%rbp) is the input variable  (called value_at_minus_8 in the write-up)
//   -4(%rbp) is the output variable (called value_minus_4 in the write-up)

	movl	-8(%rbp), %eax
	leal	7(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$3, %eax
	movl	-8(%rbp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
