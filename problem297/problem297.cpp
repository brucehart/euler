#include <iostream>
#include <vector>

// Define the maximum value for Fibonacci numbers.
static const unsigned long long MAX_N = 100000000000000000ULL;

// Vectors to store Fibonacci numbers and their cumulative sums.
std::vector<unsigned long long> fibs;
std::vector<unsigned long long> fibs_sum;

// Recursive function to compute the "z-sum" for a given number `n`.
unsigned long long z_sum(unsigned long long n) {
    // Find the largest Fibonacci number less than or equal to `n`.
    int idx = 0;
    while (fibs[idx + 1] <= n) 
        idx++;

    // Calculate the difference between `n` and the selected Fibonacci number.
    unsigned long long diff = n - fibs[idx];

    // Base case: If `diff` is zero, return the cumulative sum up to the current Fibonacci number.
    if (diff == 0)
        return fibs_sum[idx];

    // Recursive step: Add the cumulative sum up to the current Fibonacci number, 
    // the difference, and the z-sum of the difference.
    return fibs_sum[idx] + diff + z_sum(diff);
}

int main() {
    // Initialize the first two Fibonacci numbers and their cumulative sums.
    fibs.push_back(1);
    fibs.push_back(2);
    fibs_sum.push_back(1);  // Sum of Fibonacci sequence up to 1.
    fibs_sum.push_back(2);  // Sum of Fibonacci sequence up to 2.

    // Generate Fibonacci numbers and their cumulative sums until they exceed MAX_N.
    while (fibs.back() < MAX_N) {
        // Add the next Fibonacci number.
        fibs.push_back(fibs[fibs.size() - 1] + fibs[fibs.size() - 2]);

        // Calculate the cumulative sum including the new Fibonacci number.
         fibs_sum.push_back(fibs_sum[fibs_sum.size() - 1] + fibs_sum[fibs_sum.size() - 2] + 
                            fibs[fibs_sum.size() - 2] - 1); 
    }

    // Compute and output the z-sum for the maximum allowable value (MAX_N - 1).
    std::cout << z_sum(MAX_N - 1) << std::endl;

    return 0;
}
