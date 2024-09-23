#include <iostream>
#include <set>
#include <cmath>
#include <cstdint>

std::set<int64_t> primes;  // A set to store prime numbers as they are generated

// Basic primality test for small numbers
// This function checks whether a number `n` is prime
bool isPrime(int64_t n) {
    if (n <= 1) return false;  // Numbers less than or equal to 1 are not prime
    if (n == 2 || n == 3) return true;  // 2 and 3 are prime
    if (n % 2 == 0 || n % 3 == 0) return false;  // Even numbers and multiples of 3 are not prime

    // For numbers greater than 3, check for divisibility starting from 5
    // and skip numbers that are multiples of 2 or 3 by incrementing in steps of 6
    for (int64_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;  // Divisible by `i` or `i+2` means not prime
    }
    return true;  // If no divisors found, `n` is prime
}

// Generate all prime numbers less than `n` using the `isPrime` function
void generatePrimes(int64_t n) {
    for (int64_t i = 2; i < n; i++) {  // Start from 2, the smallest prime
        if (isPrime(i)) {  // If `i` is prime
            primes.insert(i);  // Insert the prime into the set
        }
    }
}

// Perform modular exponentiation: compute (base^exp) % mod
// This function uses the "exponentiation by squaring" method for efficiency
int64_t mod_pow(int64_t base, int64_t exp, int64_t mod) {
    int64_t result = 1;  // Initialize result as 1
    base = base % mod;  // Take base modulo `mod` initially to reduce size

    // While `exp` is greater than 0
    while (exp > 0) {
        // If `exp` is odd, multiply the result by `base` modulo `mod`
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;  // Divide `exp` by 2 (right shift by 1)
        base = (base * base) % mod;  // Square the base and reduce modulo `mod`
    }
    return result;  // Return the final result
}

// Calculate the power of 10 just greater than or equal to `n`
// For example, if n = 123, tenPower will return 1000
int64_t tenPower(int64_t n) {
    int64_t tenPower = 1;  // Initialize tenPower as 1
    while (n != 0) {  // While `n` is not zero
        n /= 10;  // Reduce `n` by dividing by 10
        tenPower *= 10;  // Multiply tenPower by 10
    }
    return tenPower;  // Return the result
}

int main() {
    int64_t sum = 0;  // Use int64_t for handling large integers
    generatePrimes(1001000);  // Generate all primes less than 1,001,000

    // Loop over the generated primes using an iterator
    for (auto it = primes.begin(); it != primes.end(); it++) {
        auto p1 = *it;  // Get the current prime (p1)
        auto p2 = *std::next(it, 1);  // Get the next prime (p2)

        if (p1 < 5) continue;  // Skip primes less than 5
        if (p1 > 1000000) break;  // Stop the loop if p1 exceeds 1,000,000

        auto k = tenPower(p1);  // Get the power of 10 greater than `p1`

        // Calculate m = (-p1 * mod_pow(k, p2-2, p2)) % p2
        // `mod_pow(k, p2-2, p2)` calculates (k^(p2-2)) % p2
        // Then `-p1 *` is multiplied with the result, and the result is taken modulo p2
        int64_t m = (-p1 * mod_pow(k, p2 - 2, p2)) % p2;

        // If the result `m` is negative, adjust it to ensure a positive result (modulo operation)
        if (m < 0) m += p2;

        // Calculate the final term (m * k + p1), where `k` is a power of 10 and `p1` is the prime
        int64_t term = (m * k + p1);

        // Add the calculated term to the sum
        sum += term;
    }

    // Output the final sum
    std::cout << sum << std::endl;

    return 0;  // End the program
}

