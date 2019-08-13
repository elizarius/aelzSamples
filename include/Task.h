#ifndef _TASK_H_
#define _TASK_H_

#include "NonCopyable.h"

namespace aelzns {

// Abstract task to be inherited by task executors
class Task : public NonCopyable {
    public:
        Task() {};
        virtual ~Task(){};
        virtual bool execute() = 0;
};
}
#endif
