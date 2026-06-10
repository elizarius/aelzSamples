#include <iostream>
#include <string>

// string parsing to substring example

using namespace std ;


    int main ()
    {

    string vlink("v192.0.0.3-a0.0.0.20");
    size_t pos_start, pos_end ;

     cout << "Full vlink string : "<<vlink<<endl ;

     pos_start =vlink.find("v");
     pos_end =vlink.find("-");
     string vrouter = vlink.substr(pos_start+1, pos_end-pos_start-1);
     cout << "Vrouter : "<<vrouter<<endl ;

     pos_start =vlink.find("a");
     string area = vlink.substr(pos_start+1);
     cout << "transit_area : "<<area<<endl ;


    return 0 ;
    }
