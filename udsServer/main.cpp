#include <iostream>
#include <string>

#include "Handlers.h"
#include "HelpHandler.h"
#include "UdsServer.h"


using namespace std;

/** 
*  Function sends message to HALI via uds
*/
int sendHaliMsg()
{
    std::cout << "Sending message to HALI" << std::endl;
    struct sockaddr_un servAddr;
    int sockFd, msgSize ;
    int respCode = 0 ;
    char msgBuffer[RCVBUFSIZE];

    /* Create socket for incoming connections */
    if ((sockFd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        cout<<"ERR: client socket() failed"<<endl;
        return 1; 
    }

    /* Construct the server address structure */
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sun_family = AF_UNIX;                
    strcpy(servAddr.sun_path,UDS_NAME);

    /* Establish the connection to the HAL server */
    if (connect(sockFd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)
    {
        std::cout<<"ERR: client connect failed"<<std::endl;
        close(sockFd);
        return 1; 
    }

    msgSize = sprintf(msgBuffer,"Hello from client");
    write(sockFd, msgBuffer, msgSize);

    msgSize = read(sockFd, msgBuffer, RCVBUFSIZE);
    msgBuffer[msgSize] = 0 ;
    cout <<"Response: "<< msgBuffer<<endl;

    return 0;
}


int main(int argc, char* argv[])
{

    // std::string msg, req;
    int respCode= 0 ;

    /** Init cli handlers storage. */ 
    Handlers & cmdHandlers = Handlers::Instance() ;
    cmdHandlers.init();

    if (argc < 2 )
    {
        std::cout << "CLI input error: not enough arguments"<<std::endl;
        std::cout << "more info ./rtclient help"<<std::endl;
        return 1;
    }

    Cli * cliHandler = cmdHandlers.getHandler(argv[1]);

    if (cliHandler)
    {
        std::cout<<"Starting with argument :  "<< argv[1]<<std::endl;

        if (cliHandler->processCli(argc , argv ))
        {
            respCode=sendHaliMsg();
        }
    }

    return respCode;
} 

