#ifndef _LOADER_H_
#define _LOADER_H_

#include <map>
#include <string>
#include "cli.h"

namespace aelzns
{
  typedef std::map<std::string, Cli *> argHandlersType;

  /*
  *   Cli handlers storage.
  *   Signleton pattern used because handlers could be reachable
  *   from several classes.
  */
  class Loader
  {
    public:
      static Loader& Instance() {
        static Loader ch;
        return ch;
      }

      virtual  ~Loader();
      void init();
      void usage();

      /* run all handlers in loop */
      void runAll(int argc, char* argv[]);
      Cli * getHandler(const char * arg);

    private:
      Loader (){}                             // default ctor is hidden
      Loader(Loader const&);                // copy ctor is hidden
      Loader& operator=(Loader const&);     // assignment op is hidden

    argHandlersType mHandlers;
  };
}
#endif
