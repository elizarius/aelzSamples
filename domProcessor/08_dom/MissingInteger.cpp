 #include <vector>
 #include <iostream>
 #include <algorithm>
 #include <iterator>
 #include <set>

// Note: similar approach can be implemented with sorted vector and std::binary_search
// algorithm

// Write a function: int solution(vector<int> &A);
// that, given an array A of N integers, returns the smallest positive integer (greater than 0)
// that does not occur in A.
// For example:
//
// Given A = [1, 3, 6, 4, 1, 2], the function should return 5.
// Given A = [1, 2, 3], the function should return 4.
// Given A = [-1, -3], the function should return 1.
// Write an efficient algorithm for the following assumptions:
// N is an integer within the range [1..100,000];
// each element of array A is an integer within the range [-1,000,000..1,000,000].
// [-1,0,-2]
// [4]
// [1,100000]
// [0,100000]
// [-1000000,1000000]
// [1]
// [4, 5, 6, 2]

using namespace std;
int solution(vector<int> &A) {

    std::set<int>::iterator next_it;
    std::set<int> B;
    sort(A.begin(), A.end());

    // all negatives, return 1
    if ( std::all_of(A.begin(), A.end(), [](int i){return i<=0;}))
        return 1;

    // one element=1, return 2
    if ( (A.size() == 1) && (*A.begin() == 1) )
            return 2;

    // one element, return 1
    if (A.size() == 1)
        return 1;

    // Boundary conditions finished.

    // get set of only positive numbers
    for (auto it = A.begin(); it != A.end(); ++it) {
        if (*it >0)
            B.insert(*it);
    }

    // one element, return 1
    if (B.size() == 1)
        return 1;

    //for (auto it=B.begin(); it != B.end(); it++) {
    //    std::cout<<"set member: "<<(*it)<<std::endl;
    //}

    for (unsigned int i=1; i<=B.size(); i++) {
        auto it = B.find(i);
        if ( it  == B.end()) {
            //std::cout<<"found missed member: "<<i<<std::endl;
            return i;
        }
    }

    // now reached level when when elements are permutation
    int maxIn = *max_element(B.begin(), B.end());
    return maxIn +1;
}
