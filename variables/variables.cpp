/*
 * 1. Data Types and Byte Allocation:
 *    - The primary difference between data types is the amount of bytes allocated when initialized.
 *    - An object with n bits can hold 2^n unique values.
 *
 * 2. Signed and Unsigned Ranges:
 *    - n-bit signed variable: Range = -(2^n-1) to (2^n-1) - 1
 *    - n-bit unsigned variable: Range = 0 to (2^n) - 1
 *    - Ranges assume two’s complement binary representation, the standard for modern architectures.
 *
 * 3. Fixed-Width Integer Types (C++11):
 *    - Ensures consistent size and range across platforms.
 *    - Defined in <cstdint>.
 *    - These are aliases for existing types. For example, std::int32_t may alias int or long depending on the platform.
 *
 *    | Name            | Size    | Range                                                     | Notes                       |
 *    |-----------------|---------|-----------------------------------------------------------|-----------------------------|
 *    | std::int8_t     | 1 byte  | -128 to 127                                               | Treated like signed char    |
 *    | std::uint8_t    | 1 byte  | 0 to 255                                                  | Treated like unsigned char  |
 *    | std::int16_t    | 2 bytes | -32,768 to 32,767                                         |                             |
 *    | std::uint16_t   | 2 bytes | 0 to 65,535                                               |                             |
 *    | std::int32_t    | 4 bytes | -2,147,483,648 to 2,147,483,647                           |                             |
 *    | std::uint32_t   | 4 bytes | 0 to 4,294,967,295                                        |                             |
 *    | std::int64_t    | 8 bytes | -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807   |                             |
 *    | std::uint64_t   | 8 bytes |  0 to 18,446,744,073,709,551,615                          |                             |
 *
 *    - std::int8_t and std::uint8_t behave like char and unsigned char.
 *    - Use static_cast<int>(variable) to print them as integers.
 *
 * 6. Best Practices:
 *    - Prefer 'int' when the size doesn’t matter.
 *    - Use std::int#_t for quantities requiring a guaranteed range.
 *    - Use std::uint#_t for bit manipulation or wrap-around behavior (e.g., cryptography).
 *
 * 7. Avoid (if possible):
 *    - short and long integers (platform-dependent size), use fixed-width types instead.
 *    - Fast and least integral types (unpredictable size), prefer fixed-width types.
 *    - Unsigned types for holding quantities, use signed integers (see infinite_loop() below).
 *    - 8-bit fixed-width integers are often treated as char types instead of real integers, prefer 16-bit fixed-width types.
 *
 * 8. Misc
 *    - CPUs are often optimized for 32-bit processing. A 32-bit int may be faster than 16-bit or 8-bit types.
 *    - Use sizeof(datatype) to determine the exact size on your machine.
 *    - Define variables as close to their first use as reasonable.
 *
 * TODO (Initialization Techniques to Explore):
 *  1. Aggregate initialization
 *  2. Copy-list-initialization
 *  3. Reference initialization
 *  4. Static, constant, and dynamic initialization
 *  5. Zero-initialization
 */

#include <iostream>
#include <cstddef>
#include <cstddef>

typedef long lo;

// Denotes that the variable is defined in an external p.
extern float GLOBAL_PI;

int GLOBAL_INT = 5;

void dataTypes() {
    std::cout << GLOBAL_PI;
    // Integer types
    int i                   = GLOBAL_INT;               // 4 bytes, range: -2,147,483,648 to 2,147,483,647
    unsigned int ui         = 4294967295U;              // 4 bytes, range: 0 to 4,294,967,295

    // Character types
    char c                  = 'A';                      // 1 byte, range: -128 to 127
    unsigned char uc        = 255;                      // 1 byte, range: 0 to 255
    wchar_t wc              = L'A';                     // 2 or 4 bytes, wide character literal
    char16_t u16            = u'A';                     // 2 bytes, UTF-16 character literal
    char32_t u32            = U'A';                     // 4 bytes, UTF-32 character literal

    // Short types
    short s                 = 32767;                    // 2 bytes, range: -32,768 to 32,767
    unsigned short us       = 65535;                    // 2 bytes, range: 0 to 65,535

    // Long types
    lo l                    = 2147483647L;              // At least 4 bytes
    unsigned long ul        = 4294967295UL;             // At least 4 bytes

    // Long long types
    long long ll            = 9223372036854775807LL;    // At least 8 bytes
    unsigned long long ull  = 18446744073709551615ULL;  // At least 8 bytes

    // Floating-point types
    float f                 = 1.7F;                     // 4 bytes appending a F denotes a float, else it will be set to a double.
    double d                = 1.7E+308;                 // 8 bytes
    long double ld          = 1.7E+308L;                // 8, 12, or 16 bytes

    // Boolean type
    bool b                  = true;                     // 1 byte
    
    // Null pointer
    std::nullptr_t p        = nullptr;                  // 4 or 8 bytes
    
    std::size_t int_size    = sizeof(int);              // Prints actual size of integer based on machine architecture.
    
    
}

void initialization() {
    int a;                                              // default-initialization

    // Traditional initialization forms:
    int c (6);                                          // direct-initialization
    // Copy-initialization is also used whenever values are implicitly copied, such as when:
    // - Passing arguments to a function by value
    // - Returning from a function by value
    // - Catching exceptions by value.
    int b = 5;                                          // copy-initialization
    

    // Modern initialization forms (preferred):
    int d {7};                                          // direct-list-initialization
    int e {};                                           // value-initialization / zero-initialization to value 0
    
    // Benefits of direct-list-intitialization:
    // int w1 { 4.5 };                                  // compile error
    int w2 = 4.5;                                       // compiles
    int w3 (4.5);                                       // compiles
    
    // Use direct-list-initialization when you’re actually using the initial value:
    int x {0};
    std::cout << x << std::endl;
   
    // Use value-initialization when the object’s value is temporary and will be replaced
    int y {};
    std::cin >> y;
    
    [[maybe_unused]] double pi { 3.14159 };             // Don't complain if pi is unused
}

void benefits_of_brace_initialization() {
    // 1. Prevents Narrowing Conversions
    // int x {4.5};                 // Compiler error
    int y = 4.5;                    // Compiles, but silently truncates to 4

    // 2. Supports Uniform Initialization
    int num{5};                     // Works for built-in types
    std::vector<int> vec{1, 2, 3};  // Works for STL containers
    // MyClass obj{5, 10};          // Works for custom classes

    // 3. Avoids Most Vexing Parse
    std::vector<int> v1(10, 1);  // Creates a vector with 10 elements, all 1
    std::vector<int> v2{10, 1};  // Creates a vector with two elements: {10, 1}

    // 4. Prevents Uninitialized Variables
    int a;                      // Undefined value (garbage)
    int b {};                   // Zero-initialized
    
    // 5. Consistent behavior across types
    int x{};                    // Zero-initialized (x = 0)
    double d{};                 // Zero-initialized (d = 0.0)
    std::string s{};            // Default constructor is called (s = "")
}
void infinite_loop() {
    // for (std::size_t i = n; i >= 0; --i) { //  Infinite loop! (size_t is always ≥ 0)
}
