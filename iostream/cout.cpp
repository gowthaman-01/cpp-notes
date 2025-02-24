#include <iostream>
#include <chrono>
#include <thread>

/* Use std::cerr for debugging because it's unbuffered, ensuring immediate output.
 * std::cout may delay output and mislead debugging.
 *
 * std::endl is inefficient because it does two things:
 * 1. Outputs a newline (\n).
 * 2. Flushes the output buffer (which is slow).
 *
 * Frequent use of std::endl causes unnecessary flushes, slowing down performance.
 * C++ output system auto-flushes periodically, so explicit flushing is usually not needed.
 * Use \n instead of std::endl for better performance since:
 */
void endl_vs_slash_n() {
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 100000; ++i)
        std::cout << "Line " << i << '\n';

    auto mid = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 100000; ++i)
        std::cout << "Line " << i << std::endl;

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Using '\\n': "
              << std::chrono::duration_cast<std::chrono::milliseconds>(mid - start).count()
              << " ms\n";

    std::cout << "Using 'std::endl': "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - mid).count()
              << " ms\n";
}

void cout_general() {
    std::cout << "Hello "
        "world!"; // Prints "Hello world!
    
    std::cout
        << "Hello world"; // Note the << on the newline
    
    // Evaluates as (std::cout << "Hello ") << "world!".
    // This first prints "Hello " to the console.
    // This operation returns std::cout, which can then be used to print "world!" to the console as well.
    std::cout << "Hello " << "world!";
}
