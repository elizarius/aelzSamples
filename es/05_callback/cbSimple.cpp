#include <iostream>
#include <functional>

class CallbackSample
{
    public:
        void registerOperation() const {
            std::cout << "CallbackSample::registerOperation() called" << std::endl;
        }
};

int main()
{
    const CallbackSample callback;

    std::function<void()> cb = std::bind(&CallbackSample::registerOperation, &callback);

    if (cb) {
        cb();
    }

    return 0;
}
