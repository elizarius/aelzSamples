#include <iostream>
#include <string>

#include "api.h"
#include "Logger.h"


using namespace std;
using namespace hs;


int main(int argc, char* argv[])
{
  Scanner scanner;
  scanner.init(5,LOG_STD); 
  scanner.run();

  return 0;
}

