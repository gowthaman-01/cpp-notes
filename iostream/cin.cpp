#include <iostream>

/*
 * Buffered Input with std::cin (C++)
 * ----------------------------------
 * - Input is buffered and processed in FIFO (First In, First Out) order.
 * - std::cin extracts data sequentially, based on type and format.
 *
 * Example 1: Separate Inputs
 * -------------------------
 * User Input: 4 (Enter), then 5 (Enter)
 * Buffer:     [ 4\n ] -> x = 4
 *             [ 5\n ] -> y = 5
 * Output:     You entered 4 and 5
 *
 * Example 2: Single Line Input
 * ----------------------------
 * User Input: 4 5 (Enter)
 * Buffer:     [ 4 5\n ]
 * Extraction: - x = 4 (extraction stops at space)
 *             - y = 5 (remaining buffer is extracted automatically)
 *
 * Buffer Behavior:
 * -----------------
 * - Input is stored as characters (e.g., "4 5\n").
 * - Leading whitespace (spaces, tabs, newlines) is ignored during extraction.
 * - Extraction halts at the first invalid character for the target type.
 *
 * Handling Extraction Errors:
 * ----------------------------
 * If the user types 5a and enter, 5a\n will be added to the buffer.
 * 5 will be extracted, converted to an integer, and assigned to variable x.
 * a\n will be left in the input buffer for the next extraction.
 *
 * If the user types ‘b’ and enter, b\n would be added to the buffer.
 * Because b is not a valid integer, no characters can be extracted, so this is an extraction failure.
 * Variable x would be set to 0, and future extractions will fail until std::cin.clear() is called.
 *
 * If std::cin is not in a good state due to a prior failed extraction, nothing happens here.
 * The value of variable x is not altered.
 *
 * cin Behavior for int (Key Points):
 * ---------------------------
 * 1. Non-integer input             -> x = 0 (fail state).
 * 2. Fractional numbers            -> truncated to integer.
 * 3. Negative integers             -> correctly extracted.
 * 4. Large numbers                 -> capped at INT_MAX (typically 2147483647).
 * 5. Mixed inputs (e.g., 42abc)    -> 42 extracted, 'abc' left in buffer.
 * 6. Leading spaces                -> ignored. '+' before numbers is valid.
 * 7. Letter-start input            -> fails (e.g., 'abc123' -> x = 0).
 */
void cin_demo() {
    std::cout << "Enter two numbers: ";

    int x{};
    std::cin >> x;

    int y{};
    std::cin >> y;

    std::cout << "You entered " << x << " and " << y << '\n';
}

