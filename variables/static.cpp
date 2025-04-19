/*
 * `static` has different meanings in different contexts.
 *
 * 1. Global variables
 *  - `static` gives a global identifier internal linkage, which means the identifier can only be used in the file in which it is defined.
 *
 * 2. Local variables
 *  - Using the `static` keyword on a local variable changes its duration from automatic duration to static duration.
 *  - Non-const static local variables should only be used if in your entire program and in the foreseeable future of your program,
 *    the variable is unique and it wouldn’t make sense to reset the variable.
 *  - A `const` or `constexpr` static local variable is useful when initializing a value is expensive (e.g., reading from a database).
 *  - It ensures the value is created only once and reused across function calls, avoiding repeated costly initialization.
 *
 * 3. Functions (at global scope)
 *  - `static` gives the function internal linkage just like global static variables.
 *  - Limits the visibility of the function to the current file — useful to avoid naming collisions.

 * 4. Class static variables (data members)
 *  - Shared among all instances of the class (not per-object).
 *  - Must be defined separately outside the class in a .cpp file (unless `inline`).
 *
 * 5. Class static methods
 *  - Do not operate on class instances (no `this` pointer).
 *  - Can only access other `static` members or methods.
 *  - Can be called without creating an object.
 *  - Useful for factory methods, utilities, or accessing global state.
 */

void counter() {
    // This variable has function scope but static storage duration (exists for the lifetime of the program).
    static int s_count{ 0 };     // “s_” to prefix static local variables
    ++s_count;
}

void incrementCount() {
    counter();                  // s_count = 1
    counter();                  // s_count = 2
    counter();                  // s_count = 3
}
