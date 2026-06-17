#include <iostream>

int main() {
    std::cout << "About to crash..." << std::endl;

    int* ptr = nullptr;
    *ptr = 42;  // Dereference null pointer - CRASH!

    return 0;
}
