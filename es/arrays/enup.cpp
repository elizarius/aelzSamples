#include <iostream>

enum class DayOfWeek{
    Monday = 1,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};


void print_day(DayOfWeek day) {
    switch (day) {
        case DayOfWeek::Monday :
            std::cout << "Today is Monday";
        break;

        case DayOfWeek::Tuesday :
            std::cout << "Today is Tuesday";
        break;

        case DayOfWeek::Wednesday :
            std::cout << "Today is Wednesday";
        break;

        case DayOfWeek::Thursday :
            std::cout << "Today is Thursday";
        break;

        case DayOfWeek::Friday :
            std::cout << "Today is Friday" ;
        break;

        case DayOfWeek::Saturday :
            std::cout << "Today is Saturday";
        break;

        case DayOfWeek::Sunday :
            std::cout << "Today is Sunday" ;
        break;

        default :
            std::cout << "No day";
    }
}

int main () {
    print_day(DayOfWeek::Monday);
    return 0;
}

