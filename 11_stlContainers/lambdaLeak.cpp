#include <functional>
#include <iostream>
#include <memory>
#include <string>

struct Button {
    std::string name;
    std::function<void()> onClick;

    ~Button() {
        std::cout << "~Button\n";
    }
};

int main() {
    auto button = std::make_shared<Button>();
    button->name = "My Button";
    // weak pointer to avoid circular reference and memory leak
    button->onClick = [weak = std::weak_ptr<Button>{button}] {
        if (auto self = weak.lock()) {
            std::cout << self->name << " **** onClick\n";
        }
    };
    button->onClick();
}
