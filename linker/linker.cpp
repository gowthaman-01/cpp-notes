/*
 * A function has a unique signature which is used by the linker to link multiple object files into one executable.
 * The main() function is usually the entry point to a C++ application, but this can be changed.
 */

#include "linker.hpp"

// The linker will look for function definitions with the same name, return type and parameters.
// Note that there is no definition for this log function.
// This is done on purpose to demonstrate linker behavior in the 'link' function defined below.
void log(const char* message);

// This function is marked as static, which means it is only delcared for use by the current file and not visible to other files.
static void link() {
    // There is no error during linking even though log is not defined as the link function is never called elsewhere.
    log("message");
    linkHelper();
}
