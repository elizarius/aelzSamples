#include <iostream>
#include <string>

// 1.Global scope variable 
std::string myString = "myString :: global scope";
     
namespace aelz 
{
  // 2.Namespace scope variable 
  std::string myString = "myString :: aelz namespace";
}

int main()
{
  bool success = true;
  std::string tempString;
  
  // 3.Main function scope variable 
  std::string myString = "myString :: main: scope";

  if ( success) 
  {
    // 4.If scope variable 
    std::string myString = "myString :: if scope";
    tempString = myString;
  } 

  // Print everything  
  std::cout << ::myString << std::endl;
  std::cout << aelz::myString << std::endl;
  std::cout << myString << std::endl;
  std::cout << tempString<<std::endl;

  return 0 ; 
}




