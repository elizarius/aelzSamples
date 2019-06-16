#include <iostream>
#include <string>
#include <map>



using namespace std ;

class Base ;
class sec_class ;

//type of the collection
typedef std::map<std::string,sec_class *> BaseType ;




class sec_class
{
 public:

 sec_class() {std::cout<<" sec_class CR called"<<std::endl; }
 virtual ~sec_class() {std::cout<<"sec_class DR called"<<std::endl; }

   virtual void printInstance ()
   {
    std::cout<<" sec class instance called  "<<std::endl;
   }
};



class Base
{
 public:

 Base() {std::cout<<"BASE CR called"<<std::endl; }
 virtual ~Base() {std::cout<<"BASE DR called"<<std::endl; }

   virtual void printInstance ()
   {

    BaseType::iterator iter = baseMap.begin() ;
    std::cout<<" "<<iter->first<<std::endl ;  
    iter->second->printInstance() ;  
    
   }
   
  
   BaseType baseMap ;

};




void setMap (Base * base_instance )
{
 sec_class *  temp_b = new sec_class ;
 base_instance->baseMap.insert(std::pair<std::string, sec_class *>("First string", temp_b) ) ;
}

     
     


using namespace std ;
   int main()
   {
    
   Base testClass ;
   setMap(&testClass) ;
   testClass.printInstance () ;       
   }




