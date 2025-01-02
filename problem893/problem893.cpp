#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

// Matchstick cost for digits 0..9
static const int DIGIT_COST[10] = {
    6, // 0
    2, // 1
    5, // 2
    5, // 3
    4, // 4
    5, // 5
    6, // 6
    3, // 7
    7, // 8
    6  // 9
};

// Returns the cost of writing integer x in digit form.
int digitCost(int x) {
    if (x == 0) {
        return DIGIT_COST[0];
    }
    int cost = 0;
    while (x > 0) {
        cost += DIGIT_COST[x % 10];
        x /= 10;
    }
    return cost;
}

int main() {
    // For demonstration, we keep N at 1000000 (10^6).
    // But WARNING: Step 3 (addition) is O(N^2) = 10^12 operations
    // and will be extremely slow for N=10^6.
    // This code is correct in principle but not practical at that scale.
    const int N = 1000000;

    // M[n] will hold the minimum matchstick count for n
    std::vector<int> M(N + 1, 0);

    // 1) Initialize with digit cost for each number
    for (int n = 1; n <= N; ++n) {
        M[n] = digitCost(n);
    }

    // 2) Consider multiplication:  M(a*b) <= M(a) + M(b) + 2
    //    We do a sieve-like approach: for each n, update its multiples.
    for (int n = 2; n <= N; ++n) {
        int costN = M[n];  // store M[n] in a local variable for speed
        // iterate through multiples of n
        for (int k = 2; (int64_t)k * n <= N; ++k) {
            int m = k * n;
            int candidate = costN + M[k] + 2;  // +2 for '*'
            if (candidate < M[m]) {
                M[m] = candidate;
            }
        }
    }

    // 3) Consider addition:  M(a + b) <= M(a) + M(b) + 2
    //    Naive double loop: for each n in [2..N], check all a in [1..n-1].
    //    This is O(N^2) = 1e12 operations for N=1e6 (infeasible in practice).
    //    Shown here for completeness only.
    for (int n = 2; n <= N; ++n) {
        int bestSoFar = M[n];
        for (int a = 1; a < n; ++a) {
            // b = n - a
            int b = n - a;
            int candidate = M[a] + M[b] + 2; // +2 for '+'
            if (candidate < bestSoFar) {
                bestSoFar = candidate;
            }
        }
        M[n] = bestSoFar;
    }

    // 4) Sum up M(1) through M(N)
    std::int64_t answer = 0;
    for (int n = 1; n <= N; ++n) {
        answer += M[n];
    }

    // 5) Output result
    std::cout << answer << std::endl;
    return 0;
}

