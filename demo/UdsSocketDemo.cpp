#include "UdsSocketDemo.h"

#include <iostream>
#include <string>
#include <thread>
#include "UdsServer.h"
#include "InterfaceHandler.h"


void udsS(){
    UdsServer us;
    
    /* 
    * Historical function name, actually nothing to cli but socket listener 
    */
    char* argus[] = {"exit_after_one" };
    us.processCli(1, argus);
    return;
}

void udsCl(){
    InterfaceHandler ih;
    char* argus[] = {"aelz","--if-name", "zzz" };
    ih.processCli(3, argus);
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
