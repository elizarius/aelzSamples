#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* get vlan id from interface name */
int main ()
{

    char * vlan_iface = "eth10.11";
    printf ("vlan ifname : %s \n",vlan_iface);
    char * vlan_id = strstr(vlan_iface ,".");

    printf ("ifname : %s \n",vlan_id);
    int vid ;
    vlan_id ++;
    vid = atoi(vlan_id);
    printf ("vlan id : %d \n",vid);

  return 0;
}
