#include <iostream>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include <cstring>

using boost::multiprecision::cpp_int;

static const cpp_int MOD = 14348907; // 3^15

// Function to compute power of 10 modulo MOD
cpp_int power10(int exponent) {
    cpp_int result = 1;
    cpp_int base = 10;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exponent /= 2;
    }
    return result;
}

// Function to compute counts and sums of numbers with given length and digit sum
void compute_counts_and_sums(int length, std::vector<std::vector<cpp_int>>& counts, std::vector<std::vector<cpp_int>>& sums, bool is_first_half, bool is_middle_digit = false) {
    int max_sum = 9 * length;
    counts.assign(length + 1, std::vector<cpp_int>(max_sum + 1, 0));
    sums.assign(length + 1, std::vector<cpp_int>(max_sum + 1, 0));

    // Initialize base case
    counts[0][0] = 1;
    sums[0][0] = 0;

    for (int pos = 1; pos <= length; ++pos) {
        int digit_start = 0;
        int digit_end = 9;

        // First digit cannot be zero if it's the first half
        if (pos == 1 && is_first_half) {
            digit_start = 1;
        }

        for (int sum = 0; sum <= max_sum; ++sum) {
            for (int d = digit_start; d <= digit_end; ++d) {
                if (sum - d >= 0) {
                    counts[pos][sum] = (counts[pos][sum] + counts[pos - 1][sum - d]) % MOD;
                    sums[pos][sum] = (sums[pos][sum] + (sums[pos - 1][sum - d] * 10 + d * counts[pos - 1][sum - d])) % MOD;
                }
            }
        }
    }

    // If we're considering the middle digit separately (for odd k), adjust the counts and sums
    if (is_middle_digit && length == 0) {
        counts[1].assign(10, 0);
        sums[1].assign(10, 0);
        for (int d = 0; d <= 9; ++d) {
            if (!(d == 0 && is_first_half)) { // Avoid leading zero in first half
                counts[1][d] = 1;
                sums[1][d] = d;
            }
        }
    }
}

// Main function to compute T(k)
cpp_int compute_T(int k) {
    if (k <= 0) return 0;

    cpp_int total_sum = 0;
    int l = (k + 1) / 2; // Length of the half (including middle digit for odd k)
    int max_sum = 9 * l;

    // Initialize counts and sums for first and second halves
    std::vector<std::vector<cpp_int>> counts_first, sums_first;
    std::vector<std::vector<cpp_int>> counts_last, sums_last;

    // Compute counts and sums for the first half
    compute_counts_and_sums(l, counts_first, sums_first, true, false);

    // Compute counts and sums for the second half
    compute_counts_and_sums(l, counts_last, sums_last, false, false);

    cpp_int power_shift = power10(k - l);

    // For odd k, we need to consider the middle digit separately
    if (k % 2 == 0) {
        // Even k
        for (int s = 0; s <= 9 * l; ++s) {
            cpp_int count = (counts_first[l][s] * counts_last[l][s]) % MOD;
            cpp_int sum_first = sums_first[l][s];
            cpp_int sum_last = sums_last[l][s];

            cpp_int total = (sum_first * counts_last[l][s]) % MOD;
            total = (total * power_shift) % MOD;
            total = (total + (counts_first[l][s] * sum_last) % MOD) % MOD;

            total_sum = (total_sum + total) % MOD;
        }
    } else {
        // Odd k
        // Need to consider middle digit separately
        int middle_digit_start = 0;
        int middle_digit_end = 9;

        // For the first half, we exclude the middle digit
        compute_counts_and_sums(l - 1, counts_first, sums_first, true, false);
        // For the last half, we exclude the middle digit
        compute_counts_and_sums(l - 1, counts_last, sums_last, false, false);

        for (int d = middle_digit_start; d <= middle_digit_end; ++d) {
            // Avoid leading zero in the overall number
            if (k == 1 && d == 0) continue;

            cpp_int middle_digit = d * power10(k / 2) % MOD;

            for (int s = 0; s <= 9 * (l - 1); ++s) {
                cpp_int c_first = counts_first[l - 1][s];
                cpp_int s_first = sums_first[l - 1][s];

                // Avoid leading zero in the first half
                if (k > 1 && c_first == 0) continue;

                cpp_int c_last = counts_last[l - 1][s];
                cpp_int s_last = sums_last[l - 1][s];

                cpp_int count = (c_first * c_last) % MOD;

                cpp_int total = (s_first * c_last) % MOD;
                total = (total * power_shift * 10) % MOD;
                total = (total + (c_first * s_last) % MOD) % MOD;
                total = (total + (middle_digit * count) % MOD) % MOD;

                total_sum = (total_sum + total) % MOD;
            }
        }
    }

    return total_sum;
}

int main() {
    cpp_int sum_T = 0;

    for (int k = 1; k <= 47; ++k) {
        cpp_int T_k = compute_T(k);
        sum_T = (sum_T + T_k) % MOD;
    }

    std::cout << sum_T << std::endl;
    return 0;
}

