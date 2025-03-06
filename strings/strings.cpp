/*
 * C-style string literals include an implicit null terminator ('\0') to mark the end of the string.
 * C-style string literals are const objects that exist for the entire duration of the program.
 *
 * Unlike C-style string literals, std::string and std::string_view literals create temporary objects.
 * These temporary objects must be used immediately, as they are destroyed at the end of the full expression in which they are created.
 *
 * An initialized object has no control over what happens to the initialization value after initialization is finished.
 *
 * Take care not to write any code that assumes a std::string_view is null terminated.
 * If you have a non-null-terminated std::string_view and you need a null-terminated string for some reason, convert the std::string_view into a std::string.
 *
 * std::string provides a modifiable string. It is expensive to initialize and copy.
 * std::string_view provide a read-only view of a string that exists elsewhere. It is inexpensive to initialize and copy.
 *
 * Things to remember about std::string:
 * - Initializing and copying std::string is expensive, so avoid this as much as possible.
 * - Avoid passing std::string by value, as this makes a copy.
 * - If possible, avoid creating short-lived std::string objects.
 * - Modifying a std::string will invalidate any views to that string.
 * - It is okay to return a local std::string by value due to Return Value Optimization (RVO) and move semantics.
 *
 * Things to remember about std::string_view:
 * - std::string_view is typically used for passing string function parameters and returning string literals.
 * - Because C-style string literals exist for the entire program, it is always okay to set a std::string_view to a C-style string literal.
 * - When a string is destroyed, all views to that string are invalidated.
 * - Using an invalidated view (other than using assignment to revalidate the view) will cause undefined behavior.
 * - A std::string_view may or may not be null-terminated.
 *
 * Refer to code at https://www.learncpp.com/cpp-tutorial/chapter-5-summary-and-quiz for example use of std::string and std::string_view
 *
 * TODO: Reread https://www.learncpp.com/cpp-tutorial/stdstring_view-part-2/#stringvsstringview
 */

#include <iostream>
#include <string>
#include <string_view>

void print_string() {
    std::string name{};
    // When extracting a string with std::cin >>, it stops at the first whitespace, leaving the rest in the input buffer.
    // If you enter "John Doe", std::cin >> name gets "John" and leaves "Doe" in the buffer.
    
    // Use std::getline() instead
    // use std::cin >> std::ws input manipulator to ignore leading whitespace.
    // This needs to be done for each std::getline() call, as std::ws is not preserved across calls.
    std::getline(std::cin >> std::ws, name);
}

void string_view() {
    // When a std::string object is initialized, it makes an independent copy of the initializer's value.
    // This copy ensures that the string is not affected by any changes to the initializer after initialization.
    // The downside is that this independence comes with the cost of making an expensive copy.
    std::string s{"Sample"};
    
    std::string_view sv { "Hello, world!" };        // Initialize with C-style string literal
    
    std::string s2{ "Hello, world!" };
    std::string_view sv2 { s };                      // Initialize with std::string

    std::string_view sv3 { s2 };                     // Initialize with std::string_view
    
    s2 = "Foobar";                                  // s2 is now viewing "Foobar" instead of "Hello, world!"
}

// Will accept arguments of type C-style string, a std::string, or std::string_view:
void printSV(std::string_view str) {
    std::cout << str << '\n';
}

// Will not accept std::string_view.
// A possible workaroud is to printString(std::string{sv}) or printString(static_cast<std::string>(sv))
void printString(std::string str) {
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
    std::string_view sv4(getName3());               // Valid
    std::string_view sv5(getName4("Gowthaman"));    // Valid
    std::string_view sv6(getName4("Gowthamans"));   // Invalid
            
   
    std::string_view sv7 {"Gowthaman"s};            // "Gowthaman"s creates a temporary std::string which is destroyed immediately.
    // Initialize with a C-style string literal or a std::string_view literal instead.
    // It’s also okay to initialize a std::string_view with a C-style string object, a std::string object, or a std::string_view object,
    // as long as that string object outlives the view.
    std::string_view sv8 {"Gowthaman"};
    
    std::string s {"Hello, world!"};
    std::string_view sv9 { s };
    // When a std::string is modified, any std::string_view pointing to it may become invalid, leading to undefined behavior.
    // If the std::string reallocates memory to accommodate new data, the old memory is released,
    // causing the std::string_view to dangle (point to invalid memory).
    // If no reallocation occurs: The std::string_view will point to the new data but won’t recognize length changes.
    // If the new string is longer, the view shows a substring of the new string.
    // If shorter, the view includes extra, potentially garbage characters beyond the new string's end.
    s = "Hello, a!";                                // sv5 becomes invalidated.
    
    std::string s2 {"Foobar"};
    sv5 = s2;                                       // Now sv5 is revalidated.
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
