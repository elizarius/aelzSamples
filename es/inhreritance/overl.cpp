#include <iostream>

void say_my_age(const int age);
void say_my_age(unsigned int  age);

int main(){
    say_my_age(23); // literal supposed as const
    unsigned int age = 99;
    say_my_age(age);

    return 0;
}

void say_my_age(const int age){
    std::cout << "1. CONST You are " << age << " years old!" << std::endl;
}
void say_my_age( unsigned int age){
    std::cout << "2.You are " << age << " years old!" << std::endl;
}
