#ifndef _CLI_H_
#define _CLI_H_

#include <iostream>
#include <string>


class Cli 
{
    public:
        Cli(){}
        virtual ~Cli(){}

        /** 
        *      Abstract class of few cli handlers.  
        *  
        *      @param 1  number of cli args
        *      @param 2  pointer to string of args
        *      @retval   0 if request not created , else 1.
        */ 
        virtual int processCli(int argc , char * argv[]) = 0 ;
};


#endif
