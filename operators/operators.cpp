#include <iostream>

int getValue() {
    std::cout << "Enter an integer: ";

    int x{};
    std::cin >> x;
    return x;
}

void printCalculation(int x, int y, int z) {
    std::cout << x + (y * z);
}

/*
 * Operator precedence and associativity determine how operands are grouped with operators, not evaluation order.
 * Operands, function arguments, and subexpressions can be evaluated in any order.
 * Avoid writing expressions or function calls that rely on a specific order of evaluation.
 */
void order_of_evaluation() {
    // This line is ambiguous.
    // If we enter the inputs 1, 2, and 3, we expect 1 + (2 * 3) = 7 to be printed.
    // But this is not guarenteed, the arguments might evaluate in right-to-left order in certain compilers.
    // Instead create 3 variables to store the 3 user entered values.
    printCalculation(getValue(), getValue(), getValue());
}
