#include <stdio.h>
#include "endian_sizes.h"

/***************************************************
*
*  Demo:
*  - print OS / Architecture info
*  - print different sizes
*
*  Start on different platforms to see difference
*
*
****************************************************/

int main(void)
{
    struct utsname uts;

    printf("Print system information\n");
    printf("------------------------\n");

    if (uname(&uts) < 0) {
        printf("Error: impossible to fetch system information\n");
    } else {
        printf("System name :  %s\n", uts.sysname);
        printf("Node name   :  %s\n", uts.nodename);
        printf("Release     :  %s\n", uts.release);
        printf("Version     :  %s\n", uts.version);
        printf("Machine     :  %s\n\n", uts.machine);
    }

    printf("Most usable sizes :\n");
    printf("------------------------\n");
    printf("Integer   :  %zu\n", sizeof(int));
    printf("Int32_t   :  %zu\n", sizeof(int32_t));
    printf("ENUM      :  %zu\n\n", sizeof(lm_response_status));

    printf("Custom sizes :\n");
    printf("------------------------\n");
    printf("lm_hello    :  %zu\n", sizeof(lm_hello));
    printf(" -int_32t   :  %zu\n", sizeof(int32_t));
    printf(" -time_t    :  %zu\n", sizeof(time_t));

    return 0;
}
