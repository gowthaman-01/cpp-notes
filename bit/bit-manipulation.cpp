#include <bitset>
#include <iostream>

/*
 * In modern computer architectures, the smallest unit of memory is a byte.
 * A boolean, which only needs 1 bit, uses a full byte—wasting 7 bits.
 * It is more efficient to pack multiple Booleans into a single byte.
 * To avoid surprises, use the bitwise operators with unsigned integral operands or std::bitset
 */
void bitset() {
    [[maybe_unused]] constexpr int isHungry   { 0 };
    [[maybe_unused]] constexpr int isSad      { 1 };
    [[maybe_unused]] constexpr int isMad      { 2 };
    [[maybe_unused]] constexpr int isHappy    { 3 };
    [[maybe_unused]] constexpr int isLaughing { 4 };
    [[maybe_unused]] constexpr int isAsleep   { 5 };
    [[maybe_unused]] constexpr int isDead     { 6 };
    [[maybe_unused]] constexpr int isCrying   { 7 };

    // std::bitset is optimized for speed, not memory.
    // Although it can represent 8 bits, a std::bitset<8> usually takes 4 or 8 bytes due to alignment with size_t.
    // It's best used for convenience, not space efficiency.
    std::bitset<8> me{ 0b0000'0101 };               // Bit 0 and 2 are set

    me.set(isHappy);                                // Bit 3 → set to 1   → 0000'1101
    me.flip(isLaughing);                            // Bit 4 → flip       → 0001'1101
    me.reset(isLaughing);                           // Bit 4 → reset to 0 → 0000'1101

    std::cout << "My state: " << me << '\n';
    std::cout << "I am happy? " << me.test(isHappy) << '\n';
    std::cout << "I am laughing? " << me.test(isLaughing) << '\n';
    
    std::cout << me.size() << '\n';                 // 8
    std::cout << me.count() << '\n';                // Set bits -> 3
    std::cout << me.any() << '\n';                  // All set -> true
    std::cout << me.none() << '\n';                 // None set -> false
    std::cout << me.to_ulong() << '\n';             // Convert to long -> 13
}

/*
 * Bitwise operations promote small types (e.g., uint8_t) to int/unsigned int.
 * This can cause unexpected results with ~ or << due to width differences.
 * Avoid bitwise ops on small types (use int or uint32_t).
 * If needed, use static_cast<original_type>(...) after bitwise operations.
 *
 * In bitwise XOR, if a column has an odd number of 1s, the result is 1; if it's even, the result is 0.
 */
void bit_manipulation() {
    int x = 1;
    
    std::cout << x << 1 << '\n';                    // print value of x (0110), then 1
    std::cout << (x << 1) << '\n';                  // print x left shifted by 1 (1100)
}


std::bitset<4> rotl(std::bitset<4> bits) {
    // Keep track of whether the leftmost bit was a 1
    const bool leftbit{ bits.test(3) };

    bits <<= 1; // Left shift (which shifts the leftmost bit off the end)

    // If the left bit was a 1
    if (leftbit)
        bits.set(0); // Set the rightmost bit to a 1

    return bits;
}

std::bitset<4> rotl_bitwise(std::bitset<4> bits) {
    // bits << 1 does the left shift
    // bits >> 3 handle the rotation of the leftmost bit
    return (bits << 1) | (bits >> 3);
}

// Hard to read and maintain
void configure_options_with_booleans(bool option1, bool option2, bool option3, bool option4, bool option5, bool option6, bool option7, bool option8, bool option9, bool option10, bool option11, bool option12, bool option13, bool option14, bool option15, bool option16, bool option17, bool option18, bool option19, bool option20, bool option21, bool option22, bool option23, bool option24, bool option25, bool option26, bool option27, bool option28, bool option29, bool option30, bool option31, bool option32) {}

// Clean and scalable
void configure_options(std::bitset<32> options) {}

/*
 * Bit flags don’t *always* save memory!
 * - Example: 8 individual bools → 8 bytes
 * - One `std::uint8_t` + 8 constexpr masks → ~9 bytes
 *
 * Use bit flags when:
 *  - You have many identical flag variables (e.g., in arrays or structs).
 *  - You want to compactly pass multiple boolean options to functions.
 */
void bit_mask() {
    constexpr std::uint8_t option0{ 0b0000'0001 };  // represents bit 0
    constexpr std::uint8_t option1{ 0b0000'0010 };  // represents bit 1
    constexpr std::uint8_t option2{ 0b0000'0100 };  // represents bit 2
    constexpr std::uint8_t option3{ 0b0000'1000 };  // represents bit 3
    constexpr std::uint8_t option4{ 0b0001'0000 };  // represents bit 4
    constexpr std::uint8_t option5{ 0b0010'0000 };  // represents bit 5
    constexpr std::uint8_t option6{ 0b0100'0000 };  // represents bit 6
    constexpr std::uint8_t option7{ 0b1000'0000 };  // represents bit 7
    
    std::uint8_t flags{ 0b1010'1110 };
    
    // Using bit flags:
    if (flags & option4) {}                         // If option4 is set, do something
    
    flags |= option4;                               // Turn option 4 on.
    flags |= (option4 | option5);                   // Turn options 4 and 5 on.

    flags &= ~option4;                              // Turn option 4 off
    flags &= ~(option4 | option5);                  // Turn options 4 and 5 off

    flags ^= option4;                               // Flip option4
    flags ^= (option4 | option5);                   // Flip options 4 and 5
    
    // Instead of this
    configure_options_with_booleans(false, false, false, false, false, false, false, false, false, true, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, true);

    // Do this
    configure_options(option1 | option2);

}

/* This function extracts and prints the individual 8-bit RGBA components from a 32-bit hexadecimal color value.
 *
 * Background:
 *  - In displays, each pixel is made up of red, green, and blue light (RGB).
 *  - Each RGB component has an intensity from 0 to 255 (stored in 8 bits).
 *  - An optional 4th component, alpha (A), represents transparency.
 *  - A = 0 means fully transparent, A = 255 means fully opaque.
 *
 * In 32-bit RGBA representation:
 *  - Bits 31–24: Red
 *  - Bits 23–16: Green
 *  - Bits 15–8 : Blue
 *  - Bits 7–0  : Alpha
 *
 * Example Input:
 *   Input: 0xFF7F3300
 *   Binary layout: [11111111 01111111 00110011 00000000]
 *   Output:
 *   ff red
 *   7f green
 *   33 blue
 *   0 alpha
*/
void printColorChannelsFromRGBA(std::uint32_t pixel)
{
    constexpr std::uint32_t redBits   { 0xFF000000 };
    constexpr std::uint32_t greenBits { 0x00FF0000 };
    constexpr std::uint32_t blueBits  { 0x0000FF00 };
    constexpr std::uint32_t alphaBits { 0x000000FF };

    // Extract each channel using bitwise AND and right shift
    const std::uint8_t red   { static_cast<std::uint8_t>((pixel & redBits) >> 24) };
    const std::uint8_t green { static_cast<std::uint8_t>((pixel & greenBits) >> 16) };
    const std::uint8_t blue  { static_cast<std::uint8_t>((pixel & blueBits) >> 8) };
    const std::uint8_t alpha { static_cast<std::uint8_t>(pixel & alphaBits) };

    std::cout << "Your color contains:\n";
    std::cout << std::hex;
    std::cout << static_cast<int>(red)   << " red\n";
    std::cout << static_cast<int>(green) << " green\n";
    std::cout << static_cast<int>(blue)  << " blue\n";
    std::cout << static_cast<int>(alpha) << " alpha\n";
}

