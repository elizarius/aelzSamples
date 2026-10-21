#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define AELZ_AGE 49

/** Demonstrate:
   - Assert usage
   - Preprocessor operations (#define)
**/

int main(void)
{
    int checkAssert = 1;
    assert(checkAssert != 0);
    printf("Assert pass, value: %d\n", checkAssert);
    printf("AELZ age: %d\n", AELZ_AGE);

    // malloc: allocate memory, uninitialized
    int *ptr1 = malloc(sizeof(int));
    if (ptr1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    *ptr1 = 10;
    printf("Value of ptr1: %d\n", *ptr1);
    free(ptr1);

    return 0;
}
