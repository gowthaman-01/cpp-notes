#include <iostream>

void number_systems() {
    int octal{012};
    std::cout << octal << '\n';             // Prints 10
    
    int hex{0xF};
    std::cout << hex << '\n';               // Prints 15
    
    int bin{};                              // Assume 16-bit ints.
    bin = 0b1;                              // Assign binary 0000 0000 0000 0001 to the variable
    bin = 0b11;                             // Assign binary 0000 0000 0000 0011 to the variable
    bin = 0b1010;                           // Assign binary 0000 0000 0000 1010 to the variable
    bin = 0b1111'0000;                      // Assign binary 0000 0000 1111 0000 to the variable. Note the digit separator
    // bin = 0b'1011'0010                   // Error: ' used before first digit of value

    int x = 10;
    std::cout << x << '\n';                 // Decimal (by default)
    std::cout << std::hex << x << '\n';     // Hexadecimal
    std::cout << std::oct << x << '\n';     // Octal
    std::cout << std::dec << x << '\n';     // Return to decimal
}
