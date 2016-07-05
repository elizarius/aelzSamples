#include <iostream>
#include <string>

#include "Handlers.h"
#include "HelpHandler.h"
#include "UdsServer.h"


using namespace std;


int main(int argc, char* argv[])
{

    int respCode= 0 ;

    /** Init cli handlers storage. */
    Handlers & cmdHandlers = Handlers::Instance() ;
    cmdHandlers.init();

    if (argc < 2) {
        std::cout << "CLI input error: not enough arguments"<<std::endl;
        std::cout << "more info ./rtclient help"<<std::endl;
        return 1;
    }

    Cli * cliHandler = cmdHandlers.getHandler(argv[1]);
    if (cliHandler) {
        cliHandler->processCli(argc, argv );
    }

    return 0;
}

