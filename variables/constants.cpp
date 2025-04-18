/*
 * Compile-time evaluation allows us to write programs that are both more performant and of higher quality.
 * The following C++ features are the most foundational to compile-time programming:
 * - Constexpr variables
 * - Constexpr functions
 * - Templates
 * - static_assert
 *
 * Constant expression is an expression where each part of the expression must be evaluatable at compile-time.
 * A few common cases where a compile-time evaluatable expression is required:
 * - The initializer of a constexpr variable.
 * - A non-type template argument.
 * - The defined length of a std::array or a C-style array.
 *
 * const means that the value of an object cannot be changed after initialization. The value of the initializer may be known at compile-time or runtime. The const object can be evaluated at runtime.
 * constexpr means that the object can be used in a constant expression. The value of the initializer must be known at compile-time. The constexpr object can be evaluated at runtime or compile-time.
 * Constexpr variables are implicitly const.
 * Const variables are not implicitly constexpr (except for const integral variables with a constant expression initializer).
 * Unlike const, constexpr is not part of an object’s type.
 * A variable defined as constexpr int actually has type const int.
 *
 * Any constant variable whose initializer is a constant expression should be declared as constexpr.
 * Any constant variable whose initializer is not a constant expression should be declared as const.
 * For constant objects of std::string, std::vector, and other types that use dynamic memory allocation, either use const instead of constexpr, or pick a different type that is constexpr compatible (e.g. std::string_view or std::array).
 *
 * const function parameters are treated as runtime constants (even when the supplied argument is a compile-time constant).
 * Function parameters cannot be declared as constexpr, since their initialization value isn’t determined until runtime.
 *
 * const/constexpr variables usually a better choice than #defined symbolic constants as #define constants do not show up in the debugger and are more likely to have naming conflicts.
*/

#include <string_view>

//  1. Literals are constant expressions
constexpr int a = 5;
constexpr double b = 3.14;
constexpr double c = 5 + 3.14;                              // Even though operands have different types

// 2. Non-const variables are NOT constant expressions
int x = 5;                                                  // Not a constant expression (can be changed later)
const int x2 = x;                                           // x2 is NOT a constant expression

const int y = 10;
const int y2 = y;                                           // y2 is a constant expression
const int y3 = y + 10;                                      // y3 is a constant expression

// 3. constexpr variables are ALWAYS constant expressions
constexpr int z = 20;                                       // Read-only and a constant expression
// z = 25;                                                  // Error: z is read-only

// 4. Most operators with constant expression operands
constexpr int sum = a + z;                                  // Sum is a constant expression
constexpr int product = a * z;                              // Product is a constant expression

// 5. Operators with non-constant operands
int m = 3, n = 4;
// constexpr int invalidSum = m + n;                        // Error: m and n are not constant expressions
    
// 6. Constexpr function with constant arguments
constexpr int square(int x) { return x * x; }
constexpr int squaredValue = square(5);                     // Constant expression

// 7. Constexpr function with non-constant arguments
int nonConstArg = 5;
// constexpr int invalidResult = square(nonConstArg);       // Error: nonConstArg is not a constant expression

// 8. Non-type template parameters (must be constant expressions)
template <int Size>
struct Array {
    int arr[Size];                                          // Array size must be a constant expression
};

Array<5> validArray;                                        // 5 is a constant expression

// Non-constant expression as template parameter
// Array<m> invalidArray;                                   // Error: m is not a constant expression

// 9. Enumerators are constant expressions
enum Colors { RED = 1, BLUE = 2 };
constexpr int favoriteColor = RED;                          // Constant expression

// 10. Const non-integral variables are NOT constant expressions
const double pi = 3.14159;                                  // Not a constant expression
// constexpr double pi = 3.14159;                           // Fix: make it constexpr

// 11. Constexpr lambda expressions
constexpr auto add = [](int x, int y) { return x + y; };
constexpr int lambdaResult = add(2, 3);                     // Constant expression

// 12. Certain operators cannot be used in constant expressions
// constexpr int* p = new int(5);                           // Error: `new` is not allowed in constant expressions
// constexpr int invalidType = typeid(int).hash_code();     // Error: typeid is not allowed`

// 13. The return value of a non-constexpr function is a runtime expression
// even when the return expression is a constant expression
int five() {
    return 5;
}

// 14. Unlike std::string, std::string_view has full support for constexpr:
constexpr std::string_view s{ "Hello, world!" };            // s is a string symbolic constant
// std::cout << s << '\n';                                  // s will be replaced with "Hello, world!" at compile-time



