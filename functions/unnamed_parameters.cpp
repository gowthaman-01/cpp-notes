#include <iostream>
#include <typeinfo>

// 1. Unnamed parameter in a regular function
void foo(int /*bar*/) {
    // Parameter is unused, but kept to avoid breaking existing function calls.
}

// 2. Operator overloading (++ and --)
struct Counter {
    int value = 0;

    // Prefix increment: ++x
    Counter& operator++() {
        ++value;
        return *this;
    }

    // Postfix increment: x++
    Counter operator++(int) {
        // The 'int' parameter is unused but required to differentiate postfix.
        Counter temp = *this;
        ++value;
        return temp;
    }
};

// 3. Template function with unnamed parameter
template <typename T>
void printType(T) {
    // We care about the type of T, not the value
    std::cout << "Type: " << typeid(T).name() << '\n';
}

template <typename T>
void checkTypeSize(T) {
    // Unused parameter T is passed only to check the type
    static_assert(sizeof(T) > 1, "Type size too small");
}
