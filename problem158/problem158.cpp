#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

// Function to calculate power b^p
int pow(int b, int p) {
    int result = b;
    for (int i = 2; i <= p; i++) {
        result *= b;
    }
    return result;
}

// Function to compute the binomial coefficient C(n, k) using dynamic programming
std::vector<std::vector<long long>> compute_binomial(int m) {
    // Initialize a 2D vector to store the binomial coefficients
    std::vector<std::vector<long long>> dp(m + 1, std::vector<long long>(m + 1, 0));
    
    // Fill the dynamic programming table
    for (int i = 0; i <= m; ++i) {
        dp[i][0] = dp[i][i] = 1; // Base cases: C(i, 0) = C(i, i) = 1
        for (int j = 1; j < i; ++j) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]; // Recurrence relation
        }
    }
    return dp;
}

// Main function to execute the program
int main() {
    int m = 26; // The maximum value for n (number of letters)
    auto binomial_coeffs = compute_binomial(m); // Precompute binomial coefficients

    long long p = 0; // To store the maximum value of pnew
    long long priorconfigs = 1; // Initial value of prior configurations

    // Loop through values of n from 3 to 26
    for (int n = 3; n <= 26; n++) {
        // Calculate the binomial coefficient C(26, n)
        long long binom = binomial_coeffs[26][n];
        // Calculate the number of configurations for this n
        long long configs = priorconfigs + (pow(2, n - 1) - 1);
        // Calculate the new p value for this n
        long long pnew = binom * configs;

        // Update the maximum p value
        p = std::max(p, pnew);
        // Update prior configurations for the next iteration
        priorconfigs = configs;
    }

    // Output the result
    std::cout << std::to_string(p) << std::endl;
    return 0;
}
