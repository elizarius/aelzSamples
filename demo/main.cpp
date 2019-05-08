#include <iostream>
#include <string>
#include "cli.h"
#include "Loader.h"

using namespace std;
using namespace aelzns;

int main(int argc, char* argv[])
{
    /** Init cli handlers storage. */
    Loader & loader = Loader::Instance();
    loader.init();


    if (argc == 1) {
        loader.runAll(argc, argv);
        return 0;
      }
    if (argc > 1) {
      string arg = argv[1];
      if ((arg == "-h") || (arg == "--help")) {
        loader.usage();
        return 0;
      } else {
          Cli * cliHandler = loader.getHandler(argv[1]);
          if (cliHandler) {
            cliHandler->processCli(argc, argv );
          }
          else  {
            cout<<"****** Error: wrong  handler:"<<argv[1]<<endl;
          }
      }
    }

    return 0;
}

