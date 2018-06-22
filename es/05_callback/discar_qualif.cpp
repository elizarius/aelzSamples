#include <iostream>
#include <string>

class CallbackSample
{
    public:
    /*
    *	Real action executed in Callback
    */
        void  registerOperation() const {
            std::cout<<"CallbackSample::registerOperation() called"<<std::endl ;
        }
};

class CbCaller
{
 public:
    void setCB (const CallbackSample * FF) {
        cbPTR =const_cast<CallbackSample *>(FF);
    }

    int runCBF () {
        cbPTR->registerOperation();
        return 0;
    }

 private :
    const  CallbackSample* cbPTR;

};

int main ( )
{

    const CallbackSample CallBack;

    CbCaller *  CbUser = new  CbCaller;
    CbUser->setCB(&CallBack);
    CbUser->runCBF();

    return 0;
}
