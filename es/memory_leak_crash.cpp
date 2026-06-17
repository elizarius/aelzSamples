#include <iostream>
#include <vector>

// Memory Leak Crash Demonstration
// Allocates memory with 'new' but never releases with 'delete'
// Causes eventual crash due to out-of-memory condition

int main() {
    std::cout << "=== Memory Leak Crash Demonstration ===" << std::endl;
    std::cout << "Allocating memory without releasing it..." << std::endl;
    std::cout << std::endl;

    // Track allocations
    int allocationCount = 0;
    const size_t BLOCK_SIZE = 1024 * 1024 * 100;  // 100 MB per allocation

    try {
        while (true) {
            // Allocate 100 MB blocks repeatedly
            char* buffer = new char[BLOCK_SIZE];
            allocationCount++;

            // Print progress every 10 allocations
            if (allocationCount % 10 == 0) {
                std::cout << "Allocated " << allocationCount << " blocks ("
                          << (allocationCount * BLOCK_SIZE / (1024 * 1024)) << " MB total)"
                          << std::endl;
            }

            // Fill the memory to ensure it's actually allocated
            for (size_t i = 0; i < BLOCK_SIZE; i += 4096) {
                buffer[i] = 0xFF;
            }

            // INTENTIONALLY NOT DELETING: delete buffer;
            // This causes memory leak that will eventually crash the program
        }
    }
    catch (const std::bad_alloc& e) {
        std::cout << std::endl;
        std::cout << "=== OUT OF MEMORY ===" << std::endl;
        std::cout << "Memory allocation failed after " << allocationCount << " blocks" << std::endl;
        std::cout << "Total memory leaked: " << (allocationCount * BLOCK_SIZE / (1024 * 1024))
                  << " MB" << std::endl;
        std::cout << "Exception: " << e.what() << std::endl;
        std::cout << std::endl;
        std::cout << "CRASH REASON:" << std::endl;
        std::cout << "  - Allocated memory with 'new' without corresponding 'delete'" << std::endl;
        std::cout << "  - Each loop iteration allocates 100 MB but never frees it" << std::endl;
        std::cout << "  - Eventually system runs out of available memory" << std::endl;
        std::cout << "  - Program terminates with bad_alloc exception" << std::endl;
        std::cout << std::endl;
        return 1;
    }

    return 0;
}
