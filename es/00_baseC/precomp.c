#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define AELZ_AGE 49

/** Demonstrate:
   - Preprocessor operation
   - run: cpp xx.c
**/


int main ()
{
    int checkAssert = 1;
    assert (checkAssert != 0);
    printf("Assert pass, value: %d \n", checkAssert);
    printf("AELZ age: %d \n", AELZ_AGE);

    return 0;
}
