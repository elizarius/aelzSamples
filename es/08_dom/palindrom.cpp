#include <string>
#include <stdexcept>
#include <iostream>

class Palindrome
{
public:
    static bool isPalindrome(const std::string& word)
    {
        int i;
        std::cout<<"---------"<<std::endl;
        int  sz = word.length();
        for (i=0; i<=sz; i++) {
            //std::cout<<tolower(word[i])<< "  ::: "<<tolower(word[sz-1-i])<<std::endl;
            if (tolower(word[i]) != tolower(word[sz-1-i])) {
                return false;
            }
        }
        return true;
    }
};

#ifndef RunTests
int main()
{
    std::cout << Palindrome::isPalindrome("hao")<<std::endl;
    std::cout << Palindrome::isPalindrome("Deleveled")<<std::endl;
    std::cout << Palindrome::isPalindrome("haoah")<<std::endl;
}
#endif
