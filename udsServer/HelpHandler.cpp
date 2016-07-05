#include <iostream>
#include <string>

#include "Handlers.h"
#include "HelpHandler.h"

using namespace std;

HelpHandler::HelpHandler()
{}

int HelpHandler::processCli(int argc , char * argv[])
{
    progName_ = argv[0];

   // Only help without parameters
   if( argc == 2 ) {
        usage();
        return 0 ;
   }

    if (argc > 2) {
        string handler = (argv[2]) ;
        if(handler =="design") design();
    }

    return 0 ;
}


void HelpHandler::usage()
{
    std::cout <<progName_<<" help <handler -h|design> "<< endl<<endl;
    std::cout <<"Examples:"<< endl<<endl;
    std::cout <<"  "<<progName_<<" udsServer"<< endl<<endl;
    std::cout <<"  "<<progName_<<" iface  -h"<< endl<<endl;
    std::cout <<"  "<<progName_<<" iface  --if-name zzz"<< endl<<endl;
}


void HelpHandler::design()
{
    cout <<endl<< "Design: " << endl;
    cout << "-------" << endl<<endl;
    cout << "To develop new cli handler:" <<endl;
    cout << "\t"<<" 1. Design your handler commands " <<endl;
    cout << "\t"<<" 2. Inherite cli handler from abstract Cli class." <<endl;
    cout << "\t"<<"    Handler should implement at least processCli() function " <<endl;
    cout << "\t"<<" 3. Add your handler to mapHandlers in Handlers::init()/Handlers.cpp " <<endl;
    cout << "\t"<<" 4. Add help to own handler with -h option " <<endl;
    cout << "\t"<<" 5. GetHandler class can be used as referenced example" <<endl;

    cout << "In proto example rtclient starts and sends echo request to server" <<endl;
}





