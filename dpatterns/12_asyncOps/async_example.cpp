#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <stdexcept>

// g++ async_example.cpp -std=c++17 -pthread
// ./a.out

using namespace std;

// AELZ_01: more info on async methods and ops, see C++ threads session in bucluclu  

// Example 1: Simple async function that returns a value
int calculateSum(int a, int b) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    return a + b;
}

// Example 2: Function that throws an exception
int riskyCalculation(int divisor) {
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    if (divisor == 0) {
        throw std::invalid_argument("Division by zero!");
    }
    return 100 / divisor;
}

// Example 3: Long-running task
string processData(const string& data) {
    for (int i = 0; i < 3; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::cout << "  Processing: " << data << " (step " << (i + 1) << "/3)" << std::endl;
    }
    return "Processed: " + data;
}

// Example 4: Lambda function with capture
double computeAverage(const vector<int>& numbers) {
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    double sum = 0;
    for (int num : numbers) {
        sum += num;
    }
    return numbers.empty() ? 0 : sum / numbers.size();
}

int main() {
    std::cout << "=== std::async Examples ===" << std::endl << std::endl;

    // Example 1: Basic async with std::launch::async
    std::cout << "Example 1: Basic Async Execution" << std::endl;
    std::cout << "Launching async task to calculate 5 + 3..." << std::endl;
    auto future1 = std::async(std::launch::async, calculateSum, 5, 3);
    std::cout << "Doing other work while task runs..." << std::endl;
    int result1 = future1.get();  // Blocks until task completes
    std::cout << "Result: " << result1 << std::endl << std::endl;


    // Example 2: Deferred launch (lazy evaluation)
    std::cout << "Example 2: Deferred Execution (Lazy Evaluation)" << std::endl;
    auto future2 = std::async(std::launch::deferred, calculateSum, 10, 20);
    std::cout << "Task created but not started yet..." << std::endl;
    std::cout << "Getting result (this triggers execution):" << std::endl;
    int result2 = future2.get();
    std::cout << "Result: " << result2 << std::endl << std::endl;

    // Example 3: Exception handling in async
    std::cout << "Example 3: Exception Handling" << std::endl;
    auto future3 = std::async(std::launch::async, riskyCalculation, 0);
    try {
        int result = future3.get();
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    std::cout << std::endl;

    // Example 4: Multiple concurrent tasks
    std::cout << "Example 4: Multiple Concurrent Tasks" << std::endl;
    std::vector<std::future<string>> futures;
    std::vector<string> dataItems = {"Task A", "Task B", "Task C"};

    for (const auto& item : dataItems) {
        futures.push_back(std::async(std::launch::async, processData, item));
    }

    std::cout << "Waiting for all tasks to complete..." << std::endl;
    for (size_t i = 0; i < futures.size(); ++i) {
        std::cout << "Result " << (i + 1) << ": " << futures[i].get() << std::endl;
    }
    std::cout << std::endl;

    // Example 5: Lambda with capture
    std::cout << "Example 5: Lambda Functions with Capture" << std::endl;
    vector<int> numbers = {10, 20, 30, 40, 50};
    auto lambdaTask = std::async(std::launch::async, [](const vector<int>& nums) {
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        double sum = 0;
        for (int num : nums) {
            sum += num;
        }
        return sum / nums.size();
    }, numbers);

    std::cout << "Computing average of: ";
    for (int num : numbers) std::cout << num << " ";
    std::cout << std::endl;
    double average = lambdaTask.get();
    std::cout << "Average: " << average << std::endl << std::endl;


    // Example 6: Checking task status without blocking
    std::cout << "Example 6: Wait For Result with Timeout" << std::endl;
    auto future6 = std::async(std::launch::async, calculateSum, 7, 8);

    std::cout << "Checking if task is ready..." << std::endl;
    auto status = future6.wait_for(std::chrono::milliseconds(100));

    if (status == std::future_status::ready) {
        std::cout << "Task completed: " << future6.get() << std::endl;
    } else if (status == std::future_status::timeout) {
        std::cout << "Task still running, waiting more..." << std::endl;
        std::cout << "Final result: " << future6.get() << std::endl;
    }
    std::cout << std::endl;

    // Example 7: Combining multiple async calls
    std::cout << "Example 7: Combining Results from Multiple Tasks" << std::endl;
    auto task1 = std::async(std::launch::async, calculateSum, 5, 10);
    auto task2 = std::async(std::launch::async, calculateSum, 20, 15);
    auto task3 = std::async(std::launch::async, calculateSum, 3, 4);

    int r1 = task1.get();
    int r2 = task2.get();
    int r3 = task3.get();
    int combined = r1 + r2 + r3;

    std::cout << "Task 1 result: " << r1 << std::endl;
    std::cout << "Task 2 result: " << r2 << std::endl;
    std::cout << "Task 3 result: " << r3 << std::endl;
    std::cout << "Combined result: " << combined << std::endl << std::endl;

    // Example 8: Default launch policy behavior
    std::cout << "Example 8: Default Launch Policy" << std::endl;
    auto future8a = std::async(calculateSum, 100, 200);
    auto future8b = std::async(calculateSum, 50, 75);

    std::cout << "Result A: " << future8a.get() << std::endl;
    std::cout << "Result B: " << future8b.get() << std::endl;
    std::cout << "(Default policy may use async or deferred)" << std::endl << std::endl;

    std::cout << "=== All examples completed ===" << std::endl;
    return 0;
}
