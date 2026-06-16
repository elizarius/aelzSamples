#include <memory>
#include <iostream>

int main() {
  std::unique_ptr<int> p1 = std::make_unique<int>(3);
  std::unique_ptr<int> p2 = std::make_unique<int>(4);
  std::unique_ptr<int> p3 = std::make_unique<int>(5);

  std::cout << "p1: " << *p1 << ", p2: " << *p2 << ", p3: " << *p3 << std::endl;

  p2 = std::move(p1);
  std::cout << "After p2 = std::move(p1): p2: " << *p2 << std::endl;

  p1 = std::move(p3);
  std::cout << "After p1 = std::move(p3): p1: " << *p1 << std::endl;
}