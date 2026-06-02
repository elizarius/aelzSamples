/* Return indices of two members == sum (second argument)*/
#include <stdexcept>
#include <iostream>
#include <vector>

class TwoSum
{
public:
    static std::pair<int, int> findTwoSum(const std::vector<int>& vec, int sum)
    {
        for (int i=0; i<vec.size(); i++) {
            for (int j=i+1; j< vec.size(); j++) {
                if ((vec[i] + vec[j]) == sum) {
                    return (std::make_pair(i, j));
                }
            }
        }
        return (std::make_pair(-1, -1));
    }
};

int main()
{
    std::vector<int> one = {3, 1, 5, 7, 5, 9};
    std::pair<int, int> indices = TwoSum::findTwoSum(one, 10);
    std::cout << indices.first <<" ::: " << indices.second<<std::endl;
}
