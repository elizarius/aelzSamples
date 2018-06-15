#include <iostream>
#include <string>

using namespace std ;


int main ( )
{

    
    const char *  zz =   "PRIMARY ALONE" ; 
    string hsb_role = zz;
    
    string temp = "PRIMARY ALONE" ;
   
    if ( temp.c_str() == "PRIMARY ALONE")
        std::cout<<"hsb_role correct OK : " <<hsb_role<<std::endl ;
   else 
      // Probably string with blanks and require extra analysis
      //
      std::cout<<"hsb_role incorrect string received : " <<hsb_role.c_str()<<" "<<hsb_role<<std::endl ;
  
 return 1 ;

}
