#include <iostream>

int main() {
    double x, y;

    std::cout << "Enter location point (x, y):" << std::endl;
    std::cout << "x: ";
    std::cin >> x;
    std::cout << "y: ";
    std::cin >> y;

    if (x >= -10 && x <= 10 && y >= -5 && y <= 5) {
        std::cout << "The point (" << x << ", " << y << ") is within the rectangle." << std::endl;
    } else {
        std::cout << "The point (" << x << ", " << y << ") is outside the rectangle." << std::endl;
    }

    return 0;
}
