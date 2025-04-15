/*
 * Global variables are created when the program starts (before main() begins execution), and destroyed when it ends.
 * This is called static duration.
 *
 * An identifier with internal linkage can be seen and used within a single translation unit,
 * but it is not accessible from other translation units.
 *
 * An identifier with external linkage can be seen and used both from the file in which it is defined,
 * and from other code files (via a forward declaration).
 *
 * Consider using a “g” or “g_” prefix when naming global variables (especially those defined in the global namespace),
 * to help differentiate them from local variables and function parameters.
 */

// Functions and non const (or constexpr) global variables have external linkage by default.
// Setting this to const or static will cause it to link internally, causing the linking of data.cpp to fail.
float GLOBAL_PI = 3.14;

// Removing the static keyword will cause the linking of data.cpp to fail, as GLOBAL_INT is also defined there.
static int GLOBAL_INT = 5;

// Non-constant global variables (should be avoided)
int g_x;                        // Defines non-initialized global variable (zero initialized by default)
// g_x = 5;                     // Error: Only declarations and initializations allowed in the global scope
int g_x2 {};                    // Defines explicitly value-initialized global variable
int g_x3 { 1 };                 // Defines explicitly initialized global variable

// const globals have internal linkage by default
// const int g_y;               // Error: const variables must be initialized
const int g_y { 2 };            // Defines initialized global const
extern const int g_y2 { 1 };    // Variable definition (const requires initializers) and external linkage
extern const int g_y3;          // Forward declaration (no initializer)

// constexpr globals have internal linkage by default
// constexpr int g_z;           // Error: constexpr variables must be initialized
constexpr int g_z { 3 };        // Defines initialized global constexpr

namespace Foo {
    int g_z {};             // g_z is now inside the Foo namespace, but is still a global variable
}

// g_z can be accessed through Foo::g_z

void counter() {
    // This variable has function scope but static storage duration (exists for the lifetime of the program).
    static int count = 0;
    count++;
}

void incrementCount() {
    counter();      // count = 1
    counter();      // count = 2
    counter();      // count = 3
}
