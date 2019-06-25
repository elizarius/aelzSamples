#include <vector>
#include <algorithm>

/* rotate cyclically members of array */

using namespace std; 
vector<int> solution(vector<int> &A, int K) {

    if ((K < 0) || (A.size()==1) ||
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
