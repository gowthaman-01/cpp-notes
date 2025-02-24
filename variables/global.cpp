// Note that the following two examples also applies to functions.
// Setting this to const or static will cause it to link internally, causing the linking of variables.cpp to fail.
float GLOBAL_PI = 3.14;

// Removing the static keyword will cause the linking of variables.cpp to fail, as GLOBAL_INT is also defined there.
static int GLOBAL_INT = 5;

int x;      // Strongly discouraged: non-const global variable definition
// x = 5;   // Global scope → Only declarations and initializations allowed. This will result in a compilation error.

void counter() {
    // This variable has function scope but static storage duration (exists for the lifetime of the program).
    static int count = 0;
    count++;
}

void incrementCount() {
    counter();  // count = 1
    counter();  // count = 2
    counter();  // count = 3
}
