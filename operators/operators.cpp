#include <iostream>
#include <cmath>
#include <vector>

int getValue() {
    std::cout << "Enter an integer: ";

    int x{};
    std::cin >> x;
    return x;
}

void printCalculation(int x, int y, int z) {
    std::cout << x + (y * z);
}

int foo() {
    std::cout << "f\n"; return 1;
}
int bar() {
    std::cout << "g\n"; return 2;
}

void operator_precedence() {
    int x, y, z, a, b, c, d;
    
    x = 3 + 4 + 5;
    x = ((3 + 4) + 5);

    x = y = z;
    x = (y = z);

    z *= ++y + 5;
    z *= ((++y) + 5);

    a || b && c || d;
    (a || (b && c)) || d;
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
    
    // Similar UB
    int i = 1;
    printCalculation(i, ++i, ++i);
    
    // Can print f g OR g f
    int x = foo() + bar();
    
    // UB: 'i' is modified and read in same expression
    int arr[5];
    arr[i] = i++;
}

void division() {
    // Integer vs Floating Point Division
    constexpr int i = 7;
    constexpr int j = 4;
    
    std::cout << "int / int = " << i / j << '\n';                                                   // 1 (integer division)
    std::cout << "double / int = " << static_cast<double>(i) / j << '\n';                           // 1.75
    std::cout << "int / double = " << i / static_cast<double>(j) << '\n';                           // 1.75
    std::cout << "double / double = " << static_cast<double>(i) / static_cast<double>(j) << '\n';   // 1.75
}

void mod() {
    // x % y always returns results with the sign of x.
    int a = -6 % 4;                 // -2
    int b = 6 % -4;                 // 2
    
    // int c = 4.0 % 2;             // Compiler error (% only allowed on int)
    
    // bool is_odd = (a % 2) == 1;  // Fails when x is -5
    bool is_odd = (a % 2) != 0;
    bool isEven = (a % 2) == 0;
}

/*
 * Integer exponentiation will overflow the integral type in most cases.
 * This is why such a function wasn’t included in standard library.
 */
void exponentiation() {
    // Parameters and return value of function pow() are of type double.
    double x = std::pow(3.0, 4.0);
}

void comma_operator() {
    // Separator comma: used to declare multiple variables on the same line
    // Avoid this style for clarity; define one variable per line
    int a, b, z;
    
    // Evaluate (a, b) first to get result of b, then assign that value to variable z.
    z = (a, b);
    
    // Evaluates as "(z = a), b"
    // So z gets assigned the value of a, and b is evaluated and discarded.
    z = a, b;
    
    std::vector<int> arr{ 1, 2, 3, 4, 5, 6 };

    // Two-pointer loop: i starts at the beginning, j starts at the end.
    // Moves inward and prints pairs of elements.
    // Output:
    // Pair: 1 + 6 = 7
    // Pair: 2 + 5 = 7
    // Pair: 3 + 4 = 7
    for (int i = 0, j = static_cast<int>(arr.size()) - 1;
         i < j;
         ++i, --j) {
        std::cout << "Pair: " << arr[i]
                  << " + " << arr[j]
                  << " = " << (arr[i] + arr[j]) << '\n';
    }
}

/*
 * Parenthesize the entire ternary expression when used inside a compound expression (refer to the std::cout example below)
 * Consider adding parentheses around the condition if it contains operators (refer to the int z example below).
 */
void ternery_operator() {
    int x { 1 };
    int y { 2 };
    
    // Equivalent to ((10 - x) > y) ? x : y
    int z = 10 - x > y ? x : y;

    // Evaluates as (std::cout << false) ? "negative" : "non-negative"
    // The output is "0", not the string
    std::cout << (x < 0) ? "negative" : "non-negative";
    // Better practice
    std::cout << ((x < 0) ? "negative" : "non-negative") << '\n';
    
    
    // Type conversions
    std::cout << (true ? 1 : 2) << '\n';        // Okay: both operands have matching type int.
    std::cout << (false ? 1 : 2.2) << '\n';     // Okay: int value 1 converted to double.
    std::cout << (true ? -1 : 2u) << '\n';      // -1 converted to unsigned int, result out of range!
    // std::cout << ((x != 5) ? x : "x is 5");  // Compiler error!
}

/* Floating point comparisons can be unreliable due to rounding errors.
 * Values that should be equal may differ slightly, causing unexpected results with ==, !=, <, or >.
 * Use with care, especially when values are nearly equal.
 */
void floating_point_comparisions() {
    constexpr double d1{ 100.0 - 99.99 }; // approx. 0.01
    constexpr double d2{ 10.0 - 9.99 };   // also approx. 0.01

    // Prints d1 > d2
    if (d1 == d2)
        std::cout << "d1 == d2" << '\n';
    else if (d1 > d2)
        std::cout << "d1 > d2" << '\n';
    else if (d1 < d2)
        std::cout << "d1 < d2" << '\n';
    
    // Evaluates to false!
    bool b = (0.3 == 0.2 + 0.1);
    
    // It's safe to compare floating point literals with same-type variables initialized from the same literal,
    // within their precision limits (float: 6 digits, double: 15).
    constexpr double gravity { 9.8 };
    // Evaluates to true.
    bool b2 = gravity == 9.8;
}

/*
 * Absolute epsilon-based comparison
 * Less precise for large/small numbers as fixed epsilon may be too loose or too strict
 */
bool approximatelyEqualAbs(double a, double b, double absEps) {
    return std::abs(a - b) <= absEps;
}

/*
 * Knuth's relative epsilon method (scales with magnitude).
 * Can fail near zero.
 */
bool approximatelyEqualRel(double a, double b, double relEps) {
    return std::abs(a - b) <= std::max(std::abs(a), std::abs(b)) * relEps;
}

// Combined approach for robustness (good near zero).
bool approximatelyEqualAbsRel(double a, double b, double absEps, double relEps) {
    if (std::abs(a - b) <= absEps)
        return true;
    return approximatelyEqualRel(a, b, relEps);
}

void logical_operators() {
    
}
