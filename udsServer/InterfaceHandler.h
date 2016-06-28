#ifndef _IF_HANDLER_
#define _IF_HANDLER_

#include "cli.h"
//#include "msg.h"


/**
 *  Interface CLI handler 
 */
class InterfaceHandler : public Cli
{
    public:
        InterfaceHandler(): hIface_("./protoclient iface --if-name  <name>  [--mtu <int>]")
         {};
        virtual int processCli(int argc, char * argv[]);

    private:

        int fillInterfaceMsg();

        /** interface help message   */
        std::string hIface_;
        std::string ifaceName_ ;

        unsigned int mtuSize_;
        unsigned int ifaceIndex_ ;

     //   struct hal_msg_if ifMsg_;
        
};

#endif
