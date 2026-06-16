#include <iostream>
#include <string>

int main() {
    int currentDay, dayDifference;
    std::string days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    std::cout << "Enter current day number (1-7): ";
    std::cin >> currentDay;

    if (currentDay < 1 || currentDay > 7) {
        std::cerr << "Error: Invalid day. Please enter a number between 1 and 7." << std::endl;
        return 1;
    }

    std::cout << "Enter day difference (days in the past): ";
    std::cin >> dayDifference;

    int resultDay = currentDay - dayDifference;
    while (resultDay <= 0) {
        resultDay += 7;
    }

    std::cout << dayDifference << " day(s) in the past from day " << currentDay << " (" << days[currentDay - 1]
              << ") is day " << resultDay << " (" << days[resultDay - 1] << ")" << std::endl;

    return 0;
}
