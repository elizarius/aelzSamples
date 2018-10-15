#include <stdio.h>
#include "endian_sizes.h"

/***************************************************
*
*  Demo:
*  - print OS / Architecture info
*  - print different sizes
*
*  Start on differnt platforms to see difference
*
*
****************************************************/

int main(int argc, char **argv)
{
    struct utsname uts ;

    printf("Print system information \n");
    printf("------------------------ \n");

    if ( uname(&uts) < 0 ) {
     printf("Error : impossible to fetch system information \n");
    }
    else
    {
     printf("System name :  %s \n" , uts.sysname );
     printf("Node name   :  %s \n" , uts.nodename);
     printf("Release     :  %s \n" , uts.release);
     printf("Version     :  %s \n" , uts.version);
     printf("Machine     :  %s \n\n" , uts.machine);
    }

 printf("Most usable sizes :  \n");
 printf("------------------------ \n");
 printf("Integer   :  %li \n" , sizeof(int) );
 printf("Int32_t   :  %li \n" , sizeof(int32_t) );
 printf("ENUM      :  %lu \n\n" , sizeof(lm_response_status) );

 printf("Custom sizes :  \n");
 printf("------------------------ \n");
 printf("lm_hello    :  %lu \n" , sizeof(lm_hello) );
 printf(" -int_32t   :  %lu \n" , sizeof(int32_t)  );
 printf(" -time_t    :  %lu \n" , sizeof(time_t)  );

 return 0;
}




