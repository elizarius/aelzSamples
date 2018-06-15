/*
*   AELZ_01 example to compare strings
*/
#include <iostream>
#include <string>

using namespace std ;


int main ( )
{
    string node_1 = "10.159.9.71" ;
    string node_2 = "11.159.9.75";

    
    if ( node_1  > node_2 ) 
      cout<< "node_1 is >>>>"<<endl ;
     else  
      if ( node_1 < node_2 ) 
        cout<< "node_1 is <<<<<"<<endl ;
       else 
         cout<< "node_1 is ==== node_2"<<endl ;
  
 return 1 ;

}
