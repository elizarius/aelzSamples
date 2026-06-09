#include "DomWorker.h"
#include <iostream>

using namespace aelzns;

int main(int argc, char *argv[]) {
  DomWorker worker;
  int result = worker.processCli(argc, argv);
  std::cout <<std::endl<<"DomProcessor completed." << std::endl;
  return result;
}
