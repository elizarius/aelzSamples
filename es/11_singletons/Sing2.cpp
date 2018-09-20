#include <iostream>
#include <string>


/* DON'T FORGET ABOUT DELETE IN DESTRUCTOR 
   NOT DONE IN THIS EXAMPLE  */

/* AELZ traditional singleton with pointer */

class Singleton
{
private:
 static Singleton* pinstance ;

protected :
 Singleton(){}
 Singleton(const Singleton& ){}
 Singleton& operator= (const Singleton&);
 
public:
 static Singleton* Instance();
 void  printInstance(){
    std::cout<<"AELZ singleton with pointer , print instance"<<std::endl;
 }
};

Singleton* Singleton::pinstance = NULL ;

 Singleton* Singleton::Instance()
 {
  if (pinstance == 0) // is id the first call ?
   {
   pinstance = new Singleton ; //create sole instance 
   }
  return pinstance ; 
 }

 
 int main ()
 {
    Singleton* sing = Singleton::Instance();
    sing->printInstance();
 }
 
 
