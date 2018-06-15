#include <iostream>
#include <string>


const char *  getSqlCommand(int ctype )
{
    switch (ctype) {
        case 1:  	return const_cast<char *>("1 Called")   ;
        case 2:  	return const_cast<char *>("2 Called")   ;
        case 3:  	return const_cast<char *>("3 Called")   ;
        case 4:  	return const_cast<char *>("4 Called")   ;
        default : 	return const_cast<char *>("UNKNOWN COMMAND'")  ;
    }
}

void print_st(const char * tt , int i )
{
   std::cout<<" i: "<<i<< " : "<<tt<<std::endl ;
}

int main ( )
{
    const char * admincmd = 0 ;
    int i = 0 ;

    for  ( i =1; i<8 ;i++)
    {
        admincmd = getSqlCommand(i ) ;
        print_st (admincmd , i ) ;

    }
    return 1 ;
}
