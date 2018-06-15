#include <iostream>
#include <string>
#include <map>
#include <stdio.h>
#include <time.h>

using namespace std ;
int main()
{

  typedef map<int,const char *> Month_map;

  Month_map::const_iterator itr;
  Month_map m_ins ;
  Month_map m_add ;
  time_t s1 , s2;


 int clo_1 =clock();
 for  (int i =1 ; i<10000000;i++)
  { 
  m_add[i] = "jan";
  }
  cout<<"AELZ 2 :"<<(clock() - clo_1)<<endl;


  
  int clo =clock();
  for  (int i =1 ; i<10000000;i++)
  { 
   m_ins.insert( pair<int, const char *>(i, "jan" ) ) ;
  }
  cout<<"AELZ 1 :"<<(clock() - clo)<<endl;
 

  
//  cout<<"Timediff: "<<s2<<" "<<s1<<"  "<<s2-s1 <<endl;
  

  
  std::cout<<std::endl ;

/*  
  for (itr = m_ins.begin(); itr != m_ins.end(); ++itr)
  {
    std::cout<<(*itr).first<<"  "<<(*itr).second<<std::endl ;
  }
 */ 
  
  
  
 	
 return 0 ;
}
