#include <iostream>
#include <string>
#include <map>


using namespace std;


// example: use map for sorting

int main()
{
typedef  map<int, char *> Month_map;

 Month_map::const_iterator itr;
 Month_map months ;


  months.insert( pair<int, char *>(1, const_cast<char *>("jan" ))) ;
  months.insert( pair<int, char *>(2, const_cast<char *>("feb" ))) ;
  months.insert( pair<int, char *>(3, const_cast<char *>("mar" )) ) ;
  months.insert( pair<int, char *>(4, const_cast<char *>("apr" ))) ;
  months.insert( pair<int, char *>(5, const_cast<char *>("may" ))) ;
  months.insert( pair<int, char *>(6, const_cast<char *>("jun" ))) ;
  months.insert( pair<int, char *>(7, const_cast<char *>("jul" ))) ;
  months.insert( pair<int, char *>(8, const_cast<char *>("aug "))) ;
  months.insert( pair<int, char *>(9, const_cast<char *>("sep" ))) ;
  months.insert( pair<int, char *>(10,const_cast<char *>("oct" ))) ;
  months.insert( pair<int, char *>(11,const_cast<char *>( "nov" )) ) ;
  months.insert( pair<int, char *>(12,const_cast<char*>("dec ")) ) ;


  std::cout<<std::endl ;

  for (itr = months.begin(); itr != months.end(); ++itr)
  {
    std::cout<<(*itr).first<<"  "<<(*itr).second<<std::endl ;
  }
    std::cout<<std::endl ;

 return 0 ;
}
