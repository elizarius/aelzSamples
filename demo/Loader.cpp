#include "Loader.h"
#include "UdsSocketDemo.h"
#include "FwdList.h"
#include "DomWorker.h"
#include <iostream>

using namespace std;
using namespace aelzns;

void Loader::init() {
  mHandlers.insert(argHandlersType::value_type ("udsSocket", new UdsSocketDemo));
  mHandlers.insert(argHandlersType::value_type ("fwdList", new FwdList));
  mHandlers.insert(argHandlersType::value_type ("simpleSamples", new DomWorker));
}

void Loader::usage() {
  cout<<"Usage ./demo <no_args|handlers>"<<endl;
  cout<<"Handlers:"<<endl;
  argHandlersType::iterator theIt;

  for (theIt = mHandlers.begin(); theIt != mHandlers.end(); ++theIt) {
    cout<<"    "<<theIt->first<<endl;
  }
}
/*
*   Get Cli handler instance with argument name as key parameter.
*/
Cli * Loader::getHandler(const char * arg) {
  std::string temp_str(arg);
  argHandlersType::iterator theIterator;

  theIterator = mHandlers.find(temp_str) ;
  if (theIterator != mHandlers.end()) {
    return theIterator->second;
  }
  else
   return 0 ;
}

void Loader::runAll(int argc, char* argv[]) {
  
  argHandlersType::iterator theIt;
  cout<<endl<<"**  Application demonstrates basic C++ samples and techniques **"<<endl<<endl;

  for (theIt = mHandlers.begin(); theIt != mHandlers.end(); ++theIt) {
    cout<<"***\t"<<theIt->first<<" started\t***"<<endl;
    theIt->second->processCli(argc, argv);
    cout<<"***\t"<<theIt->first<<" finished\t***"<<endl<<endl<<endl;
  }
}

Loader::~Loader() {
  argHandlersType::iterator theIt;
  for (theIt = mHandlers.begin(); theIt != mHandlers.end(); ++theIt) {
    delete theIt->second ;
    theIt->second = 0 ;
  }
  mHandlers.clear();
}
