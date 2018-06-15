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
       std::cout << "Der_1: print fucntion called"<<std::endl;
   }
};



int main(void)
{
 int flag = 1   ;
 
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




