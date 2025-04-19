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
 
 * Avoid initializing objects with static duration (like global variables)
 * using other objects with static duration from a different translation unit.
 * as the order of initialization isn’t guaranteed.
 
 * Dynamic initialization of global variables is also susceptible to initialization order issues
 * and should be avoided whenever possible.
 *
 * Globals can be justified in rare cases where:
 * - Only one instance will ever exist (e.g., log file, random number generator).
 * - The object is used everywhere in the program (e.g., std::cout, std::cin).
 */

// Forward declarations
int init_x();
int init_y();

int g_init_x{ init_x() };       // g_x is initialized first
int g_init_y{ init_y() };

int init_x() {
    return g_init_y;            // g_y isn't initialized when this is called
}

int init_y() {
    return 5;
}


// Functions and non const (or constexpr) global variables have external linkage by default.
// Setting this to const or static will cause it to link internally, causing the linking of data.cpp to fail.
float GLOBAL_PI = 3.14;

// Removing the static keyword will cause the linking of data.cpp to fail, as GLOBAL_INT is also defined there.
static int GLOBAL_INT = 5;

// Non-constant global variables (SHOULD BE AVOIDED!)
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
    // g_z can be accessed through Foo::g_z
    int g_z {};                 // g_z is now inside the Foo namespace, but is still a global variable
}

/*
 **********************************
 * GLOBAL VARIABLES BEST PRACTICES
 **********************************
 */

// 1. Use a namespace to avoid naming collisions
namespace constants {
    constexpr double gravity { 9.8 };
}

// 2. Encapsulate access through a function (for validation or refactoring)
double getGravity() {
    return constants::gravity;
}

// 3. Pass global values as parameters instead of accessing them inside the function
// Example usage: instantVelocity(5, constants::gravity)
double instantVelocity(int time, double gravity) {
    return gravity * time;
}
