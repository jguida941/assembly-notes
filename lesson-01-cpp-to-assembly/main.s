
# C++ to Assembly Mapping Example
# This file uses the course-guide style of assembly: x86-64 GNU/AT&T syntax.
# It maps simple C++ integer assignment and addition into stack slots and registers.

# C++ equivalent:
# int i, j, k;
# i = 2;
# j = 3;
# k = i + j;


.text                    # Start of the code section
.globl main              # Makes main visible to the linker
.type main, @function    # Marks main as a function


# main starts here.
# The program does not start directly at your C++ code. Startup code calls main.
# Because main is a function, it needs its own stack frame for local variables.
# The next two lines save the caller's stack frame and create main's stack frame.

main:                     # main starts here
    pushq %rbp            # Save the old rbp because main is about to replace it
    movq %rsp, %rbp       # Replace rbp with main's stack starting point

    movl $2, -12(%rbp)    # Store 2 in local variable slot at rbp -12
    movl $3, -8(%rbp)     # Store 3 at the memory location rbp - 8
    movl -8(%rbp), %eax   # Copy the value from rbp - 8 into eax.
    movl -12(%rbp), %edx  # Copy the value from rbp -12 into edx.
    addl %edx, %eax       # Add edx to eax; eax now holds 5
    movl %eax, -4(%rbp)   # k = eax

    movl $0, %eax         # Return 0
    popq %rbp             # Put the saved old rbp back
    ret                   # Leave main