#include <stdio.h>

/*
 * C to Assembly Mapping Example
 *
 * This C program matches the assembly file in this lesson.
 * The assembly version shows how these variables are stored in stack slots,
 * copied into CPU registers, added together, and stored back in memory.
 *
 * Suggested comparison:
 *   C variable i  -> assembly stack slot -12(%rbp)
 *   C variable j  -> assembly stack slot -8(%rbp)
 *   C variable k  -> assembly stack slot -4(%rbp)
 */
int main(void)
{
    int i, j, k;   /* These three ints map to three 4-byte stack slots. */

    i = 2;         /* Assembly: movl $2, -12(%rbp) */
    j = 3;         /* Assembly: movl $3, -8(%rbp) */
    k = i + j;     /* Assembly: load i and j into registers, add them, store result in k. */

    printf("%d\n", k);  /* Print k so we can see the result: 5 */

    return 0;      /* Assembly: movl $0, %eax */
}