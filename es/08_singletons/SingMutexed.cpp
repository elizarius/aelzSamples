#include <iostream>
#include <string>
#include <mutex>

/* AELZ traditional singleton with mutex */

std::mutex mtx;

class Singleton
{
  private:
    static Singleton* pInstance;
    Singleton(){}
    Singleton(const Singleton& ){}
    Singleton& operator= (const Singleton&);
    int mModify;


  public:
    static Singleton* Instance();
    void  printInstance(){
        std::cout<<"AELZ singleton with mutex"<<std::endl;
    }

    void setModifieble (int m) {
        mtx.lock();
        mModify = m;
        std::cout<<"Modifieble = " <<mModify<<std::endl;
        mtx.unlock();
    }
};

Singleton* Singleton::Instance()
{
    if (pInstance == 0) {           // is id the first call ?
        pInstance = new Singleton;
    }
    return pInstance;
}


Singleton* Singleton::pInstance = NULL;

int main ()
{
    Singleton* sing = Singleton::Instance();
    sing->printInstance();
    sing->setModifieble(10);
}

