#include <iostream>
#include <functional>

class CallbackSample
{
    public:
        void registerOperation() const {
            std::cout << "CallbackSample::registerOperation() called" << std::endl;
        }
};

// Simple callback function
void simpleCallback() {
    std::cout << "Simple callback executed" << std::endl;
}

// Using for function pointer (modern C++ style)
using FunctionalPtr = void (*)();

// Execute callback using std::function
void executeCallback(std::function<void()> callback) {
    if (callback) {
        callback();
    }
}

// Execute callback using function pointer
void executeCallbackWithFuncPtr(FunctionalPtr funcPtr) {
    if (funcPtr) {
        funcPtr();
    }
}

int main()
{
    std::cout << "=== Class based callback: std::function with std::bind ===" << std::endl;
    const CallbackSample callback;
    std::function<void()> cb = std::bind(&CallbackSample::registerOperation, &callback);
    if (cb) {
        cb();
    }
    std::cout << std::endl;

    std::cout << "=== Basic Function Pointer Example ===" << std::endl;

    // Declare and assign a function pointer
    void (*funcPointer)() = &simpleCallback;

    // Call through function pointer
    funcPointer();

    // Pass function pointer to another function
    executeCallback(simpleCallback);
    std::cout << std::endl;

    std::cout << "=== std::function with Function Pointer ===" << std::endl;

    // Use std::function with function signature
    std::function<void()> funcWrapper = simpleCallback;

    // Call through std::function wrapper
    if (funcWrapper) {
        funcWrapper();
    }

    // Pass function to executeCallback
    executeCallback(funcWrapper);

    return 0;
}
