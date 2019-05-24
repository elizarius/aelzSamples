#ifndef _IF_HANDLER_
#define _IF_HANDLER_

#include "cli.h"
#include <string>


/**
 *  Interface CLI handler
 */
class InterfaceHandler : public aelzns::Cli
{
    public:
        InterfaceHandler(): hIface_("./rtcclient iface --if-name  <name>  [--mtu <int>]")
         {};
        virtual int processCli(int argc, char * argv[]);

    private:
        /** interface help message   */
        std::string hIface_;
        std::string ifaceName_ ;

        unsigned int mtuSize_;
        unsigned int ifaceIndex_ ;

        /**
        *  Function sends message to HALI server via uds
        */
        int sendHaliMsg() ;
};

#endif
