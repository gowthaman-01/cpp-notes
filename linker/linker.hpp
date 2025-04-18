#pragma once

/*
 * This function is called in both linker.cpp and main.cpp.
 *
 * The 'inline' keyword would replace the call with the function body instead.
 * Without the inline keyword, the linker will fail with a duplicate symbol error.
 *
 * Another alternative is to use the static keyword.
 * Marking a function as static makes its linking internal, creating separate versions in linker.cpp and main.cpp.
 *
 * However, the best practice is to have a declaration in this header file, and define the function in linker.cpp
 */
inline void linkHelper() {
    return;
}
