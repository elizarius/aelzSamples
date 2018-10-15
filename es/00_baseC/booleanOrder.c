#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/* The order of logical operations to minimize number of parenthes  */


int main ()
{
    int ar1 = 1;
    int ar2 = 0;

    if (!ar1 && !ar2) {
     printf ( "order left right expects 0  \n") ;
   } else {
     printf ( "order left right expects 1  \n") ;
  }

 return 0;
}
