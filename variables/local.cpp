#include <iostream>

/*
 * Scope determines where declaration of a single identifier can be seen and used in the code.
 * Linkage determines whether multiple declarations of the same identifier refer to the same object or not.
 *
 * Local variables have
 * - Block scope (are only visible within the block they are declared in).
 * - Automatic duration (they are created at the point of definition and destroyed when the block is exited).
 
 * Define variables in the most limited existing scope.
 * Avoid creating new blocks whose only purpose is to limit the scope of variables.
 */

extern int x;

void local_variables() {
    int x { 2 };

    {
        // At this point, 'x' from the outer block is still in scope.
        std::cout << x << '\n';     // Prints 2 (outer 'x')

        // This 'x' shadows the outer 'x'. This should be avoided.
        // Within this block, all references to 'x' refer to this inner variable
        int x { 3 };

        std::cout << x << '\n';     // Prints 3 (inner 'x')
        std::cout << ::x << '\n';   // Prints 1 (global 'x', defined in constants.cpp)
    }

    // The inner 'x' goes out of scope here. The outer 'x' is now visible again.
    std::cout << x << '\n';         // Prints 2 (outer 'x')
}
