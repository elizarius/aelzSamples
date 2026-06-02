#ifndef _LOADER_H_
#define _LOADER_H_

#include <map>
#include <string>
#include <memory>
#include "cli.h"

namespace aelzns
{
  using HandlerMap = std::map<std::string, std::unique_ptr<Cli>>;

  class Loader
  {
    public:
      static Loader& Instance() {
        static Loader instance;
        return instance;
      }

      ~Loader();
      void init();
      void usage();
      void runAll(int argc, char* argv[]);
      Cli* getHandler(const std::string& arg);

      Loader(const Loader&) = delete;
      Loader& operator=(const Loader&) = delete;

    private:
      Loader() = default;
      HandlerMap mHandlers;
  };
}
#endif
