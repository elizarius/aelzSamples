#ifndef _CYCLIC_R_H_
#define _CYCLIC_R_H_

#include "Task.h"
#include <vector>
#include <algorithm>
#include <iostream>


/* rotate cyclically members of array (vector) */


namespace aelzns {
    
class CyclicRotation : public Task {
  public:
    CyclicRotation() { }
    virtual ~CyclicRotation(){}

    virtual bool execute() {
      
      std::vector <int> orig{1,2,3,4,5,6,7,8};
      int shifts = 3;

      std::cout<<"\t"<<__PRETTY_FUNCTION__<<" rotate vector to: "<<shifts<<std::endl;
      std::vector <int> rotated = solution(orig, shifts);
      for (int i=0; i<rotated.size(); i++) {
        std::cout<<"\t"<<rotated[i];
      }
      std::cout<<std::endl;
    }
  private:

    std::vector<int> solution(std::vector<int> &A, int K) {
      if ((K < 0) || 
          (A.size()==1) ||
          (A.size()== static_cast<unsigned int>(K)) ||
          (A.empty())) {
            return A;
      }

      if  (A.size() < static_cast<unsigned int>(K))  {
            K = K-A.size() ;
      }
      std::rotate(A.begin(), A.end()-K, A.end());
      return A;
    }
};
}
#endif
