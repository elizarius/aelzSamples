#include <stdio.h>
#include <stdint.h>

/* Bitwise operations example */
int main ()
{
  int  slot_mask = 0xff ;
  int  slot = 3;

  printf ("slot mask before &:      0x%x\n", slot_mask  );

  slot_mask & (1 << slot);
  printf ("slot mask after <</&:    0x%x\n", slot_mask  );

  slot_mask = slot_mask & (1 << slot);
  printf ("slot mask after  = <</&: 0x%x\n", slot_mask  );

  return 0;
}
