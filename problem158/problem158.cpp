#include <iostream>
#include <vector>

int main() {
    const int N = 26;
    std::vector<std::vector<std::vector<int>>> dp(N + 1, std::vector<std::vector<int>>(N, std::vector<int>(2, 0)));

    // Initialize base case for strings of length 1
    for (int j = 0; j < N; ++j) {
        dp[1][j][0] = 1;
    }

    // Fill the DP table
    for (int len = 2; len <= N; ++len) {
        for (int j = 0; j < N; ++j) {
            for (int x = 0; x < j; ++x) {
                dp[len][j][1] += dp[len - 1][x][0];  // Add one increasing pair
            }
            for (int x = j + 1; x < N; ++x) {
                dp[len][j][1] += dp[len - 1][x][1];  // Continue existing increasing pairs
            }
        }
    }

    // Find the maximum p(n)
    int max_p = 0;
    for (int len = 2; len <= N; ++len) {
        int current_p = 0;
        for (int j = 0; j < N; ++j) {
            current_p += dp[len][j][1];
        }
        max_p = std::max(max_p, current_p);
        std::cout << "p(" << len << ") = " << current_p << std::endl;
    }

    std::cout << "Maximum value of p(n): " << max_p << std::endl;
    return 0;
}
