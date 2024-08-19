#include <iostream>
#include <vector>
#include <iomanip>

// Function to compute (base^exp) % mod using modular exponentiation
long long mod_exp(int base, int exp, long long mod) {
    long long result = 1;
    long long power = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * power) % mod;
        }
        power = (power * power) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    const int max_len = 20;
    const int base = 10;
    const long long mod = 1000000000LL;
    long long max_sum = static_cast<long long>((base - 1) * (base - 1) * max_len);

    // dp_sum[n][s] stores the sum of all n-digit numbers whose digit squares sum to s, modulo mod
    std::vector<std::vector<long long>> dp_sum(max_len + 1, std::vector<long long>(max_sum + 1, 0));
    
    // dp_count[n][s] stores the count of all n-digit numbers whose digit squares sum to s, modulo mod
    std::vector<std::vector<long long>> dp_count(max_len + 1, std::vector<long long>(max_sum + 1, 0));

    // Initialize base case
    dp_count[0][0] = 1;

    // Fill dp_sum and dp_count using dynamic programming
    for (int len = 1; len <= max_len; len++) {
        // Compute (base^(len-1)) % mod for this length
        long long base_pow_mod = mod_exp(base, len - 1, mod);
        
        for (int digit = 0; digit < base; digit++) {
            for (long long sum = 0; sum <= max_sum; sum++) {
                long long new_sum = sum + static_cast<long long>(digit * digit);
                if (new_sum > max_sum) break;

                // Update dp_sum and dp_count for this length and new_sum
                dp_sum[len][new_sum] = (dp_sum[len][new_sum] + dp_sum[len - 1][sum] + base_pow_mod * digit * dp_count[len - 1][sum]) % mod;
                dp_count[len][new_sum] = (dp_count[len][new_sum] + dp_count[len - 1][sum]) % mod;
            }
        }
    }

    // Calculate the final sum of all numbers where the digit square sum is a perfect square
    long long result = 0;
    for (long long sqr = 1; sqr * sqr <= max_sum; sqr++) {
        result = (result + dp_sum[max_len][sqr * sqr]) % mod;
    }

    // Ensure result is non-negative and print it with leading zeros
    if (result < 0) {
        result += mod;
    }

    std::cout << std::setw(9) << std::setfill('0') << result << std::endl;
    return 0;
}
