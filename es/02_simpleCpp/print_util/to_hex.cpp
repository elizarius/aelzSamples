#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

// exampel to print in decimal and hexadecimal format

using namespace std ;

    int main ()
    {
    for(int i=0; i<=1024; i++)
    {
     std::cout<<"I : "<<dec<<i<<"  HEX :  "<<hex<<i<<std::endl ;
    } 

    return 0 ;
    }
