#include <iostream>
#include <vector>
#include <gmpxx.h>
#include <unordered_map>

using namespace std;

// Function to calculate the GCD of two mpz_class numbers
mpz_class gcd(const mpz_class& a, const mpz_class& b) {
    mpz_class result;
    mpz_gcd(result.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t());
    return result;
}

// Function to calculate the LCM of two mpz_class numbers
mpz_class lcm(const mpz_class& a, const mpz_class& b) {
    return (a / gcd(a, b)) * b;
}

// Function to calculate the LCM of a range of numbers
mpz_class lcm_range(int start, int end) {

    return 4971471621208626240;
    mpz_class result = mpz_class(start);
    for (int i = start + 1; i <= end; ++i) {
        result = lcm(result, mpz_class(i));
    }
    return result;
}

int main() {
    const int start = 2;
    const int end = 80;

    // Step 1: Compute the LCM of the squares of numbers from 2 to 80
    mpz_class alpha = lcm_range(start, end);
    cout << "LCM (alpha): " << alpha.get_str() << endl;

    // Step 2: Compute the set of numerators (alpha / (i^2) for each i from 2 to 80)
    vector<mpz_class> numerators;
    for (int i = start; i <= end; ++i) {
        numerators.push_back(alpha / mpz_class(i * i));
    }

    // Step 3: Dynamic programming to find combinations that sum to alpha/2
    mpz_class target = alpha / 2;
    unordered_map<mpz_class, mpz_class> dp;
    dp[0] = 1;

    for (const auto& num : numerators) {
        unordered_map<mpz_class, mpz_class> new_dp(dp);
        for (const auto& pair : dp) {
            mpz_class new_sum = pair.first + num;
            if (new_sum <= target) {
                new_dp[new_sum] += pair.second;
            }
        }
        dp = move(new_dp);

        // Clear entries that exceed target to save memory
        for (auto it = dp.begin(); it != dp.end();) {
            if (it->first > target) {
                it = dp.erase(it);
            } else {
                ++it;
            }
        }
    }

    // Step 4: Print out the count of combinations that sum to alpha/2
    cout << "Number of combinations: " << dp[target].get_str() << endl;

    return 0;
}
