#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* VLAN operations: extract parent interface name and VLAN ID */

void getParentName(const char *vlanName, char *ifName)
{
    char *pch = strchr(vlanName, '.');
    if (pch != NULL)
        strncpy(ifName, vlanName, pch - vlanName);
}

int getVlanId(const char *vlanIface)
{
    char *vlanId = strstr(vlanIface, ".");
    if (vlanId == NULL)
        return 1;

    vlanId++;
    return atoi(vlanId);
}

int main(void)
{
    const char *vlanIface = "eth10.11";
    char parentName[16] = {0};
    int vid;

    printf("Interface: %s\n", vlanIface);
    printf("------------------------\n");

    getParentName(vlanIface, parentName);
    printf("Parent interface: %s\n", parentName);

    vid = getVlanId(vlanIface);
    printf("VLAN ID: %d\n", vid);

    return 0;
}
