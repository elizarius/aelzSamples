/*
*	Implement function countNumbers that accepts a sorted vector of unique integers and counts the
*	number of vector elements that are less than the parameter lessThan.For example, for vector v 
*	containing { 1, 3, 5, 7 }, SortedSearch::countNumbers(v, 4) should return 2 because there are 
*	two vector elements less than 4.
*/

#include <vector>
#include <stdexcept>
#include <iostream>


class SortedSearch
{
public:
  static int countNumbers(const std::vector<int>& sortedVector, int lessThan) {
    int count = 0;
    for (auto it = sortedVector.begin();it < sortedVector.end();++it) {
      if ( *it >= lessThan) return count; 
        else 
          count++;
     }
       return count;
  }

};

int main()
{
  std::vector<int> v { 1, 3, 5, 7 };
  std::cout << SortedSearch::countNumbers(v, 4)<<std::endl;
  return 0;
}
