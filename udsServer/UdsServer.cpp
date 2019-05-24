#include "UdsServer.h"

#include <iostream>
#include <string>

using namespace std;

int UdsServer::processCli(int c, char * argv[])
{
    int  servSock, clientSock ;          /* Socket descriptor for server && client */
    char msgBuffer[RCVBUFSIZE];         /* Buffer for echo string */
    struct sockaddr_un echoServAddr;    /* Local address */

    int msgSize = 0 ;                   /* received message size */
    std::string stop_receiving = argv[0];

    cout<<__PRETTY_FUNCTION__<<": running in server mode..."<<endl;

    /* Create socket for incoming connections */
    if ((servSock = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        cout<<"ERR: server socket() failed"<<endl;
        return 0;
    }

    unlink(UDS_NAME);

    /* clean local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));

    echoServAddr.sun_family = AF_UNIX;
    strcpy(echoServAddr.sun_path,UDS_NAME);

    /* Bind to the uds address */
    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
    {
        cout<<"ERR: UdsServer bind() failed"<<endl;
        return 0;
    }

    /* Mark the socket so it will listen for incoming connections */
    if (listen(servSock, 5) < 0)
    {
        cout<<"ERR: UdsServer listen() failed"<<endl;
        return 0;
    }

    for (;;)
    {
        cout<<__PRETTY_FUNCTION__<<": waiting new client connection..."<<endl;

        /* Wait for a client to connect */
        if ((clientSock = accept(servSock,0,0)) < 0)
        {
            cout<<"ERR: UdsServer accept() failed"<<endl;
            return 0;
        }

        // AELZ_702: clarify diff between write /recv and implement the same for both parts
        /* Receive message from client */
        if ((msgSize = recv(clientSock, msgBuffer, RCVBUFSIZE, 0)) <= 0)
        {
            cout<<"ERR: UdsServer recv() failed"<<endl;
            close(clientSock);
            close(servSock);
            return 0;
        }
        cout<<"received bytes from socket: "<< msgSize<<endl;
        msgBuffer[msgSize] = 0;
        cout <<"Msg from client : "<< msgBuffer<<endl;
        sendResponse(clientSock);
        if (stop_receiving == "exit_after_one") {
            break;        
        }
     } // end for
     close(clientSock);
     close(servSock);

     unlink(UDS_NAME);
     return 0 ;
}

int UdsServer::sendResponse(int sockFd)
{
    char msgBuffer[RCVBUFSIZE];

    int msgSize = sprintf(msgBuffer, "Hi, from server");
    write(sockFd, msgBuffer , msgSize);
    close(sockFd);
    return 0;
}


