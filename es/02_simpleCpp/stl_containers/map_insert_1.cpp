#include <iostream>
#include <string>
#include <map>
#include <stdio.h>
#include <time.h>

using namespace std ;

class TestClass
{
    public :
    void test_function()
    {
    std::cout<<"Test function called "<<std::endl ;
    std::cout << __func__ << ": some explanation" <<std::endl;
    }

    private :
};


int main()
{

  typedef map<int,TestClass> Month_map;

  Month_map::const_iterator itr;
  Month_map m_ins ;
  Month_map m_add ;
  time_t s1 , s2;

  TestClass zz ;


 int clo_1 =clock();
 for  (int i =1 ; i<9000000;i++)
  {
  m_add[i] = zz;
  }
  cout<<"AELZ 2 add to container: "<<(clock() - clo_1)<<endl;

  int clo =clock();
  for  (int i =1 ; i<9000000;i++)
  {
   m_ins.insert(Month_map::value_type(i, zz) ) ;
  }
  cout<<"AELZ 1 insert to container: "<<(clock() - clo)<<endl;


  std::cout<<std::endl ;

/*
  for (itr = m_ins.begin(); itr != m_ins.end(); ++itr)
  {
    std::cout<<(*itr).first<<"  "<<(*itr).second<<std::endl ;
  }
 */


 return 0 ;
}
