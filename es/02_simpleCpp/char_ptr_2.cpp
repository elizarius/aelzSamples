#include <iostream>
#include <string>
#include <cstring>


char *   getSqlCommand(char * req_ptr  )
{

    req_ptr = new char (20);

    /* Actually, const_char<char *> coult be used */
    req_ptr = "My print string  ";

    std::cout<<"In subfunction   "<<std::endl<<req_ptr<<std::endl;
 return  req_ptr ;

}

int main ( )
{
    char * ptr_ = getSqlCommand(ptr_ );

    std::cout<<"In main"<<std::endl<<ptr_<<std::endl;
    std::cout<<std::endl<<"size PTR_"<<sizeof(ptr_)<<std::endl;
    std::cout<<"strle PTR: "<<strlen(ptr_)<<std::endl;
    return 1 ;

}
