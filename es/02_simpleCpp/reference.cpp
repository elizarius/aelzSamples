#include <iostream>
#include <string>

using namespace std ;
 int main()
 {
    int i = 10 ;
    int z = 148 ;
    int & ri  = i ;
    std::cout <<"Ref  to I ,  ri = "<<ri<<std::endl ;
    i++ ;
    std::cout <<"After I++ ,  ri = "<<ri<<std::endl ;

   ri = z ;
   std::cout <<"referenced anymore ,   ri = "<<ri<<" i = "<<i<<std::endl ;
   std::cout <<"Orig i = "<<i<<std::endl ;


   return 0;
 }




