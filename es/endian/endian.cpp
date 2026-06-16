#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std ;

int main(int argc, char **argv)
{
    if (argc !=2)
    {
        std::cout<<"Usage : "<<argv[0]<<" number"<<std::endl;
        return 0 ;
    }

    int  conv_number = atoi ( argv[1] ) ;
    std::cout<<"Host order: "<<conv_number<<"   "<<std::hex<< conv_number<<std::endl;
    std::cout<<"Network order :"<<htons(conv_number)<<"   "<<std::hex<<htons(conv_number)<<std::endl;

    char  loc [4] ;
    loc [0] = conv_number ;
    std::cout<<"In memory:   "<<std::hex<<loc<<std::endl;
}




