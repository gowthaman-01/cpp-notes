/*
 * A constexpr function must evaluate at compile-time when the constant expression it is part of must evaluate at compile time (e.g. in the initializer of a constexpr variable).
 * Otherwise, a constexpr function may be evaluated at either compile-time (if eligible) or runtime.
 * To be eligible for compile-time execution, all arguments must be constant expressions.
 */
