#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

// Compute the digital root of a positive integer n using a standard formula:
//   digital_root(n) = 1 + (n - 1) % 9, for n > 0; and digital_root(0) = 0.
//
// This works because repeatedly summing the digits of n (in base 10) 
// results in the remainder of n modulo 9, except that multiples of 9 
// have a digital root of 9 (rather than 0).
inline int digital_root(int n) {
    return (n == 0) ? 0 : 1 + (n - 1) % 9;
}

int main() {
    // Upper limit (exclusive bound) for which we sum mdrs(n).
    const int LIMIT = 1'000'000;

    // dp[n] will hold the maximum DRS (mdrs) for n.
    // We'll store values from 0..LIMIT inclusively; dp[0] is unused.
    std::vector<int> dp(LIMIT + 1, 0);

    // Precompute the base digital root for each number.
    // This covers the case n = prime (or no non-trivial factorization):
    //   mdrs(n) starts as the digital root of n itself.
    for (int n = 1; n <= LIMIT; ++n) {
        dp[n] = digital_root(n);
    }

    // Dynamic programming / sieve approach to update dp[n] to the max possible value
    // from any factor pair (i, j) such that i * j = n (with i, j >= 2).
    //
    // We loop i from 2..LIMIT, then mark all multiples of i (i.e., i * j).
    // For each multiple k of i, set dp[k] to be the max of its current value
    // and dp[i] + dp[k/i].  This corresponds to factoring k into (i) and (k/i).
    //
    // Note: i*j can overshoot LIMIT, so we check bounds carefully.
    for (int i = 2; i <= LIMIT; ++i) {
        for (int k = 2 * i; k <= LIMIT; k += i) {
            int j = k / i;
            // Update dp[k] if using the factor pair (i, j) produces a larger DRS.
            dp[k] = std::max(dp[k], dp[i] + dp[j]);
        }
    }

    // Finally, sum up dp[n] for n = 2..(LIMIT - 1).
    // (The problem states "1 < n < 1,000,000," so n goes up to 999,999.)
    std::int64_t answer = 0;
    for (int n = 2; n < LIMIT; ++n) {
        answer += dp[n];
    }

    // Output the result.
    std::cout << answer << std::endl;

    return 0;
}

