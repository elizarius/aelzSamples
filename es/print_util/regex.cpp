#include <iostream>
#include <string>
#include <regex>

// Example to use regular expressions in C++

int main()
{
    std::string text = "Email: test@example.com, Phone: 123-456-7890";

    // Example 1: Match email pattern
    std::regex email_pattern(R"(\w+@\w+\.\w+)");
    std::smatch match;
    if (std::regex_search(text, match, email_pattern)) {
        std::cout << "Found email: " << match[0] << std::endl;
    }

    // Example 2: Match phone pattern
    std::regex phone_pattern(R"(\d{3}-\d{3}-\d{4})");
    if (std::regex_search(text, match, phone_pattern)) {
        std::cout << "Found phone: " << match[0] << std::endl;
    }

    // Example 3: Replace pattern
    std::string result = std::regex_replace(text, phone_pattern, "[PHONE]");
    std::cout << "Replaced: " << result << std::endl;

    // Example 4: Check if entire string matches pattern
    std::string email = "user@domain.org";
    if (std::regex_match(email, email_pattern)) {
        std::cout << "Valid email: " << email << std::endl;
    }

    return 0;
}

