#include <iostream>
#include <vector>
#include <string>

// Example how to cast to void  from class type

using namespace std ;

class Base
{
 public:

 Base() {std::cout<<"BASE CR called"<<std::endl; }
 virtual ~Base() {std::cout<<"BASE DR called"<<std::endl; }

   virtual void printInstance ()
   {

      std::cout<<"Base : printInstance"<<std::endl ;

   }

};



class Der_1: public Base
{
 public:

   Der_1 () {std::cout<<"Der_1 CR called"<<std::endl; }
   virtual ~Der_1() {std::cout<<"Der_1  DR called"<<std::endl; }

   void printInstance()
   {
       std::cout << "Der_1: print function called"<<std::endl;
   }
};



int main(void)
{
    Base* MyInstance = new Der_1 ;

    void* vpt_ = reinterpret_cast<Base *>(MyInstance) ;
    //vpt_->printInstance () ;

    std::cout << "AELZ step 1 pass ------"<<std::endl;
    reinterpret_cast<Base *>(vpt_)->printInstance () ;
    delete MyInstance ;


    return 1;

}




