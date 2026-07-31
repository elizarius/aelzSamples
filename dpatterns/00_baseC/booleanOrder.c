#include <stdio.h>

/* The order of logical operations to minimize number of parentheses */

int main()
{
    int val1 = 1;
    int val2 = 0;

    if (!val1 && !val2) {
        printf("order left right expects 0\n");
    } else {
        printf("order left right expects 1\n");
    }
    return 0;
}
