#include <iostream>
#include <vector>

// Function to generate all prime numbers up to 'n' using the Sieve of Eratosthenes algorithm.
std::vector<int> generatePrimes(int n) {
    std::vector<int> primes; // Stores the prime numbers
    if (n < 2) return primes; // No primes exist for n < 2

    std::vector<bool> isPrime(n + 1, true); // Boolean array to mark whether a number is prime
    isPrime[0] = isPrime[1] = false;       // 0 and 1 are not prime numbers

    // Main sieve logic
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);           // Add prime number to the list
            for (int j = i * 2; j <= n; j += i) {
                isPrime[j] = false;        // Mark multiples of 'i' as non-prime
            }
        }
    }

    return primes;
}

int main() {
    // Define a large limit up to which primes will be calculated
    static const int N_MAX = 1000000;

    // Start with 2 to include contributions from the initial prime p = 3
    unsigned long long count = 2;

    // Generate all primes up to N_MAX
    std::vector<int> primes = generatePrimes(N_MAX);

    // Iterate over all primes and perform calculations for primes > 3
    for (size_t i = 0; i < primes.size(); ++i) {
        if (primes[i] <= 3) continue; // Skip primes <= 3 as they don't contribute

        // Calculate the square of the prime and adjust the count
        unsigned long long sq = static_cast<unsigned long long>(primes[i]) * primes[i];
        count += (sq - 1) / 12; // Update count based on the given formula
    }

    // Output the final result
    std::cout << count << std::endl;

    return 0;
}
