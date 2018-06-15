#include <iostream>
#include <string>

using namespace std ;

int main ( )
{

  
string catalog = "dba" ;
char * uid_ 	= const_cast<char *>("dba") ;
char * pwd_ 	= const_cast<char *>("dba") ;  

//************************************************
//

  string cat_identifier  = "-C" ;
  string user_identifier = "-U" ;
  string pwd_identifier = "-P" ;

cat_identifier =  cat_identifier+catalog ;
user_identifier = user_identifier+uid_ ;
pwd_identifier =  pwd_identifier+pwd_ ;

std ::cout<<cat_identifier.c_str() << std::endl ;
std ::cout<<user_identifier.c_str() << std::endl ;
std ::cout<<pwd_identifier.c_str() << std::endl ;

 return 1 ;

}
