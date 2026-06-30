#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <ctime>
#include <sstream>
#include <cstdint>

// Use-After-Free (UAF) Crash Dump Simulation
// Demonstrates what happens when freed memory is accessed

// Simulated register state at crash time
struct RegisterState {
    std::uint64_t rax = 0x0000000000000000;
    std::uint64_t rbx = 0x00007ffffffde000;
    std::uint64_t rcx = 0x0000000000000001;
    std::uint64_t rdx = 0x0000000000000010;
    std::uint64_t rsi = 0x00007ffffffde100;
    std::uint64_t rdi = 0x00007ffffffde200;
    std::uint64_t rbp = 0x00007ffffffde300;
    std::uint64_t rsp = 0x00007ffffffde400;
    std::uint64_t rip = 0x0000000000401234;  // Instruction where UAF occurred
};

// Display crash header information
void displayCrashHeader(const std::string& crashType, int signalNumber) {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);

    std::cout << std::string(80, '=') << std::endl;
    std::cout << "CRASH DUMP - Use After Free (UAF)" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    std::cout << "Timestamp: " << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << std::endl;
    std::cout << "Process ID: 12345" << std::endl;
    std::cout << "Signal: " << signalNumber << " (SIGSEGV)" << std::endl;
    std::cout << "Crash Type: " << crashType << std::endl;
    std::cout << std::string(80, '=') << std::endl << std::endl;
}

// Display memory in hexdump format
void displayMemoryDump(const std::vector<std::uint8_t>& memory, std::uint64_t baseAddress, const std::string& label) {
    std::cout << label << " @ 0x" << std::hex << std::setfill('0') << std::setw(12) << baseAddress << std::dec << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    for (size_t i = 0; i < memory.size(); i += 16) {
        std::cout << "0x" << std::hex << std::setfill('0') << std::setw(12) << (baseAddress + i) << "  ";

        // Hex dump
        for (size_t j = 0; j < 16 && i + j < memory.size(); ++j) {
            std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(memory[i + j]) << " ";
        }

        // ASCII representation
        std::cout << " | ";
        for (size_t j = 0; j < 16 && i + j < memory.size(); ++j) {
            char c = static_cast<char>(memory[i + j]);
            if (c >= 32 && c <= 126) {
                std::cout << c;
            } else {
                std::cout << ".";
            }
        }
        std::cout << std::dec << std::endl;
    }
    std::cout << std::endl;
}

// Display register state at crash
void displayRegisters(const RegisterState& regs) {
    std::cout << "REGISTERS AT CRASH TIME:" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    std::cout << "RAX (return value)    : 0x" << std::hex << std::setfill('0') << std::setw(16) << regs.rax << std::endl;
    std::cout << "RBX (callee-saved)    : 0x" << std::hex << std::setfill('0') << std::setw(16) << regs.rbx << std::endl;
    std::cout << "RCX (counter)         : 0x" << std::hex << std::setfill('0') << std::setw(16) << regs.rcx << std::endl;
    std::cout << "RDX (data)            : 0x" << std::hex << std::setfill('0') << std::setw(16) << regs.rdx << std::endl;
    std::cout << "RSI (source index)    : 0x" << std::hex << std::setfill('0') << std::setw(16) << regs.rsi << std::endl;
    std::cout << "RDI (dest index)      : 0x" << std::hex << std::setfill('0') << std::setw(16) << regs.rdi << std::endl;
    std::cout << "RBP (frame pointer)   : 0x" << std::hex << std::setfill('0') << std::setw(16) << regs.rbp << std::endl;
    std::cout << "RSP (stack pointer)   : 0x" << std::hex << std::setfill('0') << std::setw(16) << regs.rsp << std::endl;
    std::cout << "RIP (instruction ptr) : 0x" << std::hex << std::setfill('0') << std::setw(16) << regs.rip << std::dec << std::endl;
    std::cout << std::endl;
}

// Display stack trace
void displayStackTrace() {
    std::cout << "STACK TRACE:" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    std::cout << "#0  0x0000000000401234 in accessFreedMemory () at crash_dump_uaf.cpp:157" << std::endl;
    std::cout << "#1  0x00000000004012ab in demonstrateUseAfterFree () at crash_dump_uaf.cpp:180" << std::endl;
    std::cout << "#2  0x0000000000401300 in main () at crash_dump_uaf.cpp:195" << std::endl;
    std::cout << std::endl;
}

// Demonstrate Use-After-Free crash scenario
void simulateUseAfterFreeCrash() {
    std::cout << std::endl;
    std::cout << "CRASH SCENARIO: Use-After-Free (UAF)" << std::endl;
    std::cout << std::string(80, '=') << std::endl << std::endl;

    std::cout << "SOURCE CODE CONTEXT:" << std::endl;
    std::cout << "  155 int* ptr = new int(42);" << std::endl;
    std::cout << "  156 delete ptr;              // Memory freed, but ptr still points to it" << std::endl;
    std::cout << "  157 int value = *ptr;       // <-- CRASH HERE: Dereferencing freed memory" << std::endl;
    std::cout << std::endl;

    std::cout << "EXPLANATION:" << std::endl;
    std::cout << "  1. Memory was allocated on the heap (address 0x7ffee5b00000)" << std::endl;
    std::cout << "  2. Memory was freed with 'delete' but pointer was not nullified" << std::endl;
    std::cout << "  3. Attempting to dereference freed memory causes segmentation fault" << std::endl;
    std::cout << "  4. Freed memory may be reused by other allocations or marked invalid" << std::endl;
    std::cout << std::endl;

    displayCrashHeader("Use-After-Free", 11);

    // Simulate freed memory pattern (typically 0xCD bytes after deletion)
    std::vector<std::uint8_t> freedMemory(32);
    std::fill(freedMemory.begin(), freedMemory.end(), 0xCD);
    displayMemoryDump(freedMemory, 0x7ffee5b00000, "FREED HEAP MEMORY");

    RegisterState crashRegs;
    crashRegs.rax = 0x0000000000000000;
    crashRegs.rdi = 0x00007ffee5b00000;  // Pointer to freed memory
    crashRegs.rip = 0x0000000000401234;
    displayRegisters(crashRegs);

    displayStackTrace();

    std::cout << "DETECTION & PREVENTION:" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    std::cout << "✓ Use smart pointers (std::unique_ptr, std::shared_ptr)" << std::endl;
    std::cout << "✓ Set pointer to nullptr after delete: delete ptr; ptr = nullptr;" << std::endl;
    std::cout << "✓ Use tools: AddressSanitizer (ASAN), Valgrind, Dr. Memory" << std::endl;
    std::cout << "✓ Code review and testing (use dynamic analysis tools)" << std::endl;
    std::cout << "✓ RAII pattern: use constructors/destructors for resource management" << std::endl;
    std::cout << std::endl;

    std::cout << "SAFE ALTERNATIVE (C++11/17):" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    std::cout << "  // Instead of:" << std::endl;
    std::cout << "  int* ptr = new int(42);" << std::endl;
    std::cout << "  delete ptr;" << std::endl;
    std::cout << "  int value = *ptr;  // CRASH!" << std::endl;
    std::cout << std::endl;
    std::cout << "  // Use smart pointers:" << std::endl;
    std::cout << "  std::unique_ptr<int> ptr = std::make_unique<int>(42);" << std::endl;
    std::cout << "  int value = *ptr;  // Safe, automatic cleanup" << std::endl;
    std::cout << "  // ptr automatically deleted when out of scope" << std::endl;
    std::cout << std::endl;
}

int main() {
    std::cout << std::string(80, '=') << std::endl;
    std::cout << "USE-AFTER-FREE (UAF) CRASH DUMP ANALYSIS" << std::endl;
    std::cout << "Educational Crash Dump Simulation" << std::endl;
    std::cout << std::string(80, '=') << std::endl << std::endl;

    simulateUseAfterFreeCrash();

    std::cout << "WORST-CASE SCENARIOS:" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    std::cout << "1. Security: Attacker could control what gets allocated in freed space" << std::endl;
    std::cout << "2. Data corruption: Writing to freed memory corrupts other objects" << std::endl;
    std::cout << "3. Information leak: Reading freed memory exposes sensitive data" << std::endl;
    std::cout << "4. Code execution: In worst case, could lead to RCE (Remote Code Exec)" << std::endl;
    std::cout << std::endl;

    std::cout << "COMPILATION WITH ASAN (Address Sanitizer):" << std::endl;
    std::cout << "  g++ -std=c++17 -fsanitize=address -g program.cpp -o program" << std::endl;
    std::cout << "  ./program  # Will detect and report UAF automatically" << std::endl;
    std::cout << std::endl;

    return 0;
}
