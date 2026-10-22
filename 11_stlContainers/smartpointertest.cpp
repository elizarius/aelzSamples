#include <memory>
#include <iostream>

// shared_ptr: several owners share one object; it is destroyed
// when the last owner goes away.
void sharedPtrDemo() {
  std::cout << "***** Shared pointer several owners: " << std::endl;

  std::shared_ptr<int> s1 = std::make_shared<int>(10);
  std::cout << "s1 use_count: " << s1.use_count() << std::endl;

  {
    std::shared_ptr<int> s2 = s1;  // copy: both now own the same int
    std::cout << "s1 use_count inside scope: " << s1.use_count() << ", *s2: " << *s2 << std::endl;
  }  // s2 destroyed here, count drops back to 1

  std::cout << "s1 use_count after scope: " << s1.use_count() << std::endl<<std::endl;
}  // s1 destroyed here, the int is freed

// weak_ptr: observes a shared_ptr object without owning it, so it does not keep it alive.
void weakPtrDemo() {
  std::cout << "***** Weak pointer observes without owning: " << std::endl;
  std::weak_ptr<int> w;
  {
    std::shared_ptr<int> s = std::make_shared<int>(20);
    w = s;  // does not increase the use count
    std::cout << "use_count: " << s.use_count() << ", expired: " << std::boolalpha << w.expired() << std::endl;

    // lock() gives a shared_ptr only while the object is still alive
    if (auto locked = w.lock())
      std::cout << "locked value: " << *locked << std::endl;
  }  // s destroyed here, the int is freed
  std::cout << "after scope, expired: " << w.expired() << ", lock() is null: " << (w.lock() == nullptr) << std::endl<<std::endl;
}

// unique_ptr: sole ownership; moving transfers it and leaves the source null.
void uniquePtrDemo() {
  std::cout << "***** Unique pointer sole ownership: " << std::endl;
  std::unique_ptr<int> p1 = std::make_unique<int>(3);
  std::unique_ptr<int> p2 = std::make_unique<int>(4);
  std::unique_ptr<int> p3 = std::make_unique<int>(5);

  std::cout << "p1: " << *p1 << ", p2: " << *p2 << ", p3: " << *p3 << std::endl;

  p2 = std::move(p1);
  std::cout << "After: p2 = std::move(p1): p2: " << *p2 <<std::endl;

  p1 = std::move(p3);
  std::cout << "After p1 = std::move(p3): p1: " << *p1 << std::endl<<std::endl;

   // Segmentaiton fault, p1 --> nullptr
  //std::cout << "After: :P1"<<*p1<<std::endl;

}

int main() {
  uniquePtrDemo();
  sharedPtrDemo();
  weakPtrDemo();
}
