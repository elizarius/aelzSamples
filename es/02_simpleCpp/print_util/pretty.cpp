#include <iostream>
#include <vector>
#include <string>

using namespace std ;

class Base
{
 public:

 Base() {std::cout<<"BASE CR called"<<std::endl; }
 virtual ~Base() {std::cout<<"BASE DR called"<<std::endl; }
   virtual void printInstance ()
   {
      std::cout<<__PRETTY_FUNCTION__<<" pretty function called "<<std::endl ;
      std::cout<<__FUNCTION__<<"   __FUNCTION called  "<<std::endl ;
   }

};



class Der_1: public Base
{
 public:

   Der_1 () {std::cout<<"Der_1 CR called"<<std::endl; }
   virtual ~Der_1() {std::cout<<"Der_1  DR called"<<std::endl; }

   void printInstance()
   {
      std::cout<<__PRETTY_FUNCTION__<<" __PRETTY_FUNCTION_ called "<<std::endl ;
      std::cout<<__FUNCTION__<<" __FUNCTION__  called "<<std::endl ;

   }
};



int main(void)
{
 int flag = 0  ;

 Base *  MyInstance =0 ;

 if ( flag)
 {
   MyInstance = new Base  ;
 }
 else
 {
   MyInstance = new Der_1 ;
 }

  MyInstance->printInstance () ;
  delete MyInstance ;
  return 1;

}




