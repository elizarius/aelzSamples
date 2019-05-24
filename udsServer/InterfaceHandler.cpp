#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>

#include "InterfaceHandler.h"

extern "C"
{
#include <getopt.h>
#include <bits/sockaddr.h>
#include <linux/netlink.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <getopt.h>
#include <unistd.h>
}

#define UDS_NAME1 "./uds_socket"


using namespace std;

int InterfaceHandler::processCli(int argc, char * argv[])
{
    struct option InterfaceOptions[]=
    {
        {"if-name", required_argument, 0, 'i'},
        {"if-index",required_argument, 0, 'n'},
        {"mtu",     required_argument, 0, 'm'},
        {"help",    no_argument,       0, 'h'},
        {0, 0, 0, 0}
    };

    int argMust= 0 ;
    int c;
    while(-1 != (c = getopt_long(argc, argv, "i:m:h", InterfaceOptions, NULL)))
    {
        char *tail=NULL;
        switch(c)
        {
            case 'i':
                ifaceName_ = optarg;
                argMust++;
                break ;

            case 'm':
                mtuSize_ = atoi(optarg);
                break ;

            case 'n':
                ifaceIndex_ = atoi(optarg);
                break ;

            case 'h':
                std::cout<<hIface_<<std::endl;
                return 0;

            default:
                cout << "InterfaceManager : unrecognized argument "<<c<<endl;
                return 0 ;
        }

        if (tail && strlen(tail) > 0)
        {
            cout<< "garbage at: "<< tail<<endl;
            return 0;
        }

    } // END WHILE

    if (argMust < 1)
    {
        cout<< "ERR: if-name must present in command"<< endl;
        return 0;
    }
    // AELZ_104: send message , in this case just return req buffer
    sendHaliMsg();

    return 1 ;
}


/**
*  Function sends message to server via uds
*/
int InterfaceHandler::sendHaliMsg()
{
    std::cout <<__PRETTY_FUNCTION__<<" Sending message to Uds Server" << std::endl;
    struct sockaddr_un servAddr;
    int sockFd, msgSize ;
    int respCode = 0 ;

    char msgBuffer[1024];

    /* Create socket for incoming connections */
    if ((sockFd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        cout<<"ERR: client socket() failed"<<endl;
        return 1;
    }

    /* Construct the server address structure */
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sun_family = AF_UNIX;
    strcpy(servAddr.sun_path, UDS_NAME1);

    /* Establish the connection to the HAL server */
    if (connect(sockFd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
    {
        std::cout<<"ERR: client connect failed"<<std::endl;
        close(sockFd);
        return 1;
    }

    msgSize = sprintf(msgBuffer,"Hello from client");
    write(sockFd, msgBuffer, msgSize);

    msgSize = read(sockFd, msgBuffer, 1024);
    msgBuffer[msgSize] = 0 ;
    cout <<__PRETTY_FUNCTION__<<" Response: "<< msgBuffer<<endl;

    return 0;
}

