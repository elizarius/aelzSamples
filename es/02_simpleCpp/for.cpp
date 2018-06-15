#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>


using namespace std ;

   void printBuf()
    {
      int i;
      for(i=0; i<5; i++)
     {
      std::cout<<"Value : "<<i<<std::endl ;
     }

    std::cout<<"AELZ step 1 ******"<<std::endl ;

      for(i=0; i<5; ++i)
     {
      std::cout<<"Value : "<<i<<std::endl ;
     }
   }

    int main ()
    {

    printBuf( ) ;
    return 0 ;
    }
