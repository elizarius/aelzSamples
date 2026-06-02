#include <algorithm>
#include <vector>

// you are given N counters, initially set to 0, and you have two possible operations on them:

// increase(X) - counter X is increased by 1,
// max counter - all counters are set to the maximum value of any counter.
// A non-empty array A of M integers is given. This array represents consecutive operations:

// if A[K] = X, such that 1 ≤ X ≤ N, then operation K is increase(X),
// if A[K] = N + 1 then operation K is max counter.
// For example, given integer N = 5 and array A such that:

//     A[0] = 3
//     A[1] = 4
//     A[2] = 4
//     A[3] = 6
//     A[4] = 1
//     A[5] = 4
//     A[6] = 4
// the values of the counters after each consecutive operation will be:

//     (0, 0, 1, 0, 0)
//     (0, 0, 1, 1, 0)
//     (0, 0, 1, 2, 0)
//     (2, 2, 2, 2, 2)
//     (3, 2, 2, 2, 2)
//     (3, 2, 2, 3, 2)
//     (3, 2, 2, 4, 2)
// Write an efficient algorithm for the following assumptions:
// N and M are integers within the range [1..100,000];
// each element of array A is an integer within the range [1..N + 1].

vector<int> solution(int N, vector<int> &A) {
    std::vector<int> zeroes(1, 0);
    std::vector<int> counters(N, 0);
    
    if (A.size() > 100000) return zeroes;
    if ((N > 100000)  || (N<1)) return zeroes;
    int max_c = 0;
    
    for (auto it = A.begin(); it != A.end(); ++it ) {
        if (*it > N+1 ) return zeroes;

        if (*it == (N+1)) {
            //std::fill (counters.begin(),counters.end(), max_c);
            if (counters [*it] != max_c) {
                counters.assign(counters.size(), max_c);
            }
        } else {
            counters [*it-1] ++;
            if  (counters [*it-1] > max_c) 
                max_c = counters [*it-1];
        }
       
        //std::cout<<"Counters: [ ";
        //for (auto xx=counters.begin(); xx!=counters.end(); ++xx)
        //    std::cout<<*xx<<" , ";
        //std::cout<<" ] "<<endl;

    } 
    return counters;    
}
