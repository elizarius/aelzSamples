#ifndef _BINARY_GAP_H_
#define _BINARY_GAP_H_

#include "Task.h"
#include <bitset>
#include <iostream>

//  calculate binary gap: number of 0s between 1s in binary format representation
//  used algo -> bitsets as hex string representation
//  more effective approach is to use XOR ? 

namespace aelzns {
    
class BinaryGap : public Task {
  public:
    BinaryGap() { }
    virtual ~BinaryGap(){}


    virtual bool execute() {
      int target = 9;
      int maxlen = solution(target);
      std::cout<<"\t"<<__PRETTY_FUNCTION__<<" binary gap for : "<<\
      target<<" = "<<maxlen<<std::endl<<std::endl;
      return 0;    
    }
  private:

    int solution(int N) {
      std::bitset<64> aelz(N);

      unsigned int i;
      int gaplen = 0;
      int maxlen = 0;
      bool started = false;

      if  (aelz.all()  ||  aelz.none() ||  (aelz.count() == 1))
        return 0;

      for (i=0; i<aelz.size(); i++) {
        if (aelz.test(i)) {
            if (gaplen > maxlen) {
                maxlen = gaplen;
            }
            started = true;
            gaplen = 0;
        } else {
            if (started)
            gaplen++;
        }
      }
      return maxlen;
}


};
}
#endif
