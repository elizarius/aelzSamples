#include <iostream>
#include <string>

int main() {
    int day;
    std::string days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    std::cout << "Enter day number (1-7): ";
    std::cin >> day;

    if (day < 1 || day > 7) {
        std::cerr << "Error: Invalid day. Please enter a number between 1 and 7." << std::endl;
        return 1;
    }

    std::cout << "Day " << day << " is " << days[day - 1] << std::endl;

    return 0;
}
