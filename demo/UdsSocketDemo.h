#ifndef _UDS_SDEMO_
#define _UDS_SDEMO_

/**
 *  Unix domain server demo
 */
#include "cli.h"
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>

#define RCVBUFSIZE 1024
#define UDS_NAME "./uds_socket"

namespace aelzns
{
  class UdsSocketDemo : public Cli  {
    public:
        UdsSocketDemo();
        virtual int processCli(int c, char * argv[]);

  };
}
#endif
