#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


void getParentName(const char * vlanName, char * ifName)
{
    char *pch = strchr (vlanName, '.');
    if (pch != NULL)
        strncpy (ifName, vlanName , pch - vlanName);

}

int main ()
{
    char if_name [16];
    memset (if_name, 0, 16 * sizeof (unsigned char));

    getParentName("eth10.11",if_name);
    printf ("parentName: %s \n",if_name);

 return 0;
}
