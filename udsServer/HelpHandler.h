#ifndef _HELP_HANDLER_
#define _HELP_HANDLER_

#include "cli.h"


int helpMessage(const char  * msg);

class HelpHandler : public Cli
{
    public:
        HelpHandler();
        virtual int processCli(int c , char * argv[]);
        void usage () ;
    private:
        std::string progName_;

        void design();

};

#endif
