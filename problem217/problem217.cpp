#include <iostream>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

// Define DPCell structure
struct DPCell {
    cpp_int count;
    cpp_int sum;
};

static const cpp_int MOD = 14348907; // 3^15

// Custom power function for cpp_int
cpp_int power10(int exponent) {
    cpp_int result = 1;
    cpp_int base = 10;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= base;
            result %= MOD; // Apply modulo at each step to keep numbers manageable
        }
        base *= base;
        base %= MOD;
        exponent /= 2;
    }
    return result;
}

// Function to compute the sum of all k-digit numbers with digit sum n
cpp_int compute_sum_of_numbers(int k, int n) {
    // Edge case checks
    if (k <= 0) {
        // No digits, no numbers
        return 0;
    }
    if (n < 1 || n > 9 * k) {
        // Sum is too small or too large to be achieved with k digits
        return 0;
    }

    // Initialize DP table with (k+1) rows and (n+1) columns
    // DP[i][s] = DPCell for i-digit numbers with digit sum s
    std::vector<std::vector<DPCell>> DP(k + 1, std::vector<DPCell>(n + 1, DPCell{0, 0}));

    // Base case: 0-digit number with sum 0
    DP[0][0].count = 1;
    DP[0][0].sum = 0;

    // Fill the DP table
    for (int i = 1; i <= k; ++i) {
        // Determine the range of digits based on the position
        int start_d = (i == 1) ? 1 : 0; // First digit cannot be 0
        int end_d = 9;

        for (int s = 0; s <= n; ++s) {
            for (int d = start_d; d <= end_d; ++d) {
                if (s - d >= 0) {
                    DP[i][s].count += DP[i - 1][s - d].count;
                    DP[i][s].sum += DP[i - 1][s - d].sum * 10 + d * DP[i - 1][s - d].count;
                    DP[i][s].sum %= MOD; // Apply modulo to keep numbers manageable
                }
            }
        }
    }

    return DP[k][n].sum;
}

// Function to compute the count of all k-digit numbers with digit sum n
cpp_int compute_count_of_numbers(int k, int n) {
    // Edge case checks
    if (k <= 0) {
        // No digits, no numbers
        return 0;
    }
    if (n < 1 || n > 9 * k) {
        // Sum is too small or too large to be achieved with k digits
        return 0;
    }

    // Initialize DP table with (k+1) rows and (n+1) columns
    // DP[i][s] = DPCell for i-digit numbers with digit sum s
    std::vector<std::vector<DPCell>> DP(k + 1, std::vector<DPCell>(n + 1, DPCell{0, 0}));

    // Base case: 0-digit number with sum 0
    DP[0][0].count = 1;
    DP[0][0].sum = 0;

    // Fill the DP table
    for (int i = 1; i <= k; ++i) {
        // Determine the range of digits based on the position
        int start_d = (i == 1) ? 1 : 0; // First digit cannot be 0
        int end_d = 9;

        for (int s = 0; s <= n; ++s) {
            for (int d = start_d; d <= end_d; ++d) {
                if (s - d >= 0) {
                    DP[i][s].count += DP[i - 1][s - d].count;
                    // No need to compute sum in this function
                }
            }
        }
    }

    return DP[k][n].count;
}

cpp_int compute_T(int k) {
    if (k <= 0) return 0;
    if (k == 1) return 45;

    cpp_int sum_T = 0;

    for (int n = 1; n <= 9 * k; ++n) {
        cpp_int count = compute_count_of_numbers(k, n);
        cpp_int sum = compute_sum_of_numbers(k, n);

        int shift = (k + 1) / 2;
        cpp_int power_shift = power10(shift);
        cpp_int power_shift_minus = (shift > 0) ? power10(shift - 1) : 0;

        if (k % 2 == 0) {
            // Even k
            cpp_int term1 = (sum * count % MOD) * power_shift % MOD;
            cpp_int term2 = (sum * count) % MOD;
            sum_T += (term1 + term2) % MOD;
        }
        else {
            // Odd k
            cpp_int term1 = (10 * sum % MOD) * count % MOD;
            term1 = (term1 * power_shift) % MOD;

            cpp_int term2 = (45 * count % MOD) * count % MOD;
            term2 = (term2 * power_shift_minus) % MOD;

            cpp_int term3 = (10 * sum % MOD) * count % MOD;

            sum_T += (term1 + term2 + term3) % MOD;
        }

        sum_T %= MOD;
    }

    return sum_T;
}

int main()
{
    cpp_int sum_T = 0;

    for (int k = 1; k <= 47; ++k) {
        std::cout << k << std::endl;
        sum_T += compute_T(k);
        sum_T %= MOD;
    }

    std::cout << sum_T << std::endl;
    return 0;
}
