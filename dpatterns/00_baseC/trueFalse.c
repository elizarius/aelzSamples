#include <stdio.h>

/* Demonstrate: true/false in C — any non-zero is true, 0 is false */

int main(void)
{
    int TRUE = 1;
    int FALSE = 0;
    int WRONG = -1;

    printf("!TRUE  = %d\n", !TRUE);
    printf("!FALSE = %d\n", !FALSE);
    printf("WRONG = %d\n", WRONG);
    printf("!WRONG = %d\n", !WRONG);

    return 0;
}
