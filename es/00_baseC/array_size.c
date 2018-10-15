#include <stdio.h>
#include <stdint.h>

/** Demonstrate:
   - size of structure
   - size of array of structures
   - default array  initialization
**/

typedef struct sali_ifm_mt_entry_t {
    unsigned char mac_addr[6];
    char          ifname[16];
    uint16_t      bridge_id;

} sali_ifm_mt_entry_t;


int main ()
{
    sali_ifm_mt_entry_t mt_entry[1000];
    printf(" Structure size : %lu \n", sizeof(sali_ifm_mt_entry_t));
    printf(" Array of structures size : %lu \n", sizeof(mt_entry));

    printf(" mac_addr  [25] : %s \n", mt_entry[25].mac_addr);
    printf(" bridge_id [25] : %d \n", mt_entry[25].bridge_id);

    return 0;
}
