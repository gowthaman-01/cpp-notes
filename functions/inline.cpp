/*
 * Function calls introduce overhead. Every call requires:
 * - Saving the current state (program counter, CPU registers)
 * - Passing parameters
 * - Jumping to the function, and returning the result.

 * For large or complex functions, this overhead is negligible.
 * For small, frequently called functions the overhead can outweigh the actual execution time, leading to performance loss.
 *
 * The C++ compiler carries out inline expansion, replacing the function call with the actual function body,
 * removing overhead and enabling further optimizations (like constant folding).
 * Downside:
 * - Can increase executable size (called code bloat).
 * - May affect performance (e.g., cache misses due to large sizes).
 *
 * Best used for short functions and those called frequently (like in loops).
 * A function can’t be inlined if its definition is in another translation unit.
 * Modern optimizing compilers make the decision about when functions should be expanded inline.
 *
 * Use the inline keyword only when defining a function or constant in a header file.
 * Don’t use inline just to force expansion — let the compiler optimize.
 *
 * Downsides of inline functions in headers:
 * - An inline function in a header file gets compiled once per translation unit.
 * - If 6 files include the header, the function is compiled 6 times.
 * - If an inline function in a header file is modified, all files that include that header must be recompiled.
 * - In large projects, this can lead to a massive increase in build time.
 *
 * In contrast, a function defined in a .cpp file is compiled only once, regardless of how many files include its declaration.
 * A change in a .cpp file's function only triggers recompilation of that file alone.
 */
