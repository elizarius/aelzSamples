#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class Singleton
{
    public:
        // Meyer's singleton: thread-safe initialization (C++11 standard)
        static Singleton& getInstance() noexcept {
            static Singleton instance;
            return instance;
        }

        void printInstance() const {
            std::lock_guard<std::mutex> lock(mMutex);
            std::cout << "Modern C++ Singleton with Mutex" << std::endl;
        }

        void setValue(int value) {
            std::lock_guard<std::mutex> lock(mMutex);
            mValue = value;
            std::cout << "Value set to: " << mValue << std::endl;
        }

        int getValue() const {
            std::lock_guard<std::mutex> lock(mMutex);
            return mValue;
        }

        void increment() {
            std::lock_guard<std::mutex> lock(mMutex);
            ++mValue;
        }

    private:
        Singleton() = default;

        // Delete copy/move operations (modern C++ style)
        Singleton(const Singleton&) = delete;
        Singleton(Singleton&&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        Singleton& operator=(Singleton&&) = delete;

        // Destructor
        ~Singleton() = default;

        mutable std::mutex mMutex;
        int mValue = 0;
};

int main()
{
    std::cout << "=== Modern C++17 Singleton with Meyer's Pattern ===" << std::endl << std::endl;

    // Example 1: Basic access
    std::cout << "Example 1: Basic Access" << std::endl;
    Singleton& s1 = Singleton::getInstance();
    s1.printInstance();
    s1.setValue(10);
    std::cout << std::endl;

    // Example 2: Multiple references point to same instance
    std::cout << "Example 2: Multiple References" << std::endl;
    Singleton& s2 = Singleton::getInstance();
    std::cout << "s1 and s2 are same instance: " << (&s1 == &s2 ? "yes" : "no") << std::endl;
    std::cout << "s1 value: " << s1.getValue() << std::endl;
    std::cout << "s2 value: " << s2.getValue() << std::endl;
    std::cout << std::endl;

    // Example 3: Thread-safe operations
    std::cout << "Example 3: Thread-Safe Operations (5 threads x 10 increments)" << std::endl;

    // Reset value to 0 for this example
    Singleton::getInstance().setValue(0);

    std::vector<std::thread> threads;

    auto incrementFunc = [](int iterations) {
        for (int i = 0; i < iterations; ++i) {
            Singleton::getInstance().increment();
        }
    };

    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(incrementFunc, 10);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Final value (should be 50): " << Singleton::getInstance().getValue() << std::endl;
    std::cout << std::endl;

    // Example 4: Demonstrate deleted operations (compile-time error if uncommented)
    // Singleton s3 = s1;              // ERROR: deleted copy constructor
    // Singleton s4(std::move(s1));    // ERROR: deleted move constructor
    // s1 = s2;                         // ERROR: deleted copy assignment
    std::cout << "Deleted operations prevent copying/moving the singleton." << std::endl;

    return 0;
}
