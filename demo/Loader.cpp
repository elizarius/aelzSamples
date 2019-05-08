#include "Loader.h"
#include "UdsSocketDemo.h"
#include <iostream>

using namespace std;
using namespace aelzns;

void Loader::init() {
  mHandlers.insert(argHandlersType::value_type ("udsSocket", new UdsSocketDemo));
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
  for (theIt = mHandlers.begin(); theIt != mHandlers.end(); ++theIt) {
    cout<<"******  Handler started: "<<theIt->first<<endl<<endl;
    theIt->second->processCli(argc, argv);
    cout<<"******  Handler completed: "<<theIt->first<<endl<<endl;
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
