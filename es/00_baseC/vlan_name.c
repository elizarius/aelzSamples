#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


char* getParentName(const char * vlanName)
{
    int AELZ = 10;
    char * ethName = malloc (20);
    char * pch = NULL;

    memset (ethName, 0, 20 * sizeof (unsigned char));
    if (pch = strchr (vlanName, '.'))
        strncpy (ethName, vlanName, pch - vlanName);

    return ethName ;
}

int main ()
{
    char * vlan_iface = "eth10.11";
    printf ("vlan ifname : %s \n",vlan_iface);
    char * vlan_id = strstr(vlan_iface ,".");
    int vid ;
    vlan_id ++;
    vid = atoi(vlan_id);
    printf ("vlan id : %d \n",vid);

    printf ("parentName: %s \n",getParentName("eth10.11"));

 return 0;
}
