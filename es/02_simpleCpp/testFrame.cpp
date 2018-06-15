#include <iostream>
#include <string>

using namespace std;

class TestClass
{
 public :
 void F1()
 {
  std::cout<<"Test function  F1 "<<std::endl ;
 }

 void F2()
 {
  std::cout<<"Test function  F2 "<<std::endl ;
 }

 void F3()
 {
  std::cout<<"Test function  F3 "<<std::endl ;
 }



private :
};


int main ()
{ 
   TestClass tt ;
   tt.F1() ;	
   tt.F2() ;
   tt.F3() ;
 
  return  0 ;
}

