#include <iostream>
#include <string>

using namespace std ;
 int main()
 {
   int i = 10 ;
   int z = 148 ;
   //const int & ri  = i ;
    int & ri  = i ;
   std::cout <<"Ref  to I ,  ri = "<<ri<<std::endl ;
   i++ ;
   std::cout <<"After I++ ,  ri = "<<ri<<std::endl ;

   ri = z ;

   std::cout <<"referenced anymore ,   ri = "<<ri<<" I = "<<i<<std::endl ;

   std::cout <<"Orig referenced ,   i = "<<i<<std::endl ;


   return 1 ;

 }




