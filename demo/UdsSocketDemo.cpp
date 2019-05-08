#include "UdsSocketDemo.h"

#include <iostream>
#include <string>
#include <thread>
#include "UdsServer.h"

void udsS(){
    UdsServer us;
    
    /* 
    * Historical function name, actually nothing to cli but socket listener 
    */
    us.processCli(1, 0);
    return;
}

void udsCl(){
    std::cout<<__FUNCTION__<<" ********* Finished  "<<std::endl;
    return;
}

using namespace std;
using namespace aelzns;

UdsSocketDemo::UdsSocketDemo(){}

/* Activate 2 server / client threads and send control to them */  
int UdsSocketDemo::processCli(int c, char * argv[]) {
    thread first(udsS);
    thread second(udsCl);

    first.join();
    second.join();

    return 0;
}
