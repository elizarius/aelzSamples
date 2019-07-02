#ifndef _PERMUTATION_H_
#define _PERMUTATION_H_

#include "Task.h"
#include <iostream>
#include <vector>
#include <set>

// A permutation is a sequence containing each element from 1 to N once, and only once.
// For example, array A such that:
// A[0] = 4 A[1] = 1  A[2] = 3  A[3] = 2 is a permutation, 
// but array A such that:
// A[0] = 4 A[1] = 1 A[2] = 3
// is not a permutation, because value 2 is missing.
// The goal is to check whether array A is a permutation.

namespace aelzns {
    
class Permutation : public Task {
  public:
    Permutation() { }
    virtual ~Permutation(){}

    virtual bool execute() {
      std::vector<int> vect1{10, 20, 30}; 
      std::vector<int> vect2{4, 2, 3, 1}; 

      int  status1 = solution(vect1);
      std::cout<<"\t"<<__PRETTY_FUNCTION__<<"\t status1: "<<status1<<std::endl;

      int  status2 = solution(vect2);
      std::cout<<"\t"<<__PRETTY_FUNCTION__<<"\t status2: "<<status2<<std::endl;

      return true;  
    }
  private:

    int solution(std::vector<int> &A) {
      // Idea is put vector to set and analyze sizes and last element of vector

      std::set<int> B;
      for (auto it=A.begin(); it != A.end(); it++) {
          // add extra boundary checks and check on 0, now it is missed 
          // because of test code
          B.insert(*it);
      }
      
      //for (auto it=B.begin(); it != B.end(); it++) {
      //    std::cout<<" set member: "<<(*it)<<std::endl; 
      //}
      
      if (A.size() == B.size()) {
        // ATTENTION:  set.end() is not last element but tag of containers' end 
        // use rbegin instead 
          int set_end = *B.rbegin(); 
          int set_size = B.size();
          if (set_size == set_end) {
              return 1;
          }
      }
      return 0;
    }

};
}
#endif
