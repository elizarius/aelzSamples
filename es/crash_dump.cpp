#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstring>
#include <ctime>
#include <sstream>
#include <memory>

// ============================================================================
// CRASH DUMP SIMULATION & ANALYSIS
// Educational program demonstrating common crash scenarios and diagnostics
// ============================================================================

// Simulated crash types
enum class CrashType {
    NULL_POINTER_DEREFERENCE,
    STACK_OVERFLOW,
    SEGMENTATION_FAULT,
    MEMORY_CORRUPTION,
    BUFFER_OVERFLOW,
    USE_AFTER_FREE
};

// Simulated register state (similar to actual CPU registers)
struct RegisterState {
    std::uint64_t rax;  // Accumulator
    std::uint64_t rbx;  // Base register
    std::uint64_t rcx;  // Counter
    std::uint64_t rdx;  // Data register
    std::uint64_t rsi;  // Source index
    std::uint64_t rdi;  // Destination index
    std::uint64_t rbp;  // Base pointer (frame pointer)
    std::uint64_t rsp;  // Stack pointer
    std::uint64_t rip;  // Instruction pointer
};

// Simulated memory state at crash time
struct MemoryBlock {
    std::uint64_t address;
    std::vector<std::uint8_t> data;
    std::string description;
};

// Simulated stack frame information
struct StackFrame {
    int frameNumber;
    std::string functionName;
    std::string sourceFile;
    int lineNumber;
    std::uint64_t returnAddress;
};

// ============================================================================
// DIAGNOSTIC FUNCTIONS
// ============================================================================

// Generate a simulated memory dump for a given address range
std::vector<MemoryBlock> captureMemoryState(std::uint64_t baseAddress, int numBlocks) {
    std::vector<MemoryBlock> blocks;

    for (int i = 0; i < numBlocks; ++i) {
        MemoryBlock block;
        block.address = baseAddress + (i * 16);

        // Simulate memory content
        for (int j = 0; j < 16; ++j) {
            block.data.push_back(static_cast<std::uint8_t>(0xAA + (i * j) % 256));
        }

        block.description = "Memory segment " + std::to_string(i);
        blocks.push_back(block);
    }

    return blocks;
}

// Generate simulated register state
RegisterState captureRegisterState() {
    RegisterState regs;
    regs.rax = 0x0000000000000000;  // Usually contains return value
    regs.rbx = 0x00007ffffffde000;  // Callee-saved
    regs.rcx = 0x0000000000000001;  // Counter
    regs.rdx = 0x0000000000000010;  // Data
    regs.rsi = 0x00007ffffffde100;  // Source index
    regs.rdi = 0x00007ffffffde200;  // Destination index
    regs.rbp = 0x00007ffffffde300;  // Frame pointer (points to current stack frame)
    regs.rsp = 0x00007ffffffde400;  // Stack pointer
    regs.rip = 0x00000000004011a5;  // Instruction pointer (where crash occurred)

    return regs;
}

// Simulate stack unwinding to capture call stack
std::vector<StackFrame> captureStackTrace() {
    std::vector<StackFrame> trace;

    trace.push_back({0, "dereferenceNullPointer", "crash_dump.cpp", 245, 0x00000000004011a5});
    trace.push_back({1, "demonstrateNullPointerCrash", "crash_dump.cpp", 380, 0x00000000004011f2});
    trace.push_back({2, "simulateCrash", "crash_dump.cpp", 410, 0x0000000000401245});
    trace.push_back({3, "main", "crash_dump.cpp", 512, 0x0000000000401300});
    trace.push_back({4, "__libc_start_main", "libc.so.6", 313, 0x00007ffff7a05082});
    trace.push_back({5, "_start", "crash_dump.cpp", 0, 0x0000000000400f8e});

    return trace;
}

// Format and display memory dump in hex format (like xxd or hexdump)
void displayMemoryDump(const std::vector<MemoryBlock>& blocks) {
    std::cout << "\n[MEMORY DUMP]\n";
    std::cout << std::string(80, '-') << "\n";

    for (const auto& block : blocks) {
        // Display address
        std::cout << "0x" << std::hex << std::setfill('0') << std::setw(16)
                  << block.address << std::dec << "  ";

        // Display bytes in hex
        for (size_t i = 0; i < block.data.size(); ++i) {
            if (i == 8) std::cout << " ";
            std::cout << std::hex << std::setfill('0') << std::setw(2)
                      << static_cast<int>(block.data[i]) << " ";
        }

        std::cout << std::dec << "  |";

        // Display ASCII representation
        for (const auto& byte : block.data) {
            if (byte >= 32 && byte < 127) {
                std::cout << static_cast<char>(byte);
            } else {
                std::cout << ".";
            }
        }

        std::cout << "|\n";
    }
}

// Display register state at time of crash
void displayRegisters(const RegisterState& regs) {
    std::cout << "\n[REGISTERS]\n";
    std::cout << std::string(80, '-') << "\n";

    std::cout << std::hex << std::setfill('0');
    std::cout << "RAX: 0x" << std::setw(16) << regs.rax << "  ";
    std::cout << "RBX: 0x" << std::setw(16) << regs.rbx << "\n";
    std::cout << "RCX: 0x" << std::setw(16) << regs.rcx << "  ";
    std::cout << "RDX: 0x" << std::setw(16) << regs.rdx << "\n";
    std::cout << "RSI: 0x" << std::setw(16) << regs.rsi << "  ";
    std::cout << "RDI: 0x" << std::setw(16) << regs.rdi << "\n";
    std::cout << "RBP: 0x" << std::setw(16) << regs.rbp << "  ";
    std::cout << "RSP: 0x" << std::setw(16) << regs.rsp << "\n";
    std::cout << "RIP: 0x" << std::setw(16) << regs.rip << " (Instruction Pointer - crash location)\n";
    std::cout << std::dec;
}

// Display stack trace (call stack at time of crash)
void displayStackTrace(const std::vector<StackFrame>& trace) {
    std::cout << "\n[STACK TRACE]\n";
    std::cout << std::string(80, '-') << "\n";

    for (const auto& frame : trace) {
        std::cout << "#" << frame.frameNumber << "  0x"
                  << std::hex << std::setfill('0') << std::setw(16)
                  << frame.returnAddress << std::dec << " in "
                  << frame.functionName << " at " << frame.sourceFile
                  << ":" << frame.lineNumber << "\n";
    }
}

// Display crash information header
void displayCrashHeader(CrashType type, const std::string& description) {
    std::time_t now = std::time(nullptr);
    std::tm* timeinfo = std::localtime(&now);
    char timeStr[100];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo);

    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << "                         CRASH DUMP ANALYSIS\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << "Timestamp:     " << timeStr << "\n";
    std::cout << "Process ID:    12345\n";
    std::cout << "Thread ID:     1\n";
    std::cout << "Signal:        11 (SIGSEGV - Segmentation Violation)\n";
    std::cout << "Crash Type:    " << description << "\n";
    std::cout << std::string(80, '=') << "\n";
}

// ============================================================================
// CRASH SCENARIO DEMONSTRATIONS
// ============================================================================

// Scenario 1: Null Pointer Dereference
void demonstrateNullPointerCrash() {
    std::cout << "\n\n### SCENARIO 1: NULL POINTER DEREFERENCE ###\n";
    displayCrashHeader(CrashType::NULL_POINTER_DEREFERENCE,
                      "Null Pointer Dereference");

    std::cout << "\n[CRASH CONTEXT]\n";
    std::cout << std::string(80, '-') << "\n";
    std::cout << "Code that caused crash:\n";
    std::cout << "  int* ptr = nullptr;           // Pointer initialized to NULL\n";
    std::cout << "  int value = *ptr;             // Attempting to dereference NULL\n";
    std::cout << "  std::cout << value;           // Never reaches here\n\n";

    std::cout << "Error Explanation:\n";
    std::cout << "  Dereferencing a null pointer accesses memory address 0x00000000,\n";
    std::cout << "  which is protected by the OS and causes immediate segmentation fault.\n";
    std::cout << "  This is the most common crash in C++ applications.\n\n";

    // Generate and display diagnostics
    auto registers = captureRegisterState();
    auto stackTrace = captureStackTrace();
    auto memory = captureMemoryState(0x0000000000000000, 3);

    displayRegisters(registers);
    displayMemoryDump(memory);
    displayStackTrace(stackTrace);

    std::cout << "\n[PREVENTION]\n";
    std::cout << std::string(80, '-') << "\n";
    std::cout << "  1. Use smart pointers: std::unique_ptr<int> ptr = std::make_unique<int>(5);\n";
    std::cout << "  2. Check before dereference: if (ptr != nullptr) { ... }\n";
    std::cout << "  3. Use optional types: std::optional<int> value;\n";
    std::cout << "  4. Enable compiler warnings: -Wall -Wextra -Wnull-dereference\n";
}

// Scenario 2: Stack Overflow Simulation
void demonstrateStackOverflow() {
    std::cout << "\n\n### SCENARIO 2: STACK OVERFLOW SIMULATION ###\n";
    displayCrashHeader(CrashType::STACK_OVERFLOW,
                      "Stack Overflow (simulated)");

    std::cout << "\n[CRASH CONTEXT]\n";
    std::cout << std::string(80, '-') << "\n";
    std::cout << "Code that caused crash (conceptual, not actually called):\n";
    std::cout << "  void recursiveFunction(int depth) {\n";
    std::cout << "    char buffer[1024];          // Large local variable\n";
    std::cout << "    recursiveFunction(depth + 1); // Infinite recursion\n";
    std::cout << "  }\n";
    std::cout << "  recursiveFunction(0);         // Initial call\n\n";

    std::cout << "Error Explanation:\n";
    std::cout << "  Stack overflow occurs when recursion depth exceeds available stack memory.\n";
    std::cout << "  Each recursive call adds a new stack frame, consuming stack space.\n";
    std::cout << "  When stack limit is reached, further memory access causes segmentation fault.\n\n";

    // Generate diagnostics
    auto registers = captureRegisterState();
    registers.rsp = 0x00007fffff000000;  // Stack pointer at limit
    registers.rbp = 0x00007fffff001000;

    auto stackTrace = captureStackTrace();
    // Simulate many recursive calls
    for (int i = 5; i < 100; ++i) {
        stackTrace.push_back({i, "recursiveFunction", "crash_dump.cpp", 175, 0x0000000000401234});
    }

    auto memory = captureMemoryState(0x00007fffff000000, 4);

    displayRegisters(registers);
    std::cout << "\n[STACK USAGE]\n";
    std::cout << std::string(80, '-') << "\n";
    std::cout << "Stack space available: ~8 MB (typical Linux default)\n";
    std::cout << "Stack space consumed:  ~8 MB (100+ recursive frames)\n";
    std::cout << "Stack space remaining: 0 bytes (OVERFLOW!)\n";

    displayMemoryDump(memory);
    displayStackTrace(stackTrace);

    std::cout << "\n[PREVENTION]\n";
    std::cout << std::string(80, '-') << "\n";
    std::cout << "  1. Avoid unbounded recursion\n";
    std::cout << "  2. Use iteration instead: while/for loops are safer\n";
    std::cout << "  3. Implement recursion depth limit: if (depth > MAX_DEPTH) return;\n";
    std::cout << "  4. Reduce local variable sizes in recursive functions\n";
    std::cout << "  5. Consider using explicit stack (std::vector) for iteration\n";
}

// Scenario 3: Memory Corruption Detection
void demonstrateMemoryCorruption() {
    std::cout << "\n\n### SCENARIO 3: MEMORY CORRUPTION DETECTION ###\n";
    displayCrashHeader(CrashType::MEMORY_CORRUPTION,
                      "Memory Corruption (Buffer Overflow)");

    std::cout << "\n[CRASH CONTEXT]\n";
    std::cout << std::string(80, '-') << "\n";
    std::cout << "Code that caused crash:\n";
    std::cout << "  char buffer[16];                      // Small buffer\n";
    std::cout << "  strcpy(buffer, \"very long string\");  // Overflow!\n";
    std::cout << "  // Writes beyond allocated memory\n\n";

    std::cout << "Error Explanation:\n";
    std::cout << "  Writing beyond buffer boundaries overwrites adjacent memory.\n";
    std::cout << "  This can corrupt:\n";
    std::cout << "    - Stack variables\n";
    std::cout << "    - Function return addresses\n";
    std::cout << "    - vtable pointers\n";
    std::cout << "  Corrupted return address causes crash at function return.\n\n";

    // Generate diagnostics showing corrupted memory
    auto registers = captureRegisterState();
    registers.rip = 0x4141414141414141;  // 'AAAA' - typical canary/overflow pattern

    auto memory = captureMemoryState(0x00007ffffffde000, 5);
    // Mark some bytes as corrupted
    for (size_t i = 32; i < 64; ++i) {
        memory[2].data[i % 16] = 0x41;  // 'A' - overflow pattern
    }

    auto stackTrace = captureStackTrace();

    displayRegisters(registers);
    displayMemoryDump(memory);

    std::cout << "\n[MEMORY CORRUPTION ANALYSIS]\n";
    std::cout << std::string(80, '-') << "\n";
    std::cout << "Buffer location: 0x00007ffffffde000\n";
    std::cout << "Buffer size:     16 bytes\n";
    std::cout << "Bytes written:   26 bytes (10 bytes overflow)\n";
    std::cout << "Overwritten:     Return address at 0x00007ffffffde020\n";
    std::cout << "Corrupt value:   0x4141414141414141 (pattern 'AAAA')\n";

    displayStackTrace(stackTrace);

    std::cout << "\n[PREVENTION]\n";
    std::cout << std::string(80, '-') << "\n";
    std::cout << "  1. Use safe string functions: strncpy() with size limits\n";
    std::cout << "  2. Prefer C++ strings: std::string handles bounds automatically\n";
    std::cout << "  3. Enable stack canaries: -fstack-protector-strong\n";
    std::cout << "  4. Use Address Sanitizer: -fsanitize=address (detects at runtime)\n";
    std::cout << "  5. Code review and static analysis tools\n";
}

// Scenario 4: Use-After-Free
void demonstrateUseAfterFree() {
    std::cout << "\n\n### SCENARIO 4: USE-AFTER-FREE ###\n";
    displayCrashHeader(CrashType::USE_AFTER_FREE,
                      "Use-After-Free");

    std::cout << "\n[CRASH CONTEXT]\n";
    std::cout << std::string(80, '-') << "\n";
    std::cout << "Code that caused crash:\n";
    std::cout << "  int* ptr = new int(42);       // Allocate memory\n";
    std::cout << "  delete ptr;                   // Free memory\n";
    std::cout << "  std::cout << *ptr;            // Use freed memory - CRASH!\n\n";

    std::cout << "Error Explanation:\n";
    std::cout << "  After delete, the pointer still holds the memory address.\n";
    std::cout << "  That memory may be:\n";
    std::cout << "    - Returned to OS (immediate segfault)\n";
    std::cout << "    - Reused for other allocations (silent data corruption)\n";
    std::cout << "    - Still readable but with modified contents\n";
    std::cout << "  This is one of the most dangerous C++ bugs.\n\n";

    // Generate diagnostics
    auto registers = captureRegisterState();
    auto memory = captureMemoryState(0x00007fffee001234, 3);

    // Simulate freed memory with random pattern
    memory[0].data[0] = 0xCD;  // Pattern from freed memory
    memory[0].data[1] = 0xCD;

    auto stackTrace = captureStackTrace();

    displayRegisters(registers);
    displayMemoryDump(memory);
    displayStackTrace(stackTrace);

    std::cout << "\n[HEAP STATE]\n";
    std::cout << std::string(80, '-') << "\n";
    std::cout << "Allocation address: 0x00007fffee001234\n";
    std::cout << "Allocation size:    4 bytes (int)\n";
    std::cout << "Status:             FREED (marked for reuse)\n";
    std::cout << "Current content:    0xcdcdcdcd (freed memory pattern)\n";

    std::cout << "\n[PREVENTION]\n";
    std::cout << std::string(80, '-') << "\n";
    std::cout << "  1. Use smart pointers: std::unique_ptr, std::shared_ptr\n";
    std::cout << "  2. Never manually delete with new\n";
    std::cout << "  3. Set pointer to nullptr after delete (not sufficient!)\n";
    std::cout << "  4. Enable Memory Sanitizer: -fsanitize=memory\n";
    std::cout << "  5. Valgrind: valgrind --leak-check=full ./program\n";
}

// Scenario 5: Segmentation Fault from Invalid Memory Access
void demonstrateSegmentationFault() {
    std::cout << "\n\n### SCENARIO 5: SEGMENTATION FAULT (Invalid Memory Access) ###\n";
    displayCrashHeader(CrashType::SEGMENTATION_FAULT,
                      "Invalid Memory Access");

    std::cout << "\n[CRASH CONTEXT]\n";
    std::cout << std::string(80, '-') << "\n";
    std::cout << "Code that caused crash:\n";
    std::cout << "  int* ptr = reinterpret_cast<int*>(0xDEADBEEF);  // Invalid address\n";
    std::cout << "  *ptr = 42;                    // Access invalid memory\n\n";

    std::cout << "Error Explanation:\n";
    std::cout << "  Attempting to access unmapped virtual memory address.\n";
    std::cout << "  The OS memory management unit (MMU) detects invalid access.\n";
    std::cout << "  OS sends SIGSEGV signal to process, which terminates abnormally.\n\n";

    auto registers = captureRegisterState();
    registers.rdi = 0xDEADBEEF;  // The bad address

    auto stackTrace = captureStackTrace();

    displayRegisters(registers);

    std::cout << "\n[FAULT ANALYSIS]\n";
    std::cout << std::string(80, '-') << "\n";
    std::cout << "Faulting instruction: mov dword ptr [rdi], eax\n";
    std::cout << "Memory address:       0xDEADBEEF\n";
    std::cout << "Address type:         Unmapped virtual memory\n";
    std::cout << "Fault type:           Write access to unmapped page\n";

    displayStackTrace(stackTrace);

    std::cout << "\n[PREVENTION]\n";
    std::cout << std::string(80, '-') << "\n";
    std::cout << "  1. Avoid manual pointer arithmetic\n";
    std::cout << "  2. Use container classes: std::vector, std::array\n";
    std::cout << "  3. Avoid reinterpret_cast when possible\n";
    std::cout << "  4. Use bounds checking: vector.at() instead of vector[]\n";
    std::cout << "  5. Enable compiler warnings for pointer misuse\n";
}

// ============================================================================
// MAIN PROGRAM
// ============================================================================

int main() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║                    C++ CRASH DUMP SIMULATOR & ANALYZER                        ║\n";
    std::cout << "║                                                                                ║\n";
    std::cout << "║  Educational program demonstrating common crash scenarios in C++              ║\n";
    std::cout << "║  Shows what diagnostic information would be available at crash time           ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════════════════════╝\n";

    try {
        // Demonstrate each crash scenario
        demonstrateNullPointerCrash();
        demonstrateStackOverflow();
        demonstrateMemoryCorruption();
        demonstrateUseAfterFree();
        demonstrateSegmentationFault();

        // Final summary
        std::cout << "\n\n" << std::string(80, '=') << "\n";
        std::cout << "                            SUMMARY & BEST PRACTICES\n";
        std::cout << std::string(80, '=') << "\n";

        std::cout << "\nCommon Crash Types and Root Causes:\n";
        std::cout << "  1. NULL_POINTER_DEREFERENCE  - Most common, easiest to fix\n";
        std::cout << "  2. STACK_OVERFLOW           - Infinite recursion or huge locals\n";
        std::cout << "  3. BUFFER_OVERFLOW          - Writing beyond array bounds\n";
        std::cout << "  4. USE_AFTER_FREE           - Accessing deleted memory (very dangerous)\n";
        std::cout << "  5. SEGMENTATION_FAULT       - Accessing unmapped memory\n";
        std::cout << "  6. MEMORY_CORRUPTION        - Overwriting heap metadata\n";

        std::cout << "\nModern C++ Best Practices:\n";
        std::cout << "  - Use smart pointers: std::unique_ptr, std::shared_ptr\n";
        std::cout << "  - Use standard containers: std::vector, std::array, std::string\n";
        std::cout << "  - Enable compiler warnings: -Wall -Wextra -Wpedantic\n";
        std::cout << "  - Use sanitizers: AddressSanitizer, MemorySanitizer\n";
        std::cout << "  - Code review and static analysis tools\n";
        std::cout << "  - Write unit tests and integration tests\n";

        std::cout << "\nDebugging Tools:\n";
        std::cout << "  - gdb: GNU Debugger - set breakpoints, inspect memory/registers\n";
        std::cout << "  - valgrind: Find memory leaks and access violations\n";
        std::cout << "  - AddressSanitizer: Detect memory errors at runtime\n";
        std::cout << "  - clang-tidy: Static analyzer for code quality issues\n";
        std::cout << "  - Profilers: perf, gprof - find performance bottlenecks\n";

        std::cout << "\n" << std::string(80, '=') << "\n";
        std::cout << "Program completed successfully (no actual crashes!)\n";
        std::cout << std::string(80, '=') << "\n\n";

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << "\n";
        return 1;
    }
}
