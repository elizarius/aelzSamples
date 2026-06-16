#include <stdio.h>
#include <stdint.h>
#include <assert.h>

/** Demonstrate:
   - Assert usage
**/


int main ()
{
    int checkAssert = 1;
    assert (checkAssert != 0);
    printf("Assert pass, value: %d \n", checkAssert);

    return 0;
}
