#ifndef _FWD_LIST_
#define _FWD_LIST_

/**
 *  Forwarding list demo example 
 */
#include "cli.h"

namespace aelzns
{
  class FwdList : public Cli  {
    public:
        FwdList() {};
        ~FwdList(){};
        virtual int processCli(int c, char * argv[]);
  };
}
#endif
