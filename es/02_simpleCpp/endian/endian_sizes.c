#include <stdio.h>
#include "endian_sizes.h"

/***************************************
*
*  Demo how different sizes can differs for different 
*  hardware architectures . 
*  Start on dedicated platform . 
*
*  exqample: also to print system and processor info, linux version
*
*
****************************************/


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
 printf("Integer   :  %u \n" , sizeof(int) );
 printf("Int32_t   :  %u \n" , sizeof(int32_t) );
 printf("ENUM      :  %u \n\n" , sizeof(lm_response_status) );    
 

 printf("Custom sizes :  \n");
 printf("------------------------ \n");
 printf("lm_hello    :  %u \n" , sizeof(lm_hello) );  
 printf(" -int_32t   :  %u \n" , sizeof(int32_t)  );    
 printf(" -time_t    :  %u \n" , sizeof(time_t)  );    
}




