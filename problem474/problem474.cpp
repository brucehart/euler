#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// Type Definitions
typedef unsigned long long ull;
typedef long long ll;

// Constants
const int MAX_N = 1'000'000;          // Upper limit for prime generation
const int TARGET_LAST_DIGITS = 65432;  // Target last five digits
const int MOD_DP = 100'000;           // Modulus for DP (10^5)
const ull FINAL_MOD = 10'000'000'000'000'061ULL; // 10^16 + 61

// Function to generate all primes up to n using the Sieve of Eratosthenes
std::vector<int> generatePrimes(int n) {
    std::vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    int sqrt_n = std::sqrt(n);
    for (int p = 2; p <= sqrt_n; ++p) {
        if (is_prime[p]) {
            for (int multiple = p * p; multiple <= n; multiple += p) {
                is_prime[multiple] = false;
            }
        }
    }
    std::vector<int> primes;
    for (int p = 2; p <= n; ++p) {
        if (is_prime[p]) primes.push_back(p);
    }
    return primes;
}

// Function to compute the exponent of prime p in n! using Legendre's formula
ll computeExponentInFactorial(int n, int p) {
    ll exponent = 0;
    ll power = p;
    while (power <= n) {
        exponent += n / power;
        if (power > n / p) break; // Prevent overflow
        power *= p;
    }
    return exponent;
}

int main() {
    // Step 1: Generate all primes up to MAX_N
    std::vector<int> primes = generatePrimes(MAX_N);

    // Step 2: Calculate exponents of each prime in 10^6!
    struct PrimeExponent {
        int prime;
        ll exponent;
    };
    std::vector<PrimeExponent> primeExponents;
    primeExponents.reserve(primes.size());
    for (int p : primes) {
        if (p == 5) continue; // Exclude 5
        ll exp = computeExponentInFactorial(MAX_N, p);
        primeExponents.push_back(PrimeExponent{p, exp});
    }

    // Step 3: Initialize DP array
    std::vector<ull> dpCurrent(MOD_DP, 0);
    std::vector<ull> dpNext(MOD_DP, 0);

    // The product must be divisible by 8, so start with residue 8
    dpCurrent[8] = 1;

    // Step 4: Dynamic Programming to count valid subsets
    for (const auto& pe : primeExponents) {
        int prime = pe.prime;
        ll maxExponent = pe.exponent;

        // Reset dpNext
        std::fill(dpNext.begin(), dpNext.end(), 0);

        // Iterate through all possible current residues (multiples of 8)
        for (int residue = 8; residue < MOD_DP; residue += 8) {
            if (dpCurrent[residue] == 0) continue;

            // Iterate through all possible exponents of the current prime (0 to maxExponent)
            ll currentCount = dpCurrent[residue];
            ll primePower = 1; // p^0

            for (ll exp = 0; exp <= maxExponent; ++exp) {
                int newResidue = (residue * primePower) % MOD_DP;
                dpNext[newResidue] = (dpNext[newResidue] + currentCount) % FINAL_MOD;

                // Prepare for next exponent
                primePower = (primePower * prime) % MOD_DP;
            }
        }

        // Update dpCurrent with dpNext
        dpCurrent.swap(dpNext);
    }

    // Step 5: Extract the final count
    ull finalCount = dpCurrent[TARGET_LAST_DIGITS];

    // Step 6: Output the result modulo FINAL_MOD
    std::cout << finalCount % FINAL_MOD << std::endl;

    return 0;
}
