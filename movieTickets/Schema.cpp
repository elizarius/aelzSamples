#include "Schema.h"
#include "UsersDb.h"
#include "TheatersDb.h"
#include "SessionsDb.h"
#include <iostream>

using namespace std;
using namespace movie;

void Schema::init() {
  _handlers.insert(argHandlersType::value_type ("users", new UsersDb));
  _handlers.insert(argHandlersType::value_type ("theaters", new TheatersDb));
  _handlers.insert(argHandlersType::value_type ("theaters", new SessionsDb));
}

/**
 *   Get db  instance with argument name as key parameter.
 */
Db* Schema::getHandler(std::string arg) {
  argHandlersType::iterator theIt;
  theIt = _handlers.find(arg) ;
  if (theIt != _handlers.end()) {
    return theIt->second;
  }
  else
   return 0 ;
}

Schema::~Schema() {
  argHandlersType::iterator theIt;
  for (theIt = _handlers.begin(); theIt != _handlers.end(); ++theIt) {
    delete theIt->second;
    theIt->second = 0;
  }
  _handlers.clear();
}
