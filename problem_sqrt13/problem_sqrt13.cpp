#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

// Alias for convenience
using boost::multiprecision::cpp_int;

int main() {
    // Initialize variables
    const int n = 13;          // The number to find the square root of
    const int d = 1000;        // Number of decimal digits to compute

    // Compute the integer part of sqrt(n)
    cpp_int integer_part = 3;  // Since floor(sqrt(13)) = 3

    // Initial remainder: n - (integer_part)^2
    cpp_int remainder = n - integer_part * integer_part; // 13 - 9 = 4

    // Current result starts with the integer part
    cpp_int current_result = integer_part;

    // Variable to store the sum of the digits
    long long sum = 0;

    // Loop to compute each decimal digit
    for (int i = 0; i < d; ++i) {
        // Step 1: Multiply the remainder by 100 to shift two decimal places
        remainder *= 100;

        // Step 2: Calculate the base for the trial digit
        cpp_int base = 20 * current_result;

        // Step 3: Find the largest digit x such that (base + x) * x <= remainder
        int x = 0;
        for (int candidate = 0; candidate <= 9; ++candidate) {
            cpp_int trial = (base + candidate) * candidate;
            if (trial <= remainder) {
                x = candidate;
            } else {
                break; // No need to check higher candidates
            }
        }

        // Step 4: Add the found digit to the sum
        sum += x;

        // Step 5: Update the remainder by subtracting (base + x) * x
        remainder -= (base + x) * x;

        // Step 6: Append the digit x to the current result
        current_result = current_result * 10 + x;
    }

    // Output the sum of the first 1000 decimal digits of sqrt(13)
    std::cout << sum << std::endl;

    return 0;
}

