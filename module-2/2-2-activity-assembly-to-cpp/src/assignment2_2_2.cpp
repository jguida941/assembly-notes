#include <iostream>

/*
 * 2-2 Activity: Assembly to C++, Block 2
 *
 * The assembly for this block is in assignment2_2_2.s. Same shape as Block 1:
 * it reads -8(%rbp), does arithmetic, and stores into -4(%rbp). But this one
 * ends in the leal / testl / cmovs / sarl sequence, which is how the compiler
 * writes signed integer division by a power of two.
 *
 * Why that sequence exists: sarl (arithmetic shift right) rounds toward
 * negative infinity, but C++ integer division has to round toward zero. So the
 * compiler makes a copy with 7 added to it (that is, 8 - 1) and only uses that
 * copy when the value is actually negative.
 *
 * Stack slot mapping:
 *   -8(%rbp)  -> value_at_minus_8   (the input)
 *   -4(%rbp)  -> value_minus_4      (the output)
 */
int main()
{
    int value_at_minus_8 = 5;   // Assembly: the value already sitting in -8(%rbp)
    int value_minus_4;          // Assembly: the slot at -4(%rbp), written at the end

    int eax = value_at_minus_8;         // movl   -8(%rbp), %eax   copy the input into eax
    eax = eax * 4;                      // sall   $2, %eax         shift left 2 = multiply by 4
    eax = eax - 1;                      // subl   $1, %eax         subtract 1
    int edx = eax + 7;                  // leal   7(%rax), %edx    edx = eax + 7, eax unchanged
    bool eax_is_negative = (eax < 0);   // testl  %eax, %eax       set the flags from eax
    if (eax_is_negative) {              // cmovs  %edx, %eax       use the +7 copy only if negative
        eax = edx;
    }
    eax = eax >> 3;                     // sarl   $3, %eax         shift right 3 = divide by 8
    value_minus_4 = eax;                // movl   %eax, -4(%rbp)   store the result

    // The block above is the compiler's way of writing one statement:
    //   value_minus_4 = ((value_at_minus_8 * 4) - 1) / 8;

    std::cout << "value_at_minus_8 = " << value_at_minus_8 << "\n";
    std::cout << "value_minus_4    = " << value_minus_4 << "\n";  // (5 * 4 - 1) / 8 = 2

    return 0;
}
