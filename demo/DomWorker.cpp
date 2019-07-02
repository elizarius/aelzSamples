#include "DomWorker.h"
#include "BinarySearchTree.h"
#include "BinaryGap.h"
#include "CommonNames.h"
#include "CyclicRotation.h"
#include "FrogJump.h"
#include "Permutation.h"
#include <iostream>
#include <iterator>

using namespace std;
using namespace aelzns;

DomWorker::DomWorker() {
  _tasks.push_front(new BinarySearchTree);
  _tasks.push_front(new BinaryGap);
  _tasks.push_front(new CommonNames);
  _tasks.push_front(new CyclicRotation);
  _tasks.push_front(new FrogJump);
  _tasks.push_front(new Permutation);

   }

DomWorker::~DomWorker() {

  while (!_tasks.empty()) {
    Task* temp = _tasks.front();
    delete temp;
    _tasks.pop_front();
  }
  //std::cout<<__FUNCTION__<<"  task pool size:  "<<_tasks.size()<<std::endl ;
}

//  run elementary tasks from queue
int DomWorker::processCli(int c, char * argv[]) {
  for (auto itr = _tasks.begin(); itr != _tasks.end(); ++itr) {
    reinterpret_cast<Task*>(*itr)->execute();
    std::cout<<std::endl;
  }
  return 0;
}
