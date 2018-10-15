#include "Handlers.h"
#include "ComponentHandler.h"
#include "GetHandler.h"
#include "ConfigHandler.h"
#include "inbFilter.h"
#include "MplsHandler.h"
#include "bgp.h"
#include "exportRoute.h"
#include "VpnHandler.h"
#include "InterfaceHandler.h"
#include "BGPFlapHandler.h"
#include "ResponseHandler.h"


using namespace std;
using namespace EdgeRoutingMsgAPI;

void Handlers::init() 
{
   mHandlers.insert(argHandlersType::value_type ("component", new ComponentHandler));
   mHandlers.insert(argHandlersType::value_type ("server", new ServerHandler));
   mHandlers.insert(argHandlersType::value_type ("help",   new HelpHandler));
   mHandlers.insert(argHandlersType::value_type ("get",    new GetHandler));
   mHandlers.insert(argHandlersType::value_type ("config", new ConfigHandler));
   mHandlers.insert(argHandlersType::value_type ("inb_filter", new InbFilter));
   mHandlers.insert(argHandlersType::value_type ("export", new ExportHandler));
   mHandlers.insert(argHandlersType::value_type ("bgp", new BGPHandler));
   mHandlers.insert(argHandlersType::value_type ("ospf2_stats", new Ospf2Stats));
   mHandlers.insert(argHandlersType::value_type ("ospfv3Stats", new Ospfv3Stats));
   mHandlers.insert(argHandlersType::value_type ("static", new StaticHandler));
   mHandlers.insert(argHandlersType::value_type ("ospfv3", new Ospfv3Handler));
   mHandlers.insert(argHandlersType::value_type ("ospf",   new OspfHandler));
   mHandlers.insert(argHandlersType::value_type ("mpls", new MPLSHandler));
   mHandlers.insert(argHandlersType::value_type ("labels",   new LabelsHandler));
   mHandlers.insert(argHandlersType::value_type ("mplsif",   new MplsifHandler));
   mHandlers.insert(argHandlersType::value_type ("mplsxc",   new MplsxcHandler));
   mHandlers.insert(argHandlersType::value_type ("ldp",   new LdpHandler));
   mHandlers.insert(argHandlersType::value_type ("mpls_stats",new MplsxcGetHandler));
   mHandlers.insert(argHandlersType::value_type ("vpn",   new VpnHandler));
   mHandlers.insert(argHandlersType::value_type ("iface", new InterfaceHandler));
   mHandlers.insert(argHandlersType::value_type ("ping",   new LspPingHandler));
   mHandlers.insert(argHandlersType::value_type ("flap",   new BGPFlapHandler));
   mHandlers.insert(argHandlersType::value_type ("response",   new ResponseHandler));
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
