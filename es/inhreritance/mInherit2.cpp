#include <iostream>
#include <vector>
#include <string>

using namespace std ;

class animal
{
 public:

 animal() {std::cout<<"animal CR called"<<std::endl; }
 virtual ~animal() {std::cout<<"animal DR called"<<std::endl; }

   virtual void printInstance ()
   {
      std::cout<<"animal :: printInstance"<<std::endl ;
   }

};

class pet
{
 public:

 pet() {std::cout<<"pet CR called"<<std::endl; }
 virtual ~pet() {std::cout<<"pet DR called"<<std::endl; }

   virtual void printInstance ()
   {
      std::cout<<"animal :: printInstance"<<std::endl ;
   }

};

class dog : public pet
{
 public:

   dog () {std::cout<<"dog  CR called"<<std::endl; }
   virtual ~dog() {std::cout<<"dog DR called"<<std::endl; }

   void printInstance()
   {
       std::cout << "dog print function called"<<std::endl;
   }
};


class petdogs : public dog, public animal {};

int main(void)
{
    petdogs lassie;
    return 1;

}




