#ifndef _ODD_O_H_
#define _ODD_O_H_

#include "Task.h"
#include <iostream>
#include <vector>

// with using XOR operation, find uniquie unpaired member in array

namespace aelzns {

class OddOcurance : public Task {
  public:
    OddOcurance() { }
    virtual ~OddOcurance(){}

    virtual bool execute() {

      std::cout<<"\t"<<__PRETTY_FUNCTION__<<" unpaired member in array "<<std::endl;

      int odd1 = solution(x, y, d);
      std::cout<<"\t"<<__PRETTY_FUNCTION__<<"\t unpaired: "<<odd1<<std::endl;

    }
  private:

  int solution(std::vector<int> &A) {

    int odd1 = 0;
    for(int i=0; i < A.size(); i++) {
        odd1 ^= A[i];
    }
    return odd1;
  }

};
}
#endif




