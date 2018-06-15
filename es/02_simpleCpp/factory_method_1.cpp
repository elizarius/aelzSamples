#include <iostream>
#include <vector>


using namespace std ;

class FactoryBase
{
 public:
   // Factory Method
   static FactoryBase * makeFactoryInstance(int choice);
   virtual void printInstance () = 0;
};


class Fac_1: public FactoryBase
{
 public:
   void printInstance()
   {
       std::cout << "Fac_1: print fucntion called"<<std::endl;
   }
};

class Fac_2: public FactoryBase
{
 public:
   void printInstance()
   {
       std::cout << "Fac_2: print fucntion called"<<std::endl;
   }
};

class Fac_3: public FactoryBase
{
 public:
   void printInstance()
   {
       std::cout << "Fac_3: print fucntion called"<<std::endl;
   }
};

FactoryBase * FactoryBase::makeFactoryInstance(int choice)
{
 if (choice == 1)
   return new Fac_1;
 else if (choice == 2)
   return new Fac_2;
 else
   return new Fac_3;
}

int main(void)
{
 std::vector<FactoryBase *>  fi;
 int choice;
 while (true)
 {
   cout << "Fac_1(1) Fac_2(2) Fac_3(3) Go(0): ";
   cin >> choice;
   if (choice == 0)
     break;
   fi.push_back(FactoryBase::makeFactoryInstance(choice));
 }
 for (int i = 0; i < fi.size(); i++)
   fi[i]->printInstance();
 for (int i = 0; i < fi.size(); i++)
   delete fi[i];
}




