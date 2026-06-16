#include <iostream>
#include <iomanip>

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int main() {
    int year, firstDay;
    std::string months[] = {"January", "February", "March", "April", "May", "June",
                            "July", "August", "September", "October", "November", "December"};
    std::string weekDays[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    std::cout << "Enter year: ";
    std::cin >> year;

    std::cout << "Enter first weekday of the year (1=Monday, 2=Tuesday, ..., 7=Sunday): ";
    std::cin >> firstDay;

    if (firstDay < 1 || firstDay > 7) {
        std::cerr << "Error: Invalid weekday. Please enter a number between 1 and 7." << std::endl;
        return 1;
    }

    if (isLeapYear(year)) {
        daysInMonth[1] = 29;
    }

    int currentDay = firstDay;

    for (int month = 0; month < 12; month++) {
        std::cout << "\n" << months[month] << " " << year << std::endl;
        std::cout << "Mon Tue Wed Thu Fri Sat Sun" << std::endl;

        for (int i = 1; i < currentDay; i++) {
            std::cout << "    ";
        }

        for (int day = 1; day <= daysInMonth[month]; day++) {
            std::cout << std::setw(3) << day << " ";
            if (currentDay == 7) {
                std::cout << std::endl;
                currentDay = 1;
            } else {
                currentDay++;
            }
        }
        std::cout << std::endl;
    }

    return 0;
}
