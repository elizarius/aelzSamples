/*
*
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <string.h>
#include<bitset>

using namespace std ;


int main ()
{
    unsigned char mask[4] ;
    memset (mask , 0x01, 4) ;

    unsigned char  m1 ;
    int count , c1=0; ;

    for ( int i = 0 ; i<4 ; i++)
    {
        for (count = 0, m1 = 0x80; m1 != 0; m1 >>= 1)
        {
            if (mask[i] & m1)
            count++;
        }
        c1=c1+count;
    }

    cout<<"Counter "<< c1<<endl;


    return 0 ;
}
