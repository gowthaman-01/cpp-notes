#include <iostream>

int cerr_demo() {
    // When adding temporary debug statements, it can be helpful to not indent them.
    // This makes them easier to find for removal later.
std::cerr << "Error message\n";
    return 4;
}
