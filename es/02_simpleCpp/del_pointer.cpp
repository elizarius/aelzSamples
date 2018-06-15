#include <iostream>
#include <vector>
#include <string>

using namespace std ;


class Base
{
 public:

 Base() {std::cout<<"BASE CR called"<<std::endl; }
 virtual ~Base() {std::cout<<"BASE DR called"<<std::endl; }

   void printInstance ()
   {

      std::cout<<"printInstance called  "<<std::endl ;
   }
};


int main(void)
{
  int flag = 0  ;

  Base *  MyInstance = new Base  ;

  MyInstance->printInstance () ;
  delete MyInstance ;
  std::cout<<"-----------"<<std::endl<<std::endl ;

  /* Should be printed, famous C++ del pointer trick*/
  if ( MyInstance)
   MyInstance->printInstance () ;

  /* Should not be printed assign to 0 */
  std::cout<<"AELZ second try, expect no prints after that "<<std::endl ;
  MyInstance = 0 ;
  if ( MyInstance)
   MyInstance->printInstance () ;

 return 1;
}

