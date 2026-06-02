#ifndef _DOM_WORKER_H_
#define _DOM_WORKER_H_

/**
 *  Elementary samples sourced from codility and dome
 *  exercises
 */

#include "cli.h"
#include "Task.h"
#include <list>

namespace aelzns {
  class DomWorker : public Cli  {
    public:
      DomWorker();
      virtual ~DomWorker();
      virtual int processCli(int c, char * argv[]);

    private:
      std::list<Task *> _tasks;
  };
}
#endif
