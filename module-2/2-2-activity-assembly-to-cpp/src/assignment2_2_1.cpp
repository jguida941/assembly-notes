#include <iostream>

/*
 * 2-2 Activity: Assembly to C++, Block 1
 *
 * The assembly for this block is in assignment2_2_1.s. It reads one int out of
 * the stack slot -8(%rbp), does arithmetic in registers, and stores the result
 * into -4(%rbp). So the whole block is a single C++ assignment statement.
 *
 * Stack slot mapping:
 *   -8(%rbp)  -> value_at_minus_8   (the input)
 *   -4(%rbp)  -> value_minus_4      (the output)
 */
int main()
{
    int value_at_minus_8 = 5;   // Assembly: the value already sitting in -8(%rbp)
    int value_minus_4;          // Assembly: the slot at -4(%rbp), written at the end

    int eax = value_at_minus_8; // movl  -8(%rbp), %eax   copy the input into eax
    eax = eax * 8;              // sall  $3, %eax         shift left 3 = multiply by 8
    eax = eax - 3;              // subl  $3, %eax         subtract 3
    value_minus_4 = eax;        // movl  %eax, -4(%rbp)   store the result

    // The four lines above collapse to one statement:
    //   value_minus_4 = (value_at_minus_8 * 8) - 3;

    std::cout << "value_at_minus_8 = " << value_at_minus_8 << "\n";
    std::cout << "value_minus_4    = " << value_minus_4 << "\n";  // 5 * 8 - 3 = 37

    return 0;
}
