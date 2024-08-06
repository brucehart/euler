#include <iostream>
#include <cmath>
#include <vector>

// Function to compute the period length of the continued fraction representation of sqrt(n)
int getPeriodLength(int n) {
    // Initial values for m0, d0, and a0
    int m0 = 0;
    int d0 = 1;
    int a0 = static_cast<int>(std::sqrt(n));
    
    // If n is a perfect square, the period is 0
    if (a0 * a0 == n) {
        return 0;
    }

    int period = 0;  // Initialize period length
    int m = m0;      // Initialize m
    int d = d0;      // Initialize d
    int a = a0;      // Initialize a

    // Iterate until the sequence starts repeating
    while (a != 2 * a0) {
        m = d * a - m;
        d = (n - m * m) / d;
        a = (a0 + m) / d;
        period++;
    }
    
    return period;
}

int main() {
    int limit = 10000;         // Limit up to which we need to check
    int countOddPeriods = 0;   // Counter for odd period lengths

    // Iterate over each number from 2 to limit
    for (int n = 2; n <= limit; ++n) {
        int periodLength = getPeriodLength(n);  // Get the period length for the current number
        if (periodLength % 2 == 1) {            // Check if the period length is odd
            countOddPeriods++;
        }
    }

    // Output the count of numbers with odd period lengths
    std::cout << countOddPeriods << std::endl;

    return 0;
}
