#include <iostream>
#include <string>
#include <variant>

// Old style: a plain union. It holds one of its members at a time, but nothing
// records which one. Reading a member other than the one last written is undefined behavior.
union IntOrDouble {
    int i;
    double d;
};

int main()
{
    IntOrDouble u;
    u.i = 42;
    std::cout << " OLD union holds int: " << u.i << std::endl;

    u.d = 2.5;
    std::cout << " OLD union holds double: " << u.d << std::endl;

    // std::variant: the active type is tracked, and a wrong access throws instead of misbehaving.
    std::variant<int, std::string> value = 42;
    std::cout << "value holds int: " << std::get<int>(value) << std::endl;

    value = std::string("hello");
    std::cout << "value holds string: " << std::get<std::string>(value) << std::endl;

    return 0;
}
