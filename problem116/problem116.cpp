#include <iostream>
#include <vector>
#include <string>

// Function to count the number of ways to fill a row of a given length
// with grey squares (1 unit long) and colored tiles (m units long)
long long count_ways(int length, int m) {
    // Initialize a vector to store the number of ways to fill rows of each length
    // ways[n] will store the number of ways to fill a row of length n
    std::vector<long long> ways(length + 1, 0);
    ways[0] = 1; // Base case: there is exactly 1 way to fill a row of length 0 (do nothing)
    
    // Iterate through all lengths from 1 to the given length
    for (int n = 1; n <= length; ++n) {
        // If the leftmost item is a grey square, the rest of the row has length n-1
        ways[n] += ways[n - 1];
        // If the leftmost item is a colored tile of length m (and m <= n),
        // the rest of the row has length n-m
        if (n >= m) {
            ways[n] += ways[n - m];
        }
    }
    // Return the total number of ways to fill the row of the given length,
    // subtracting 1 to exclude the case where the row is filled entirely with grey squares
    return ways[length] - 1;
}

int main() {
    const int LENGTH = 50; // Length of the row to be filled
    long long result = 0; // Initialize the result to accumulate the number of ways
    
    // Iterate through tile lengths from 2 to 4 and compute the number of ways for each
    for (int i = 2; i <= 4; ++i) {
        result += count_ways(LENGTH, i);
    }
    
    // Convert the result to a string and print it
    std::cout << std::to_string(result) << std::endl;
    return 0; // Indicate successful program termination
}
