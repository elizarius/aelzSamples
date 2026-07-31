#include <stdio.h>
#include <assert.h>

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

    return 0;
}
