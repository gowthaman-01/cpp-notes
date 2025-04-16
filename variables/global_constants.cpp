/*
 * Constants like pi, gravity, frictionCoefficient, etc. are often reused across multiple files.
 * Define them once → use everywhere → easier maintenance, no duplication.
 */

// =======================================================
// Method 1: Internal Constants (Preferred prior to C++17
// =======================================================
// These are defined in a header file (constants.h)
// Each .cpp that includes the header gets its own independent copy
//
// Disadvantages:
// - Duplicated in every translation unit (TU) that includes the header.
// - Changing a constant requires recompilation of every dependent file.
namespace InternalConstants {
    constexpr double pi { 3.14159 };
    constexpr double avogadro { 6.0221413e23 };
    constexpr double gravity { 9.2 };
}

// =======================================================
// Method 2: External Constants
// =======================================================
// Declared in constants.h and defined in constants.cpp
// Must be used as runtime constants, not in constexpr expressions outside constants.cpp
//
// Advantages:
// - Only one copy exists in the entire program.
// - Changing a constant only requires recompiling one file.
// Disadvantages:
// - Not usable in constexpr expressions outside the defining file.
// - Requires keeping declaration and definition in sync.
namespace ExternalConstants {
    extern const double pi;
    extern const double avogadro;
    extern const double gravity;
}

// Definitions (would normally go in a .cpp file)
namespace ExternalConstants {
    constexpr double pi { 3.14159 };
    constexpr double avogadro { 6.0221413e23 };
    constexpr double gravity { 9.2 };
}

// =======================================================
// Method 3: Inline Constants (Preferred after C++17+)
// =======================================================
// Best method: defined once in a header, shared across all translation units
//
// Advantages:
// - Single definition shared across all files.
// - Usable in constexpr expressions everywhere.
// Disadvantages:
// - Requires C++17 or newer.
// - Changing a constant still triggers recompilation of all including files.
namespace InlineConstants {
    inline constexpr double pi { 3.14159 };
    inline constexpr double avogadro { 6.0221413e23 };
    inline constexpr double gravity { 9.2 };
}

void global_constants() {
    double c1 = 2 * 5 * InternalConstants::pi;
    double c2 = 2 * 5 * ExternalConstants::pi;
    double c3 = 2 * 5 * InlineConstants::pi;
}
