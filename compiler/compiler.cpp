/*
 * Anything with a # prefix is a preprocessor directive, which is handled by the preprocessor during compilation.
 * Preprocessor directives do not end in a ;
 *
 * Header files are not compiled, instead they are copied over through preprocessor directives into a cpp file, which is then compiled.
 * Each cpp file is individually compiled into an object file (machine code) as one translation unit. 
 * The linker will stitch each of these compiled object files together into one executable file.
 *
 * C++ does not care about file extensions. The compiler will treat .cpp file as a C++ file and a .h file as a header file.
 * You can override these default conventions (eg: use .gowthaman as the extension for C++ files) by modifying the compiler configuration.
 *
 * #include <> -> Used to include standard library headers or headers located in predefined system directories.
 * #include "" -> Used to include user-defined headers or headers located in custom paths. If it can’t find a matching header there, it will then search the include directories.
 * Header files in the cpp standard library won't have the .h extension.
 * When including system headers, include the versions with no .h extension if they exist.
 *
 * Order of #include statements (best Practice):
 * 1. The paired header file for this code file (e.g. add.cpp should #include "add.h")
 * 2. Other headers from the same project (e.g. #include "mymath.h")
 * 3. 3rd party library headers (e.g. #include <boost/tuple/tuple.hpp>)
 * 4. Standard library headers (e.g. #include <iostream>)
 * Each grouping should be sorted alphabetically, unless otherwise specified by third-party library documentation.
 *
 * Do not put function and variable definitions in header files as this will likely result in a violation of the one-definition rule (ODR).
 * Definitions for inline functions, inline variables, types, and templates can be safetly added to header files.
 *
 * Source files should #include their paired header file (if one exists) [https://www.learncpp.com/cpp-tutorial/header-files/#comment-398571]
 *
 * Overloading is based on parameter types, not return types.
 * Name mangling includes return types (depending on the compiler), which helps the linker detect definition mismatches (if the declaration and definition of a function disagree on the return type).
 *
 * Directives defined in one file do not have any impact on other files (unless they are #included into another file).
 */

#include <iostream>

// A macro replaces all entries of INTEGER with int during compilation.
// Avoid macros with substitution text unless no viable alternatives exist. (Use global constants instead)
#define INTEGER int

#if 0
// Code here this will not be compiled.
// Remember the endif
#endif

INTEGER compiler () {
    INTEGER i = 0;
    return i;
#include "compiler.hpp"         // Compiler replaces this with the closing bracket from compiler.hpp

/*
 * Using const variables can help the compiler optimize more effectively.
 * Debugging optimized compiled code can be challenging because variables might be removed, and functions might be skipped, making the debugger behave unexpectedly.
 */
void compiler_optimization() {
    int x = 3 + 4;              // Constant folding     - compiler replaces x with 7
    std::cout << x << '\n';     // Constant propogation - compiler replaces x with 7
    
    int y = 7;                  // Dead code            - removed by compiler
}
