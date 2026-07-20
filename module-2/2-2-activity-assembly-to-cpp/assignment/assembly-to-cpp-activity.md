# CS 410 Assembly to C++ Activity Template

Step 1: Convert the assembly code into C++ code.

Step 2: Explain the function of the converted C++ code.

| Assembly Code | C++ Code | Explanation of Functionality |
| --- | --- | --- |
| `movl   −8(%rbp), %eax` | `int eax = value_at_minus_8;` | An integer variable named eax is created and initialized with the value stored in value_at_minus_8. |
| `sall    $3, %eax` | `eax = eax * 8;` | This multiplies the current value of eax by 8 and then stores the result back into eax. |
| `subl    $3, %eax` | `eax = eax - 3;` | This subtracts 3 from the current value of eax and stores the result back in eax. |
| `movl    %eax, −4(%rbp)` | `value_minus_4 = eax;` | This stores the current value of eax in value_minus_4. At this point, eax contains (value_at_minus_8 * 8) - 3, so value_minus_4 now contains that same result. The original value_at_minus_8 still holds its original value. |
| `movl   −8(%rbp), %eax` | `int eax = value_at_minus_8;` | An integer variable named eax is created, and it holds the value currently stored in value_at_minus_8. |
| `sall    $2, %eax` | `eax *= 4;` | This takes what is currently held in eax, multiplies it by 4, and then stores the new result back in eax. |
| `subl    $1, %eax` | `eax = eax - 1;` | This takes what is currently held in eax, subtracts 1 from it, and then stores the new result back in eax. |
| `leal    7(%rax), %edx` | `int edx = eax + 7;` | rax is the entire 64-bit register, and eax is the lower 32 bits of that same register. At this point, eax holds (value_at_minus_8 * 4) - 1.<br>This takes what is currently held in eax, adds 7 to it, and then stores the new result in edx. The value in eax does not change. |
| `testl   %eax, %eax` | `bool eax_is_negative = (eax < 0);` | In boolean terms, this checks if eax is equal to 0 and if eax is less than 0. The next instruction only uses whether eax is less than 0. The value in eax does not change. |
| `cmovs   %edx, %eax` | `if (eax_is_negative) {`<br>`    eax = edx;`<br>`}` | If the current value held in eax is negative, this takes what is held in edx and stores it in eax. If eax is zero or positive, the value held in eax does not change. |
| `sarl    $3, %eax` | `eax = eax >> 3;` | This takes what is currently held in eax, shifts it 3 places to the right, and then stores the new result back in eax. Shifting 3 places to the right is being used as division by 8. The add 7 and negative check before this make the division round toward 0. |
| `movl    %eax, −4(%rbp)` | `value_minus_4 = eax;` | This stores the current value held in eax in value_minus_4. At this point, value_minus_4 contains ((value_at_minus_8 * 4) - 1) / 8. The original value_at_minus_8 still holds its original value. |
| `movl   −8(%rbp), %eax` | `int eax = value_at_minus_8;` | An integer variable named eax is created, and it holds the value currently stored in value_at_minus_8. |
| `leal    7(%rax), %edx` | `int edx = eax + 7;` | This takes what is currently held in eax, adds 7 to it, and then stores the new result in edx. The value in eax does not change. |
| `testl   %eax, %eax` | `bool eax_is_negative = (eax < 0);` | In boolean terms, this checks if eax is equal to 0 and if eax is less than 0. The next instruction only uses whether eax is less than 0. The value in eax does not change. |
| `cmovs   %edx, %eax` | `if (eax_is_negative) {`<br>`   eax = edx;`<br>`}` | If the current value held in eax is negative, this takes what is held in edx and stores it in eax. If eax is zero or positive, the value held in eax does not change. |
| `sarl    $3, %eax` | `eax = eax >> 3;` | This takes what is currently held in eax, shifts it 3 places to the right, and then stores the new result back in eax. The add 7, negative check, and shift work together like dividing the original value by 8 and rounding toward 0. |
| `movl   −8(%rbp), %edx` | `edx = value_at_minus_8;` | This takes what was previously held in edx and replaces it with the original value stored in value_at_minus_8. |
| `sall    $2, %edx` | `edx *= 4;` | This takes what is currently held in edx, multiplies it by 4, and then stores the new result back in edx. |
| `addl    %edx, %eax` | `eax = eax + edx;` | This takes what is currently held in edx, adds it to what is currently held in eax, and then stores the new result back in eax. |
| `movl    %eax, −4(%rbp)` | `value_minus_4 = eax;` | This stores the current value held in eax in value_minus_4. At this point, value_minus_4 contains (value_at_minus_8 / 8) + (value_at_minus_8 * 4). The original value_at_minus_8 still holds its original value. |
