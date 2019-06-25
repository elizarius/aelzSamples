#include <algorithm>
#include <vector>

// Find unique unpaired value in array of integers
using namespace std;

int solution(vector<int> &A) {
    int ctr;   
    if  ((A.size() %2 == 0) || A.empty())
        return -1;
 
    for (std::vector<int>::iterator it = A.begin(); it != A.end(); ++it) {
        
        ctr = std::count( A.begin(), A.end(), *it);
        if (ctr % 2 == 1)
          return *it;
    }
    return 0;
}


#include <vector>
#include <algorithm>

// with using XOR operation, find uniquie unpaired member in array
int solution(vector<int> &A) {
    
    int odd1 = 0;
    for(int i=0; i < A.size(); i++) {
        odd1 ^= A[i];
    }
    return odd1;
}


