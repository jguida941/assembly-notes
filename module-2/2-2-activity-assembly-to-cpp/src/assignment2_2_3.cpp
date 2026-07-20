#include <iostream>

/*
 * 2-2 Activity: Assembly to C++ — Block 3
 *
 * The assembly for this block is in assignment2_2_3.s. This one reads
 * -8(%rbp) twice: once into eax, where it gets divided by 8 using the same
 * leal / testl / cmovs / sarl round-toward-zero sequence as Block 2, and once
 * into edx, where it gets multiplied by 4. The two halves are then added.
 *
 * Stack slot mapping:
 *   -8(%rbp)  -> value_at_minus_8   (the input, read twice)
 *   -4(%rbp)  -> value_minus_4      (the output)
 */
int main()
{
    int value_at_minus_8 = 5;   // Assembly: the value already sitting in -8(%rbp)
    int value_minus_4;          // Assembly: the slot at -4(%rbp), written at the end

    int eax = value_at_minus_8;         // movl   -8(%rbp), %eax   copy the input into eax
    int edx = eax + 7;                  // leal   7(%rax), %edx    edx = eax + 7, eax unchanged
    bool eax_is_negative = (eax < 0);   // testl  %eax, %eax       set the flags from eax
    if (eax_is_negative) {              // cmovs  %edx, %eax       use the +7 copy only if negative
        eax = edx;
    }
    eax = eax >> 3;                     // sarl   $3, %eax         shift right 3 = divide by 8

    edx = value_at_minus_8;             // movl   -8(%rbp), %edx   re-read the ORIGINAL input
    edx = edx * 4;                      // sall   $2, %edx         shift left 2 = multiply by 4
    eax = eax + edx;                    // addl   %edx, %eax       add the two halves together
    value_minus_4 = eax;                // movl   %eax, -4(%rbp)   store the result

    // The block above is one statement:
    //   value_minus_4 = (value_at_minus_8 / 8) + (value_at_minus_8 * 4);

    std::cout << "value_at_minus_8 = " << value_at_minus_8 << "\n";
    std::cout << "value_minus_4    = " << value_minus_4 << "\n";  // 5/8 + 5*4 = 0 + 20 = 20

    return 0;
}
