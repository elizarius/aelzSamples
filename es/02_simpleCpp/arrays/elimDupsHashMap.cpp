#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>

/* Eliminate duplicates from the array and print the unique numbers.
   The order of the unique numbers is the same as the first occurrence in
   the input array.
*/
void unique_numbers(int numbers[], unsigned int collection_size)
{
  std::unordered_set<int> seen;

  for (unsigned int i = 0; i < collection_size; ++i)
  {
    seen.insert(numbers[i]);
  }

  // Copy to vector
  std::vector<int> vec(seen.begin(), seen.end());

  std::cout << "Seen members (unordered): ";
  for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}


int main()
{
  int numbers[] = {1, 1, 2, 10, 4, 5, 1, 2, 2, 12};
  unsigned int collection_size = std::size(numbers);
  unique_numbers(numbers, collection_size);
  return 0;
}
