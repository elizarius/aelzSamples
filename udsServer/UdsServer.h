#ifndef _UDS_SERVER_
#define _UDS_SERVER_


/**
 *  Unix domain server CLI handler 
 */
#include "cli.h"

#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <cstdio>
#include <cstdlib>

#define RCVBUFSIZE 1024
#define UDS_NAME "./uds_socket"  

class UdsServer : public Cli
{
    public:
        UdsServer(){};
        virtual int processCli(int c, char * argv[]);
        
    private:
        /**
        *  decode and print received data
        *  and send response to client 
        */
        int sendResponse(int sockFd);

};

#endif
