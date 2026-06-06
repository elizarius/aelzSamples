#ifndef _TASK_H_
#define _TASK_H_

namespace aelzns {

class Task {
    public:
        Task() = default;
        virtual ~Task() = default;

        Task(const Task&) = delete;
        Task& operator=(const Task&) = delete;

        virtual bool execute() = 0;
};
}
#endif
