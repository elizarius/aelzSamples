#ifndef _FROG_JUMP_H_
#define _FROG_JUMP_H_

#include "Task.h"
#include <iostream>

// A small frog wants to get to the other side of the road. The frog is currently located
// at position X  and wants to get to a position greater than or equal to Y. 
// The small frog always jumps a fixed distance, D.
// Count the minimal number of jumps that the small frog must perform to reach its target.

// For example, given:
//  X = 10,   Y = 85,   D = 30 returns 3 jumps



namespace aelzns {
    
class FrogJump : public Task {
  public:
    FrogJump() { }
    virtual ~FrogJump(){}

    virtual bool execute() {
      int x = 12;
      int y = 99;
      int d = 5;
      std::cout<<"\t"<<__PRETTY_FUNCTION__<<" frog jump: "<< \
      "start: "<<x<<" end: "<<y<<" jump: "<<d<<std::endl;

      int n_jumps = solution(x, y, d);
      std::cout<<"\t"<<__PRETTY_FUNCTION__<<"\t jumps: "<<n_jumps<<std::endl;
      return true;  
    }
  private:

    int solution(int X, int Y, int D) {
      if ((X < 1) || (X>1000000000)) {
        std::cout << "ERR: X out of range"<<std::endl;
        return -1;
      }

      if ((Y < 1) || (Y>1000000000)) {
        std::cout << "ERR: Y out of range"<<std::endl;
        return -1;
      }
    
      if ((D < 1) || (D>1000000000)) {
        std::cout << "ERR: D out of range"<<std::endl;
        return -1;
      }

      if (Y < X) {
        std::cout << "ERR: Wrong Y"<<std::endl;
        return -1;
      }

      int extra = (Y-X)%D;
      int increm = 0;
      if (extra != 0) 
        increm = 1;

      // number of jumps rounded to +1 if modulus > 0
      int min_jumps = ((Y-X)/D)+increm;
      return min_jumps;
    }

};
}
#endif
