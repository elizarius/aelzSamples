#include <iostream>
#include <string>
#include <unistd.h>

using namespace std ;
   int main()
   {
    int i = 0 ;
    bool status = true ;

    while (status)
    {
        std::cout<< "Loop iteration  called :" <<i++<<std::endl ;
        sleep (1) ;
        if (i >8) {
            status =false;
        }
    }

    return 1;

   }




