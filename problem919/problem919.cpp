#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>

// Function to check if a number is a perfect square using integer operations
inline bool isPerfectSquare(long long x, long long& sqrt_x) {
    sqrt_x = static_cast<long long>(std::sqrt(static_cast<double>(x)));
    // Incrementally check to avoid floating point precision issues
    if (sqrt_x * sqrt_x == x) return true;
    sqrt_x += 1;
    return sqrt_x * sqrt_x == x;
}

int main() {
    // Input N
    long long N;
    std::cout << "Enter the value of N: ";
    std::cin >> N;

    // Vector to store valid triplets
    std::vector<std::tuple<long long, long long, long long>> triplets;

    // Iterate over possible a
    for (long long a = 1; a <= N / 3; ++a) { // a <= b <= c and a + b + c <= N implies a <= N/3
        // Iterate over possible b
        // b ranges from a to (N - a)/2 to ensure c >= b and a + b + c <= N
        for (long long b = a; b <= (N - a) / 2; ++b) {
            // Check both equations
            for (int sign = -1; sign <= 1; sign += 2) {
                // Calculate numerator = 2*a^2 + 2*b^2 + sign*a*b
                long long numerator = 2 * a * a + 2 * b * b + sign * a * b;

                // Ensure that the numerator is positive
                if (numerator <= 0) {
                    continue; // c^2 must be positive
                }

                // Ensure that the numerator is divisible by 2
                if (numerator % 2 != 0) {
                    continue; // c^2 would not be integer
                }

                // Compute c^2
                long long c_sq = numerator / 2;

                // Verify that 2*c_sq equals numerator to prevent integer division issues
                if (2 * c_sq != numerator) {
                    continue; // Inexact division, skip
                }

                // Check if c_sq is a perfect square
                long long c;
                if (isPerfectSquare(c_sq, c)) {
                    // Check if c >= b and a + b + c <= N
                    if (c >= b && (a + b + c) <= N) {
                        triplets.emplace_back(a, b, c);
                    }
                }
            }
        }
    }

    // Output the results
    std::cout << "Valid triplets (a, b, c):\n";
    for (const auto& triplet : triplets) {
        std::cout << "(" 
                  << std::get<0>(triplet) << ", " 
                  << std::get<1>(triplet) << ", " 
                  << std::get<2>(triplet) << ")\n";
    }

    std::cout << "Total triplets found: " << triplets.size() << "\n";

    return 0;
}
