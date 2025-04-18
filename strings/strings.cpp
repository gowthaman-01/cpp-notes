/*
 * 1. C-Style String Literals
 -----------------------------
 * Include an implicit null terminator ('\0') to mark the end of the string.
 * Const objects that exist for the entire duration of the program (static duration).
 * Safe to use with `std::string_view` (no risk of dangling).
 *
 * 2. Temporary objects
 -----------------------------
 * Unlike C-style string literals, std::string and std::string_view literals ("text"s and "text"sv) create temporary objects.
 * These temporary objects must be used immediately, as they are destroyed at the end of the full expression in which they are created.
 *
 * 3. Null Termination
 -----------------------------
 - `std::string_view` does not guarantee null-termination.
 - Don't pass it to C-style APIs expecting `const char*`.
 - Instead, convert explicitly: `std::string(str_view).c_str();` (using str_view.data() is also bad practice)
 *
 * 4. `std::string`
 -----------------------------
 * - Owns and manages its buffer.
 * - Modifiable, null-terminated, and safe to pass to C APIs.
 * - Copying/initializing can be expensive.
 * - Avoid passing by value unless necessary (prefer `const std::string&`).
 * - Modifying the string can **invalidate views** to it.
 * - Returning `std::string` by value is okay (RVO + move semantics optimize this).
 *
 * 5. `std::string_view`
 -----------------------------
 * - Lightweight, read-only view into an existing string (does not own the data).
 * - Fast to copy and pass by value.
 * - Typically used as function parameters and viewing static literals
 * - View becomes invalid if the original string is modified or destroyed.
 * - View length doesn't update even if the source string changes.
 * - May point to garbage if it outlives its source.
 *
 * 6. Further Reading
 -------------------
 * https://www.learncpp.com/cpp-tutorial/stdstring_view-part-2/#stringvsstringview
 * https://www.learncpp.com/cpp-tutorial/chapter-5-summary-and-quiz
 *
 */

#include <iostream>
#include <string>
#include <string_view>

void print_string() {
    std::string name{};
    // When extracting a string with std::cin >>, it stops at the first whitespace, leaving the rest in the input buffer.
    // If you enter "John Doe", std::cin >> name gets "John" and leaves "Doe" in the buffer.
    
    // Instead, use std::getline() with std::cin >> std::ws input manipulator to ignore leading whitespace.
    // This needs to be done for each std::getline() call, as std::ws is not preserved across calls.
    std::getline(std::cin >> std::ws, name);
}

void string_view() {
    // When a std::string object is initialized, it makes an independent copy of the initializer's value.
    // This copy ensures that the string is not affected by any changes to the initializer after initialization.
    // The downside is that this independence comes with the cost of making an expensive copy.
    std::string s{"Hello"};
    std::string_view sv { "World" };                // Initialize with C-style string literal
    std::string_view sv2 { s };                     // Initialize with std::string
    std::string_view sv3 { sv };                    // Initialize with std::string_view

    sv = "Foobar";                                  // sv is now viewing "Foobar" instead of "Hello"
}

// Will accept arguments of type C-style string, std::string, or std::string_view:
void print_string_view(std::string_view str) {
    std::cout << str << '\n';
}

// Will accept arguments of type C-style string and std::string but not std::string_view.
// A possible workaroud is to print_string(std::string{sv}) or print_string(static_cast<std::string>(sv))
void print_string(std::string str) {
    std::cout << str << '\n';
}

void string_literals() {
    using namespace std::string_literals;           // Access the s suffix
    using namespace std::string_view_literals;      // Access the sv suffix

    std::cout << "foo\n";                           // No suffix is a C-style string literal
    std::cout << "goo\n"s;                          // s suffix is a std::string literal
    std::cout << "moo\n"sv;                         // sv suffix is a std::string_view literal
}

void string_view_parameter(std::string_view s) {
    // Prefer std::string_view or const std::string&
}

std::string getName() {
    std::string s{"Gowthaman"};
    return s;
}

std::string_view getName2() {
    std::string name{"Gowthaman"};
    return name;
}

std::string_view getName3() {
    return "Gowthaman";                             // C-style string that is valid for the entirety of the program
}

std::string_view getName4(std::string_view name) {
    return name;
}

void string_view_improper_use() {
    using namespace std::string_literals;
    
    std::string_view sv{};

    {
        std::string s{ "Hello, world!" };
        sv = s;
    }                                               // s is destroyed here, so sv is now viewing an invalid string
    
    // Return values are temporary objects that are destroyed at the end of the full expression containing the function call.
    // We must either use this return value immediately, or copy it to use later.
    // std::string_view doesn’t make copies. Instead, it creates a view to the temporary return value, which is then destroyed.
    // That leaves the std::string_view dangling (viewing an invalid object), and printing the view results in undefined behavior.
    std::string_view sv2{getName()};                // Invalid
    std::string_view sv3(getName2());               // Invalid
    std::string_view sv4(getName3());               // Valid (C-style string literal)
    std::string_view sv5(getName4("Gowthaman"));    // Valid (C-style string literal)
    std::string_view sv6 {"Gowthaman"s};            // "Gowthaman"s creates a temporary std::string which is destroyed immediately.
    
    // Initialize with a C-style string literal or a std::string_view literal instead.
    std::string_view sv7 {"Gowthaman"};
    
    std::string s {"Hello, world!"};
    std::string_view sv8 { s };
    // When a std::string is modified, any std::string_view pointing to it may become invalid, leading to undefined behavior.
    // If the std::string reallocates memory to accommodate new data, the old memory is released,
    // causing the std::string_view to dangle (point to invalid memory).
    // If no reallocation occurs: The std::string_view will point to the new data but won’t recognize length changes.
    // If the new string is longer, the view shows a substring of the new string.
    // If shorter, the view includes extra, potentially garbage characters beyond the new string's end.
    s = "Hello, a!";                                // sv8 becomes invalidated.
    
    std::string s2 {"Foobar"};
    sv5 = s2;                                       // Now sv8 is revalidated.
}

void view_modification() {
    std::string_view str{ "Peach" };

    // Remove 1 character from the left side of the view
    str.remove_prefix(1);                           // "each"

    // Remove 2 characters from the right side of the view
    str.remove_suffix(2);                           // "ea"
    
    //  The only way to reset the view is by reassigning the source string to it again.
    str = "Peach";
}
