#include <iostream>
#include <functional>

class CallbackSample
{
    public:
        void registerOperation() const {
            std::cout<<"CallbackSample::registerOperation() called"<<std::endl;
        }
};

class CbCaller
{
 public:
    void setCB(std::function<void()> callback) {
        cbFunc = callback;
    }

    int runCBF() {
        if (cbFunc) {
            cbFunc();
        }
        return 0;
    }

 private:
    std::function<void()> cbFunc;
};

int main()
{
    const CallbackSample callback;

    CbCaller cbUser;
    cbUser.setCB(std::bind(&CallbackSample::registerOperation, &callback));
    cbUser.runCBF();

    return 0;
}
