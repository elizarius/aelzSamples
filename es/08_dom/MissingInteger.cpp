 #include <vector>
 #include <iostream>
 #include <algorithm>
 #include <iterator>
 #include <set>

// Write a function:int solution(vector<int> &A);
// that, given an array A of N integers, returns the smallest positive integer (greater than 0) that does not occur in A.
// For example, given A = [1, 3, 6, 4, 1, 2], the function should return 5.
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





using namespace std;
int solution(vector<int> &A) {
     
    int smallest = 1;
    std::set<int>::iterator next_it;
    std::set<int> B;                                                                                                         
    sort(A.begin(), A.end());
    
    // all negatives, return 1 
    if ( std::all_of(A.begin(), A.end(), [](int i){return i<=0;}))
        return 1;
        
    // one elmenent=1  , return 1 
    if ( (A.size() == 1) && (*A.begin() ==1) )
            return smallest +1;
        
    // one elenent , return 1 
    if (A.size() == 1)
        return 1;

    // Boundary conditions finished. 
        
    // get set of only positive numbers
    for (auto it = A.begin(); it != A.end(); ++it) {
        if (*it >0)
            B.insert(*it);
    }
    
        // one elmenent , return 1 
    if (B.size() == 1)
        return 1;
        

    //for (auto it=B.begin(); it != B.end(); it++) {
    //    std::cout<<" set member: "<<(*it)<<std::endl;
    //}
    

    for (auto it = B.begin(); it != B.end(); ++it) {
        next_it = std::next(it);
            if ((*next_it)-(*it) > 1) {
                smallest = *it+1;
                return smallest;
            }
    }
    
    if (smallest == 1) {
        int maxInVector = *max_element(B.begin(), B.end());
        smallest = maxInVector +1;  
        //std::cout<<"AELZ smallest: "<< smallest <<endl;
        return smallest;
    }
    return smallest;
}
