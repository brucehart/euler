#include <iostream>
#include <unordered_set>
#include <cmath>

// Function to calculate the number of "stealthy" numbers <= n
int64_t solve(int64_t n) {
    // Calculate the fourth root of n to limit the search space
    int64_t limit = static_cast<int64_t>(std::pow(n, 1.0 / 4));

    // A set to keep track of already encountered stealthy numbers
    std::unordered_set<int64_t> seen;

    // Variable to store the count of unique stealthy numbers
    int64_t count = 0;

    // Loop over possible values of x
    for (int64_t x = 1; x <= limit; ++x) {
        int64_t y = x;

        // Loop to find all valid y values for a given x
        while (true) {
            // Calculate the stealthy number v = x*(x+1)*y*(y+1)
            int64_t v = x * (x + 1) * y * (y + 1);

            // If v exceeds n, no need to continue further with this y
            if (v > n) break;

            // If v has not been seen before, add it to the set and increment the count
            if (seen.find(v) == seen.end()) {
                ++count;
                seen.insert(v);
            }

            // Increment y for the next iteration
            ++y;
        }
    }

    // Return the total count of unique stealthy numbers
    return count;
}

int main() {
    // Call the solve function with n = 10^14 and print the result
    std::cout << solve(100000000000000) << std::endl;
    return 0;
}
