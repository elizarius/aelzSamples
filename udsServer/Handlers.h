#ifndef _HH_H_
#define _HH_H_

#include <map>
#include <string>

#include "cli.h"

typedef std::map<std::string, Cli *> argHandlersType ;

/*
*   Cli handlers storage.
*   Signleton pattern used because handlers should be reachable
*   from several classes.
*/
class Handlers
{
    public:
        static Handlers& Instance() {
          static Handlers ch;
          return ch;
        }

        virtual  ~Handlers();
        void init() ;

        Cli * getHandler(const char * arg);


    private:
      Handlers (){}                             // default ctor is hidden
      Handlers(Handlers const&);                // copy ctor is hidden
      Handlers& operator=(Handlers const&);     // assignment op is hidden

      argHandlersType mHandlers;
};

#endif
