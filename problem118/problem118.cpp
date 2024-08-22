#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>

const int MAX_DIGIT = 9;
const int MAX_NUMBER = 987654321;
std::vector<int> primes;
std::vector<std::bitset<MAX_DIGIT>> prime_bitmasks;

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

std::bitset<MAX_DIGIT> get_digit_mask(int n) {
    std::bitset<MAX_DIGIT> mask;
    while (n > 0) {
        int digit = n % 10;
        if (digit == 0 || mask[digit - 1]) return 0; // Return empty bitset if digit is 0 or repeated
        mask[digit - 1] = 1;
        n /= 10;
    }
    return mask;
}

// Function to perform a simple Sieve of Eratosthenes to generate small primes up to sqrt(n)
void simple_sieve(int limit, std::vector<int> &prime) {
    std::vector<bool> mark(limit + 1, true);
    
    for (int p = 2; p * p <= limit; ++p) {
        if (mark[p]) {
            for (int i = p * p; i <= limit; i += p) {
                mark[i] = false;
            }
        }
    }
    
    for (int p = 2; p <= limit; ++p) {
        if (mark[p]) {
            prime.push_back(p);
        }
    }
}

// Function to generate primes using a segmented sieve
void segmented_sieve(int n) {
    int limit = std::sqrt(n) + 1;
    std::vector<int> small_primes;
    simple_sieve(limit, small_primes); // Get all primes up to sqrt(n)
    
    int low = limit;
    int high = 2 * limit;

    // Add the small primes directly to the primes list if they are valid
    for (int p : small_primes) {
        std::bitset<MAX_DIGIT> mask = get_digit_mask(p);
        if (mask.count() > 0) {
            primes.push_back(p);
            prime_bitmasks.push_back(mask);
        }
    }

    while (low < n) {
        if (high >= n) high = n;

        // Initialize all numbers in the current segment as prime
        std::vector<bool> mark(high - low + 1, true);

        // Mark non-primes in the current range using the small primes
        for (int i = 0; i < small_primes.size(); ++i) {
            int loLim = std::max(small_primes[i] * small_primes[i], (low + small_primes[i] - 1) / small_primes[i] * small_primes[i]);

            for (int j = loLim; j < high; j += small_primes[i]) {
                mark[j - low] = false;
            }
        }

        // Primes in the current range
        for (int i = low; i < high; ++i) {
            if (mark[i - low]) {
                std::bitset<MAX_DIGIT> mask = get_digit_mask(i);
                if (mask.count() > 0) {
                    primes.push_back(i);
                    prime_bitmasks.push_back(mask);
                }
            }
        }

        // Move to the next segment
        low = low + limit;
        high = high + limit;
    }
}

int count_pandigital_prime_sets() {
    std::vector<int> dp(1 << MAX_DIGIT, 0); // DP array for subsets of digits
    dp[0] = 1; // Start with an empty set
    
    for (size_t i = 0; i < primes.size(); ++i) {
        std::bitset<MAX_DIGIT> prime_mask = prime_bitmasks[i];
        int prime_mask_int = static_cast<int>(prime_mask.to_ulong());
        
        for (int j = (1 << MAX_DIGIT) - 1; j >= 0; --j) {
            if ((j & prime_mask_int) == 0) {
                dp[j | prime_mask_int] += dp[j];
            }
        }
    }
    
    return dp[(1 << MAX_DIGIT) - 1]; // Return count of valid sets covering all digits 1-9
}

int main() {
    segmented_sieve(MAX_NUMBER);
    //std::cout << "Primes generated: " << primes.size() << std::endl;
    int result = count_pandigital_prime_sets();
    std::cout << result << std::endl;
    return 0;
}

