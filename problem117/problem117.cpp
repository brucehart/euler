#include <iostream>
#include <vector>
#include <numeric>

int main() {
    // Determine the number of ways to fill a row of length n with:
    // - Grey squares of 1 unit length
    // - Red tiles of 2 units length
    // - Green tiles of 3 units length
    // - Blue tiles of 4 units length

    // The length of the row
    const int LENGTH = 50;

    // Vector to store the number of ways to fill rows of length 0 to LENGTH
    std::vector<long long> ways(LENGTH + 1, 0);
    ways[0] = 1;  // There is one way to fill a row of length 0 (using no tiles)

    // Fill the vector using dynamic programming
    for (int n = 1; n <= LENGTH; n++) {
        // Start by adding the number of ways to fill a row of length n-1 (grey square)
        ways[n] = ways[n - 1];
        
        // If n is at least 2, add the number of ways to fill a row of length n-2 (red tile)
        if (n >= 2) ways[n] += ways[n - 2];
        
        // If n is at least 3, add the number of ways to fill a row of length n-3 (green tile)
        if (n >= 3) ways[n] += ways[n - 3];
        
        // If n is at least 4, add the number of ways to fill a row of length n-4 (blue tile)
        if (n >= 4) ways[n] += ways[n - 4];
    }

    // Print the number of ways to fill a row of length LENGTH
    std::cout << ways[LENGTH] << std::endl;

    return 0;
}
