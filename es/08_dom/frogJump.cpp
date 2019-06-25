// A small frog wants to get to the other side of the road. The frog is currently located
// at position X  and wants to get to a position greater than or equal to Y. 
// The small frog always jumps a fixed distance, D.
// Count the minimal number of jumps that the small frog must perform to reach its target.

// For example, given:
//  X = 10,   Y = 85,   D = 30 returns 3 jumps

#include <iostream>

int solution(int X, int Y, int D) {
    if ((X < 1) || (X>1000000000)) {
        //cout << "ERR: X out of range"<<endl;
        return -1;
    }

    if ((Y < 1) || (Y>1000000000)) {
        //cout << "ERR: Y out of range"<<endl;
        return -1;
    }
    
    if ((D < 1) || (D>1000000000)) {
        //cout << "ERR: D out of range"<<endl;
        return -1;
    }

    if (Y < X) {
        //cout << "ERR: Wrong Y"<<endl;
        return -1;
    }

    int extra = (Y-X)%D;
    int increm = 0;
    if (extra != 0) 
        increm =1;

    // number of jumps rounded to +1 if modulus > 0
    int min_jumps = ((Y-X)/D)+increm;
    //cout <<"min_jumps: "<<min_jumps<<endl;
    return min_jumps;
}
