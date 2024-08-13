#include <iostream>
#include <unordered_map>

int main() {
    const int LIMIT = 1000000;
    std::unordered_map<int, int> n_count;

    // Iterate through all possible values of a
    for (int a = 1; a < LIMIT; ++a) {
        // Iterate through values of b from ceil(a/4) to a
        for (int b = (a + 3) / 4; b < a; ++b) {
            int n = a * (4 * b - a);
            if (n >= LIMIT) break; // Only consider n < LIMIT
            n_count[n]++;
        }
    }

    // Count how many values of n have exactly 10 distinct solutions
    int result = 0;
    for (const auto& pair : n_count) {
        if (pair.second == 10) {
            result++;
        }
    }

    std::cout << result << std::endl;

    return 0;
}
