# Secure C++ Coding Rules

## Memory safety
- Do not use raw `new` or `delete`. Use `std::make_unique`, `std::make_shared`, or containers.
- Follow RAII: acquire resources in constructors and release them in destructors.
- Do not use `malloc`, `free`, or `realloc` in C++ code.
- Check pointers for null before dereferencing, or use references where null is not valid.

## Bounds and integer safety
- Use `.at()`, `std::span`, or range-based loops instead of unchecked `[]` on untrusted indices.
- Check arithmetic used for sizes or indices with `__builtin_add_overflow` / `__builtin_mul_overflow` (GCC and Clang) before use.
- Use explicit casts (`static_cast`). Avoid C-style casts and `reinterpret_cast` unless unavoidable and documented.
- Initialize all variables at declaration.

## Strings and I/O
- Do not use `strcpy`, `strcat`, `sprintf`, or `gets`. Use `std::string`, `std::snprintf` with size limits, or `std::format`.
- Never pass user-controlled data as a format string.
- Validate all external input (files, network, command-line, environment) for length, range, and format before use.

## Undefined behavior
- Avoid signed overflow, out-of-bounds access, use-after-free, data races, and uninitialized reads.
- Never return references or pointers to local variables.

## Error handling
- Use exceptions or check every error return value. Mark error-returning functions `[[nodiscard]]`.
- Do not let exceptions escape destructors or `noexcept` functions.

## Randomness and cryptography
- Use `<random>` (for example `std::mt19937` seeded from `std::random_device`). Do not use `rand()` for security.
- Do not write your own cryptography. Use vetted libraries such as OpenSSL or libsodium.
- Compare secrets and MACs in constant time.
- Never hardcode passwords, keys, or tokens. Load them from a secure source at runtime.

## Files and paths
- Canonicalize and validate file paths from untrusted input to prevent path traversal.
- Check the result of every open, read, and write.

## Concurrency
- Protect shared data with `std::mutex` or atomics, using `std::scoped_lock` or `std::lock_guard`.
- Do not share mutable state across threads without synchronization.

## Build and analysis
- Compile with `-Wall -Wextra -Wpedantic -Werror`.
- Harden release builds: `-O2 -D_FORTIFY_SOURCE=3 -D_GLIBCXX_ASSERTIONS -fstack-protector-strong -fPIE -pie`.
- Test with sanitizers during development: `-fsanitize=address,undefined` (add `-fsanitize=thread` for concurrent code).
- Run `clang-tidy` with the `bugprone-*`, `cert-*`, and `clang-analyzer-*` checks enabled.

## Review checklist
Before finishing any change, confirm: no raw memory management, no unchecked indices or sizes, no unsafe C functions, no hardcoded secrets, input is validated, and the code builds cleanly with the flags above.