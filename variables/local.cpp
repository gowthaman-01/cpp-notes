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

void local_variables() {
    int x { 2 };
    {
        int x { 3 };            // Inner x shadows outer x
        std::cout << x << '\n'; // Prints 3 — only inner x is accessible here
    }

    std::cout << x << '\n'; // Prints 2 — outer x is visible again
}

