#include <iostream>

int main() {
    double celsius, fahrenheit;

    std::cout << "Enter temperature in Celsius: ";
    std::cin >> celsius;

    fahrenheit = (celsius * 9.0 / 5.0) + 32.0;

    std::cout << celsius << "°C = " << fahrenheit << "°F" << std::endl;

    if (( 6%2) == 0)
     std::cout<<" ODD"<<std::endl;
    else
     std::cout<<" Even"<<std::endl;

    return 0;
}
