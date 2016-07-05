#include "Handlers.h"
#include "HelpHandler.h"
#include "InterfaceHandler.h"
#include "UdsServer.h"

using namespace std;

void Handlers::init()
{
mHandlers.insert(argHandlersType::value_type ("help",   new HelpHandler));
mHandlers.insert(argHandlersType::value_type ("udsServer", new UdsServer));
mHandlers.insert(argHandlersType::value_type ("iface",  new InterfaceHandler));
}

/*
*   Get Cli handler instance with argument name as key parameter.
*
*/
Cli * Handlers::getHandler(const char * arg)
{
  std::string temp_str(arg);
  argHandlersType ::iterator theIterator ;

  theIterator = mHandlers.find(temp_str) ;
  if (  theIterator != mHandlers.end() )
  {
    return theIterator->second;
  }
  else
   return 0 ;
}


Handlers::~Handlers()
{
  argHandlersType ::iterator theIt ;
  for (theIt = mHandlers.begin(); theIt != mHandlers.end(); ++theIt)
  {
    delete theIt->second ;
    theIt->second = 0 ;

  }
 mHandlers.clear();

}
